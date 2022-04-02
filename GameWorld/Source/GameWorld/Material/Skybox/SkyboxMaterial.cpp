#include <PrecompiledHeader.h>
#include "SkyboxMaterial.h"

#include "GameWorld/Render/ShaderBase.h"
#include "GameWorld/Render/RenderCore.h"
#include "GameWorld/Render/RenderCommand.h"

namespace GameWorld
{
	const GW_FLOAT32 skybox_vertices[] =
	{
		// positions          
		-1.0f,  1.0f, -1.0f,   -1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,    1.0f,  1.0f, -1.0f,   -1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,   -1.0f, -1.0f, -1.0f,   -1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,   -1.0f,  1.0f,  1.0f,   -1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,    1.0f, -1.0f,  1.0f,    1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,    1.0f,  1.0f, -1.0f,    1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,   -1.0f,  1.0f,  1.0f,    1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,    1.0f, -1.0f,  1.0f,   -1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,    1.0f,  1.0f, -1.0f,    1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,   -1.0f,  1.0f,  1.0f,   -1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,   -1.0f, -1.0f,  1.0f,    1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,   -1.0f, -1.0f,  1.0f,    1.0f, -1.0f,  1.0f
	};

	const std::string skybox_vertex_code = 
		R"(
			# version 330 core
			layout(location = 0) in vec3 aPos;
			out vec3 TexCoords;
			uniform vec3 uCameraPos;
			uniform mat4 uView;
			uniform mat4 uProj;

			void main()
			{
				TexCoords = aPos;
				vec4 pos = uProj * uView * vec4(aPos + uCameraPos, 1.0);
				gl_Position = pos.xyww;
			}
		)";

	const std::string skybox_fragment_code = 
		R"(
			# version 330 core
			layout(location = 0) out vec4 fragColor;

			in vec3 TexCoords;
			uniform samplerCube skybox;

			void main()
			{
				fragColor = texture(skybox, TexCoords);
			}
		)";

	SkyboxMaterial::SkyboxMaterial(const Ref<GCamera>& camera)
		: camera_(camera)
	{
		ResetShader();
		ResetTexture();
	}

	SkyboxMaterial::SkyboxMaterial(const Ref<GCamera>& camera, const std::array<std::string, 6>& faces)
		: camera_(camera)
	{
		SetTexture(faces);

		ResetShader();
		ResetTexture();
	}

	SkyboxMaterial::~SkyboxMaterial()
	{

	}

	void SkyboxMaterial::SetTexture(GW_INT32 index_face, const std::string& image_path)
	{
		GAMEWORLD_CORE_ASSERT(index_face < 6 && index_face >= 0, "Invalid Index(0<= i <6) : {0}", index_face);
		skybox_textureinfo_[index_face].LoadImgFile(image_path);
		ResetTexture();
	}
	
	void SkyboxMaterial::SetTexture(const std::array<std::string, 6>& faces)
	{
		for (GW_INT32 i = 0; i < faces.size(); i++)
		{
			skybox_textureinfo_[i].LoadImgFile(faces[i]);
		}
		ResetTexture();
	}

	void SkyboxMaterial::ResetShader()
	{
		render_shader_  = ShaderBase::CreateShaderBase();
		render_vao_     = RenderArray::CreateRenderArray();
		auto render_vbo = VertexBuffer::CreateVertexBuffer(const_cast<GW_FLOAT32*>(skybox_vertices), sizeof(skybox_vertices));

		render_vbo->SetLayout
		({
			{ ShaderDataType::Float3, "aPosition" },
		});

		render_vao_->AddVertexBuffer(render_vbo);

		render_shader_->LinkSourceCode(skybox_vertex_code, skybox_fragment_code);
		ShaderTool::SetIntUniform(render_shader_->GetProgramID(), "skybox", 0);
	}

	void SkyboxMaterial::ResetTexture()
	{
		render_texture_ = TextureCube3D::CreateTextureCube3D(skybox_textureinfo_);
	}

	void SkyboxMaterial::TickUpdate()
	{
		RenderPass(render_shader_)
		.begin()
		.next([&]()
		{
			RenderCommand::SetDepthTest(false);
		})
		.next([&]()
		{
			render_texture_->Attach();
			render_vao_->Bind();
			ShaderTool::SetVec3Uniform(render_shader_->GetProgramID(), "uCameraPos", camera_->GetPosition());
			ShaderTool::SetMat4Uniform(render_shader_->GetProgramID(), "uView", camera_->GetViewMat());
			ShaderTool::SetMat4Uniform(render_shader_->GetProgramID(), "uProj", camera_->GetProjectionMat());
		})
		.next([&]()
		{
			RenderCommand::DrawArrays(36);
		})
		.end([&]()
		{
			RenderCommand::SetDepthTest(true);
		});
	}
}
