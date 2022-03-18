#pragma once

#include "GameWorld/Core/Core.h"
#include "GameWorld/Core/Window.h"
#include "GameWorld/Events/Event.h"
#include "GameWorld/Layer/LayerStack.h"
#include "GameWorld/GUI/ImGuiLayer.h"
#include "GameWorld/Render/ShaderBase.h"

namespace GameWorld
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		inline static Application& GetInst() { return *Instance; }
		inline Window& GetWindow() const { return *GameWorldWindow; }

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		inline const GW_FLOAT32* GetBackgroundColor() const { return WindowBackgroundColor; };
		inline void SetBackgroundColor(GW_FLOAT32 color[4]) { memcpy(WindowBackgroundColor, color, sizeof(GW_FLOAT32) * 4); };

	private:
		void OnEvent(Event& e);
		bool OnWindowsClose(Event& e);
		bool OnWindowResize(Event& e);

	private:
		static Application* Instance;
		Scope<Window> GameWorldWindow;
		LayerStack GameWorldLayerStack;
		ImGuiLayer* ImGuiBaseRenderLayer;
		Scope<ShaderBase> ShaderProgram;

		float WindowBackgroundColor[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

		bool bGameWorldRunning = true;
		bool bSetMinSize = true;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};

	// To be defined in Client
	Application* CreateApplication();
}

