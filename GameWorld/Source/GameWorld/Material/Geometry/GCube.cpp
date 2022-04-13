#include <PrecompiledHeader.h>
#include "GCube.h"

#include "GameWorld/Render/RenderCore.h"
#include "GameWorld/Render/RenderCommand.h"
#include "GameWorld/Render/RenderBuffer.h"

#include "GameWorld/Material/Light/GLight.h"
#include "GameWorld/Camera/GCameraEditor.h"
#include "GameWorld/Application.h"


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

	GCubeSingleton::GCubeSingleton()
	{
		render_vao = RenderArray::CreateRenderArray();

		auto& render_vbo = VertexBuffer::CreateVertexBuffer(const_cast<GW_FLOAT32*>(CubeVertices), sizeof(CubeVertices));
		render_vbo->SetLayout
		({
			{ShaderDataType::Float3 ,"aPosition"},
			{ShaderDataType::Float3 ,"aNormal"},
			{ShaderDataType::Float2 ,"aTexcoord"},
		});

		render_vao->AddVertexBuffer(render_vbo);
	}

	GCubeSingleton::~GCubeSingleton()
	{

	}

	void GCubeSingleton::DrawCall()
	{
		render_vao->Bind();
		RenderCommand::SetDrawType(RenderDrawType::kTRIANGLES);
		RenderCommand::DrawArrays(36);
		RenderCommand::SetDrawType();
		render_vao->UnBind();
	}

	GCubeInstance::GCubeInstance()
		: GComponent(std::string("Cube_") + std::to_string(s_num_cube_instance++))
	{
		Init();
	}

	GCubeInstance::GCubeInstance(MTransform transform)
	{
		m_transform = transform;
		Init();
	}

	GCubeInstance::~GCubeInstance()
	{

	}
	
	void GCubeInstance::Init()
	{
		auto cube_shader = ShaderBase::CreateShaderBase();
		//cube_shader->LinkSourceCode(cube_vertex_code, cube_fragment_code);
		cube_shader->LinkShaderFile("Assets/Shader/Default/DefaultLighting.vert", "Assets/Shader/Default/DefaultLighting.frag");
		m_material.BindShader(cube_shader);	
	}

	void GCubeInstance::TickUpdate()
	{

#if RUN_WITH_EDITOR
		auto camera = Application::GetInst().GetCamera();
#else
		// TODO : Add Game Camera
		GAMEWORLD_CORE_ASSERT(false, "GCube::TickUpdate => Not Support yet!")
#endif

		auto shader = m_material.GetShader();
		auto directional_light = Application::GetInst().GetSceneManager().GetDirectgionalLight();
		auto ambient_light     = Application::GetInst().GetSceneManager().GetAmbientLight();

		RenderPass(shader)
		.begin()
		.next([]()
		{
			RenderCommand::SetDepthTest(true);
		})
		.next([&]()
		{
			auto model = m_transform.ToTransformMat();

			ShaderTool::SetMat4Uniform(shader->GetProgramID(), "uModel", model);
			ShaderTool::SetMat4Uniform(shader->GetProgramID(), "uView",  camera.GetViewMat());
			ShaderTool::SetMat4Uniform(shader->GetProgramID(), "uProj",  camera.GetProjectionMat());
			ShaderTool::SetMat4Uniform(shader->GetProgramID(), "uModelInvT", glm::transpose(glm::inverse(model)));

			ShaderTool::SetVec3Uniform(shader->GetProgramID(), "uLightDirectional.LightColor", directional_light.m_color);
			ShaderTool::SetVec3Uniform(shader->GetProgramID(), "uLightDirectional.LightDir", directional_light.m_direction);

			ShaderTool::SetVec3Uniform(shader->GetProgramID(), "uCameraPos", camera.GetPosition());
			ShaderTool::SetVec4Uniform(shader->GetProgramID(), "uMat.DiffuseAlbedo", m_material.GetConstant().diffuse_albedo);
			ShaderTool::SetFloatUniform(shader->GetProgramID(), "uMat.Metallic", m_material.GetConstant().metallic);
			ShaderTool::SetFloatUniform(shader->GetProgramID(), "uMat.Shininess", 1 - m_material.GetConstant().roughness);

			ShaderTool::SetVec3Uniform(shader->GetProgramID(), "uAmbientLightColor", ambient_light.m_irradiance);
			
		})
		.next([]()
		{
			GCubeSingleton::GetInst().DrawCall();
		})
		.end([]()
		{

		});
	}

}
