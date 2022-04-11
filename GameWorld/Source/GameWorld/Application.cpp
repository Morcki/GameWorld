#include <PrecompiledHeader.h>

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/ApplicationEvent.h"
#include "Input/InputSystem.h"
#include "GameWorld/GUI/ImGuiLayer.h"
#include "GameWorld/Render/ShaderBase.h"
#include "GameWorld/Render/RenderBuffer.h"
#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLRenderBuffer.h"

#include "GameWorld/Render/ShaderTool.h"
#include "GameWorld/Render/RenderCommand.h"
#include "GameWorld/Render/RenderCore.h"

namespace GameWorld
{
	Application::Application()
	{
		GAMEWORLD_CORE_ASSERT(!ptr_instance_, "GameWorld::Application::Application => Error,Application already existed!");
		ptr_instance_ = this;

		ptr_window_ = Scope<Window>(Window::Create());
		ptr_window_->SetEventCallback(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnEvent));
	}

	Application::~Application()
	{
		
	}

	void Application::Init()
	{
		imgui_base_render_layer_ = new ImGuiLayer();
		PushOverlay(imgui_base_render_layer_);

		RenderBase::Init();

		editor_camera_ = CreateScope<GCameraEditor>();
		editor_camera_->UpdateViewportRatio(ptr_window_->GetAspectRatio());

		scene_manager_ = CreateScope<GSceneManager>("Default Scene");
		scene_manager_->Init();
	}

	void Application::Run()
	{
		while (b_gameworld_running)
		{
			// First Step : Update Tick Time
			GTimeSystem::GetInst().TickUpdate();
			// Second Step : Update Camera
			editor_camera_->TickUpdate();

			// Fresh window color buffer
			RenderCommand::ClearColor({0.0f, 0.0f, 0.0f, 1.0f});
			RenderCommand::ClearBuffer();


			scene_manager_->TickUpdate();
			for (Layer* layer : layerstack_)
			{
				layer->OnUpdate();
			}

			imgui_base_render_layer_->RenderTickBegin(); 
			for (Layer* layer : layerstack_)
			{
				layer->OnImGuiRender();
			}
			imgui_base_render_layer_->RenderTickEnd();

			ptr_window_->OnUpdate();
		}
	}

	void Application::Close()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		layerstack_.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerstack_.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		//GAMEWORLD_CORE_INFO("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnWindowsClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnWindowResize));

		editor_camera_->OnEvent(e);

		for (auto it = layerstack_.end(); it != layerstack_.begin();)
		{
			(*(--it))->OnEvent(e);
		}
	}

	bool Application::OnWindowsClose(WindowCloseEvent& e)
	{
		b_gameworld_running = false;
		return b_gameworld_running;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			b_set_minSize = true;
			return false;
		}

		b_set_minSize = false;
		ptr_window_->ResizeWindow(e.GetWidth(), e.GetHeight());
		RenderBase::ResizeWindow(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}
}