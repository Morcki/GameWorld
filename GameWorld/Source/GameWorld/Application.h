#pragma once

#include "GameWorld/Core/Core.h"
#include "GameWorld/Core/Window.h"
#include "GameWorld/Core/GSingleton.h"
#include "GameWorld/Events/Event.h"
#include "GameWorld/Layer/LayerStack.h"
#include "GameWorld/GUI/ImGuiLayer.h"
#include "GameWorld/Scene/GSceneManager.h"
#include "GameWorld/Camera/GCameraEditor.h"

namespace GameWorld
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Init();
		virtual void Run();
		virtual void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& GetInst()                  { return *ptr_instance_; }
		inline Window&             GetWindow()          const { return *ptr_window_; }
		inline GCameraEditor&      GetCamera()          const { return *editor_camera_; }
		inline GSceneManager&      GetSceneManager()    const { return *scene_manager_; }

	private:
		void OnEvent(Event& e);
		bool OnWindowsClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		inline static Application*  ptr_instance_ = nullptr;
		Scope<Window>               ptr_window_;
		LayerStack                  layerstack_;
		ImGuiLayer*                 imgui_base_render_layer_;
		Scope<GCameraEditor>        editor_camera_;
		Scope<GSceneManager>        scene_manager_;


		float window_background_color_[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

		bool b_gameworld_running{ true };
		bool b_set_minSize{ true };
	};

	// To be defined in Client
	Application* GetApplication();
}

