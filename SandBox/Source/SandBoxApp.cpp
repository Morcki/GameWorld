#include <GameWorld.h>

#include "imgui/imgui.h"
#include "glm/glm.hpp"

using namespace GameWorld;

class Game2DLayer : public GameWorld::Layer
{
private:
	Ref<ShaderBase>      shader_program_;
	Ref<RenderArray>     shader_vertex_array_;
	Ref<ShaderBase>      squad_shader_program_;
	Ref<RenderArray>     squad_shader_vertex_array_;
	Scope<Camera2DOrthoController> camera_controller_;
public:
	Game2DLayer(const std::string& name = "TestLayer")
		: Layer(name)
	{
		camera_controller_ = CreateScope<Camera2DOrthoController>(1.0f, true);
		shader_vertex_array_.reset(RenderArray::CreateRenderArray());
		squad_shader_vertex_array_.reset(RenderArray::CreateRenderArray());

		{
			GW_FLOAT32 vertices[3 * 7] =
			{
				-0.25f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
				-0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
				 0.28f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			};

			auto vertex_buffer = CreateAbstractRef<VertexBuffer>(VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices)));
			vertex_buffer->SetLayout
			({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
			});
			shader_vertex_array_->AddVertexBuffer(vertex_buffer);

			GW_UINT32 indices[3] = { 0, 1, 2 };
			auto index_buffer = CreateAbstractRef<IndexBuffer>(IndexBuffer::CreateIndexBuffer(indices, sizeof(indices) / sizeof(GW_UINT32)));
			shader_vertex_array_->SetIndexBuffer(index_buffer);

			shader_program_ = CreateScope<ShaderBase>();

			shader_program_->LinkShaderFile
			(
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/test.vs",
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/test.fs"
			);
			shader_program_->UseShader();
		}

		{
			GW_FLOAT32 squad_vertices[4 * 3] =
			{
				-0.35f, -0.5f, 0.0f,
				-0.35f,  0.5f, 0.0f,
				 0.30f, -0.5f, 0.0f,
				 0.30f,  0.5f, 0.0f,
			};
			auto squad_vertex_buffer = CreateAbstractRef<VertexBuffer>(VertexBuffer::CreateVertexBuffer(squad_vertices, sizeof(squad_vertices)));
			squad_vertex_buffer->SetLayout
			({
				{ShaderDataType::Float3, "aPos"},
				});
			squad_shader_vertex_array_->AddVertexBuffer(squad_vertex_buffer);
			GW_UINT32 squad_indices[] = { 0, 1, 2, 1, 2, 3 };
			auto squad_index_buffer = CreateAbstractRef<IndexBuffer>(IndexBuffer::CreateIndexBuffer(squad_indices, sizeof(squad_indices) / sizeof(GW_UINT32)));
			squad_shader_vertex_array_->SetIndexBuffer(squad_index_buffer);

			squad_shader_program_ = CreateScope<ShaderBase>();

			squad_shader_program_->LinkShaderFile
			(
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/squad.vs",
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/squad.fs"
			);
			squad_shader_program_->UseShader();
		}
	}

	virtual	~Game2DLayer()
	{
	}

	void OnUpdate(GameWorld::Timestep ts) override
	{
		camera_controller_->TickUpdate(ts);
		squad_shader_program_->UseShader();
		ShaderTool::SetMat4Uniform(squad_shader_program_->GetProgramID(), "uVPmat", camera_controller_->GetCamera().GetViewProjectionMatrix());
		squad_shader_vertex_array_->Bind();
		RenderCommand::DrawElements(squad_shader_vertex_array_);

		shader_program_->UseShader();
		ShaderTool::SetMat4Uniform(shader_program_->GetProgramID(), "uVPmat", camera_controller_->GetCamera().GetViewProjectionMatrix());
		shader_vertex_array_->Bind();
		RenderCommand::DrawElements(shader_vertex_array_);
	}

	void  OnImGuiRender()
	{
		static bool my_tool_active;
		ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// Edit a color (stored as ~4 floats)
		const GW_FLOAT32* background_color = GameWorld::Application::GetInst().GetBackgroundColor();
		GW_FLOAT32 tmp_color[4] = { background_color[0], background_color[1], background_color[2], background_color[3] };
		ImGui::ColorEdit4("Color", tmp_color);

		GameWorld::Application::GetInst().SetBackgroundColor(tmp_color);

		// Plot some values
		const GW_FLOAT32 my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
		ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

		// Display contents in a scrolling region
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < 50; n++)
			ImGui::Text("%04d: Some text", n);
		ImGui::EndChild();
		ImGui::End();
	}

	void OnEvent(GameWorld::Event& event) override
	{
		camera_controller_->OnEvent(event);
		if (event.GetEventType() == GameWorld::EventType::KeyPressed)
		{
			GameWorld::KeyPressedEvent& e = (GameWorld::KeyPressedEvent&) event;
			GAMEWORLD_INFO("For Test Layer : {0}", (char)e.GetKeyCode());
		}
	}
};

class SandBox2DExample : public GameWorld::Application
{
public:

	SandBox2DExample()
	{
		GAMEWORLD_WARN("Application is running on sandbox");
		PushLayer(new Game2DLayer());
	};

	virtual ~SandBox2DExample()
	{

	};

};

GameWorld::Application* GameWorld::CreateApplication()
{
	return new SandBox2DExample();
}