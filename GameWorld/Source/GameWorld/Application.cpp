#include "PrecompiledHeader.h"

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

namespace GameWorld
{
	Application* Application::s_instance_ = nullptr;

	Application::Application()
	{
		GAMEWORLD_CORE_ASSERT(!s_instance_, "Application has already been created!");
		s_instance_ = this;

		ptr_window_ = Scope<Window>(Window::Create());
		ptr_window_->SetEventCallback(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnEvent));

		imgui_base_render_layer_ = new ImGuiLayer();
		PushOverlay(imgui_base_render_layer_);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (b_gameworld_running)
		{
			// Fresh window color buffer
			RenderCommand::ClearColor
			({
				window_background_color_[0],
				window_background_color_[1],
				window_background_color_[2],
				window_background_color_[3]
				});
			RenderCommand::ClearBuffer();

			for (Layer* layer : layerstack_)
			{
				layer->OnUpdate(0.05f);
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

		for (auto it = layerstack_.end(); it != layerstack_.begin();)
		{
			(*(--it))->OnEvent(e);
		}
	}

	bool Application::OnWindowsClose(Event& e)
	{
		b_gameworld_running = false;
		return b_gameworld_running;
	}

	bool Application::OnWindowResize(Event& e)
	{
		WindowResizeEvent& event = (WindowResizeEvent&)e;
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			b_set_minSize = true;
			return false;
		}

		b_set_minSize = false;
		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}