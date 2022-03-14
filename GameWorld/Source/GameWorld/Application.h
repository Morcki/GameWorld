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

		inline static Application& GetInst() { return *ApplicationInstance; }
		inline Window& GetWindow() const { return *GameWorldWindow; }

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		void OnEvent(Event& e);
		bool OnWindowsClose(Event& e);
	private:
		static Application* ApplicationInstance;
		std::unique_ptr<Window> GameWorldWindow;
		bool bGameWorldRunning = true;
		LayerStack m_LayerStack;
	};

	// To be defined in Client
	Application* CreateApplication();
}

