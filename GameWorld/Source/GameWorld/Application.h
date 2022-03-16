#pragma once

#include "GameWorld/GUI/ImGuiLayer.h"
#include "GameWorld/Layer/LayerStack.h"
#include "GameWorld/Core/Window.h"
#include "GameWorld/Events/Event.h"
#include "GameWorld/Core/Core.h"

namespace GameWorld
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		inline static Application& GetInst() { return *ApplicationInstance; }
		inline Window& GetWindow() const { return *GameWorldWindow; }

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		void OnEvent(Event& e);
		bool OnWindowsClose(Event& e);
		bool OnWindowResize(Event& e);

	private:
		static Application* ApplicationInstance;
		Scope<Window> GameWorldWindow;
		bool bGameWorldRunning = true;
		bool bSetMinSize = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
	};

	// To be defined in Client
	Application* CreateApplication();
}

