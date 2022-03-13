#pragma once
#include "Core/Core.h"
#include "Core/Window.h"
#include "Events/Event.h"
#include "Layer/LayerStack.h"

namespace GameWorld
{
	class GAMEWORLD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		void OnEvent(Event& e);
		bool OnWindowResize(Event& e);
		bool OnWindowsClose(Event& e);
	private:
		std::unique_ptr<Window> GameWorldWindow;
		bool bGameWorldRunning = true;
		LayerStack m_LayerStack;
	};

	// To be defined in Client
	Application* CreateApplication();
}

