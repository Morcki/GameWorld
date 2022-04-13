#include <PrecompiledHeader.h>
#include "GSphere.h"

#include <vector>
#include "glm/glm.hpp"

#include "GameWorld/Render/RenderCore.h"
#include "GameWorld/Render/RenderCommand.h"
#include "GameWorld/Application.h"

namespace GameWorld
{

	constexpr GW_UINT32 X_SEGMENTS = 64;
	constexpr GW_UINT32 Y_SEGMENTS = 64;

	GSphereSingleton::GSphereSingleton()
	{

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> normals;
		std::vector<GW_UINT32> indices;
		
		for (GW_UINT32 x = 0; x <= X_SEGMENTS; ++x)
		{
			for (GW_UINT32 y = 0; y <= Y_SEGMENTS; ++y)
			{
				GW_FLOAT32 xSegment = (GW_FLOAT32)x / (GW_FLOAT32)X_SEGMENTS;
				GW_FLOAT32 ySegment = (GW_FLOAT32)y / (GW_FLOAT32)Y_SEGMENTS;
				GW_FLOAT32 xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
				GW_FLOAT32 yPos = std::cos(ySegment * M_PI);
				GW_FLOAT32 zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

				positions.push_back(glm::vec3(xPos, yPos, zPos));
				uv.push_back(glm::vec2(xSegment, ySegment));
				normals.push_back(glm::vec3(xPos, yPos, zPos));
			}
		}

		GW_BOOL oddRow = false;
		for (GW_UINT32 y = 0; y < Y_SEGMENTS; ++y)
		{
			if (!oddRow) // even rows: y == 0, y == 2; and so on
			{
				for (GW_UINT32 x = 0; x <= X_SEGMENTS; ++x)
				{
					indices.push_back(y       * (X_SEGMENTS + 1) + x);
					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				}
			}
			else
			{
				for (GW_INT32 x = X_SEGMENTS; x >= 0; --x)
				{
					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					indices.push_back(y       * (X_SEGMENTS + 1) + x);
				}
			}
			oddRow = !oddRow;
		}

		std::vector<GW_FLOAT32> data;
		for (GW_UINT32 i = 0; i < positions.size(); ++i)
		{
			data.push_back(positions[i].x);
			data.push_back(positions[i].y);
			data.push_back(positions[i].z);
			if (normals.size() > 0)
			{
				data.push_back(normals[i].x);
				data.push_back(normals[i].y);
				data.push_back(normals[i].z);
			}
			if (uv.size() > 0)
			{
				data.push_back(uv[i].x);
				data.push_back(uv[i].y);
			}
		}
		
		render_vao = RenderArray::CreateRenderArray();

		auto& render_vbo = VertexBuffer::CreateVertexBuffer(&data[0], data.size() * sizeof(GW_FLOAT32));
		render_vbo->SetLayout
		({
			{ShaderDataType::Float3 ,"aPosition"},
			{ShaderDataType::Float3 ,"aNormal"},
			{ShaderDataType::Float2 ,"aTexcoord"},
		});
		auto render_ebo = IndexBuffer::CreateIndexBuffer(&indices[0], indices.size());

		render_vao->AddVertexBuffer(render_vbo);
		render_vao->SetIndexBuffer(render_ebo);
	}

	GSphereSingleton::~GSphereSingleton()
	{

	}

	void GSphereSingleton::DrawCall()
	{
		render_vao->Bind();
		RenderBase::DrawCall(render_vao);
		render_vao->UnBind();
	}

	GSphereInstance::GSphereInstance()
		: GComponent(std::string("Sphere_") + std::to_string(s_num_sphere_instance++))
	{
		Init();
	}

	GSphereInstance::GSphereInstance(MTransform transform)
	{
		m_transform = transform;
		Init();
	}

	GSphereInstance::~GSphereInstance()
	{

	}

	void GSphereInstance::Init()
	{
		auto shader = ShaderBase::CreateShaderBase();
		//shader->LinkSourceCode(sphere_vertex_code, sphere_fragment_code);
		shader->LinkShaderFile("Assets/Shader/Default/DefaultLighting.vert", "Assets/Shader/Default/DefaultLighting.frag");
		m_material.BindShader(shader);
	}

	void GSphereInstance::TickUpdate()
	{
#if RUN_WITH_EDITOR
		auto camera = Application::GetInst().GetCamera();
#else
		// TODO : Add Game Camera
		GAMEWORLD_CORE_ASSERT(false, "GCube::TickUpdate => Not Support yet!")
#endif

		auto shader = m_material.GetShader();
		auto directional_light = Application::GetInst().GetSceneManager().GetDirectgionalLight();
		auto ambient_light = Application::GetInst().GetSceneManager().GetAmbientLight();

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
			ShaderTool::SetMat4Uniform(shader->GetProgramID(), "uView", camera.GetViewMat());
			ShaderTool::SetMat4Uniform(shader->GetProgramID(), "uProj", camera.GetProjectionMat());
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
			GSphereSingleton::GetInst().DrawCall();
		})
		.end([]()
		{

		});
	}

}