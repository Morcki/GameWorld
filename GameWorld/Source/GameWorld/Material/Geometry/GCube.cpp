#include <PrecompiledHeader.h>
#include "GCube.h"

#include "GameWorld/Render/RenderCore.h"
#include "GameWorld/Render/RenderCommand.h"
#include "GameWorld/Render/RenderBuffer.h"

namespace GameWorld
{
	constexpr GW_FLOAT32 CubeVertices[] =
	{
		// back face
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
		// front face
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		// left face
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		// right face
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		// top face
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
	};

	const std::string cube_vertex_code =
		R"(
			# version 330 core
			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec3 aNormal;
			layout(location = 2) in vec2 aTexcoord;
			out vec2 Texcoord;
			uniform mat4 uModel;
			uniform mat4 uView;
			uniform mat4 uProj;

			void main()
			{
				Texcoord = aTexcoord;
				gl_Position = uProj * uView * uModel * vec4(aPosition, 1.0);
			}
		)";

	const std::string cube_fragment_code =
		R"(
			# version 330 core
			layout(location = 0) out vec4 fragColor;

			in vec3 TexCoords;
			uniform samplerCube skybox;

			void main()
			{
				fragColor = vec4( 0.85f, 0.55f, 0.96f, 1.00f );
			}
		)";

	GCube::GCube()
	{
		Init();
	}

	GCube::GCube(MTransform transform)
		: m_transform(transform)
	{
		Init();
	}

	GCube::~GCube()
	{

	}
	
	void GCube::Init()
	{
		m_transform.m_position += glm::vec3(5.0f, 1.0f, 0.0f);
		m_transform.m_scale *= 0.1;

		render_shader_ = ShaderBase::CreateShaderBase();
		render_vao_ = RenderArray::CreateRenderArray();

		auto& render_vbo = VertexBuffer::CreateVertexBuffer(const_cast<GW_FLOAT32*>(CubeVertices), sizeof(CubeVertices));
		render_vbo->SetLayout
		({
			{ShaderDataType::Float3 ,"aPosition"},
			{ShaderDataType::Float3 ,"aNormal"},
			{ShaderDataType::Float2 ,"aTexcoord"},
		});

		render_vao_->AddVertexBuffer(render_vbo);

		render_shader_->LinkSourceCode(cube_vertex_code, cube_fragment_code);
		//ShaderTool::SetIntUniform(render_shader_->GetProgramID(), "skybox", 0);
	}

	void GCube::TickUpdate(const Ref<GCamera>& camera)
	{
		RenderPass(render_shader_)
		.begin()
		.next([&]()
		{
			RenderCommand::SetDepthTest(true);
		})
		.next([&]()
		{
			render_vao_->Bind();

			//auto trans = m_transform.ToTransformMat();
			//for (int i = 0; i < 4; i++)
			//{
			//	for (int j = 0; j < 4; j++)
			//	{
			//		std::cout << trans[i][j] << " ";
			//	}
			//	std::cout << "\n";
			//}
			
			auto trans = glm::scale(m_transform.m_scale) * glm::mat4(1.0f);
			ShaderTool::SetMat4Uniform(render_shader_->GetProgramID(), "uModel", trans);
			ShaderTool::SetMat4Uniform(render_shader_->GetProgramID(), "uView",  camera->GetViewMat());
			ShaderTool::SetMat4Uniform(render_shader_->GetProgramID(), "uProj",  camera->GetProjectionMat());
		})
		.next([&]()
		{
			RenderCommand::DrawArrays(36);
		})
		.end([&]()
		{

		});
	}

}
