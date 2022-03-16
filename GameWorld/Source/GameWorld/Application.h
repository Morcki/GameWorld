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

		inline static Application& GetInst() { return *Instance; }
		inline Window& GetWindow() const { return *GameWorldWindow; }

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		void OnEvent(Event& e);
		bool OnWindowsClose(Event& e);
		bool OnWindowResize(Event& e);

	private:
		static Application* Instance;
		Scope<Window> GameWorldWindow;
		LayerStack GameWorldLayerStack;
		ImGuiLayer* ImGuiBaseRenderLayer;

		float WindowBackgroundColor[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

		bool bGameWorldRunning = true;
		bool bSetMinSize = true;
	};

	// To be defined in Client
	Application* CreateApplication();
}

