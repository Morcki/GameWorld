#pragma once

#include "GameWorld/Core/Core.h"
#include "GameWorld/Core/Window.h"
#include "GameWorld/Events/Event.h"
#include "GameWorld/Layer/LayerStack.h"
#include "GameWorld/GUI/ImGuiLayer.h"

namespace GameWorld
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		inline static Application& GetInst() { return *s_instance_; }
		inline Window& GetWindow() const { return *ptr_window_; }

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline const GW_FLOAT32* GetBackgroundColor() const { return window_background_color_; };
		inline void SetBackgroundColor(GW_FLOAT32 color[4]) { memcpy(window_background_color_, color, sizeof(GW_FLOAT32) * 4); };

	private:
		void OnEvent(Event& e);
		bool OnWindowsClose(Event& e);
		bool OnWindowResize(Event& e);

	private:
		static Application*  s_instance_;
		Scope<Window>        ptr_window_;
		LayerStack           layerstack_;
		ImGuiLayer*          imgui_base_render_layer_;

		float window_background_color_[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

		bool b_gameworld_running = true;
		bool b_set_minSize = true;
	};

	// To be defined in Client
	Application* CreateApplication();
}

