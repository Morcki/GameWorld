#include <GameWorld.h>

#include "imgui/imgui.h"
#include "glm/glm.hpp"

class TestLayer : public GameWorld::Layer
{
public:
	TestLayer(const std::string& name = "TestLayer")
		: Layer(name)
	{
	}

	virtual	~TestLayer()
	{
	}

	void OnUpdate(GameWorld::Timestep ts) override
	{
		//GAMEWORLD_INFO("For Test Layer : update");
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
		const float* background_color = GameWorld::Application::GetInst().GetBackgroundColor();
		float tmp_color[4] = { background_color[0], background_color[1], background_color[2], background_color[3] };
		ImGui::ColorEdit4("Color", tmp_color);

		GameWorld::Application::GetInst().SetBackgroundColor(tmp_color);

		// Plot some values
		const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
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
		if (event.GetEventType() == GameWorld::EventType::KeyPressed)
		{
			GameWorld::KeyPressedEvent& e = (GameWorld::KeyPressedEvent&) event;
			GAMEWORLD_INFO("For Test Layer : {0}", (char)e.GetKeyCode());
		}
	}

};

class SandBox : public GameWorld::Application
{
public:

	SandBox()
	{
		GAMEWORLD_WARN("Application is running on sandbox");
		PushLayer(new TestLayer());
	};

	virtual ~SandBox()
	{

	};

};

GameWorld::Application* GameWorld::CreateApplication()
{
	return new SandBox();
}