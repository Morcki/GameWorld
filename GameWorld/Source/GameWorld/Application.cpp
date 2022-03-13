#include "PrecompiledHeader.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameWorld
{
#define BIND_FUNCTION(func) std::bind(&Application::func, this, std::placeholders::_1)

	Application::Application()
	{
		GameWorldWindow = std::unique_ptr<Window>(Window::Create());
		GameWorldWindow->SetEventCallback(BIND_FUNCTION(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (bGameWorldRunning)
		{
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			GameWorldWindow->OnUpdate();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(0.05);
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		GAMEWORLD_CORE_INFO("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(OnWindowsClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FUNCTION(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*(--it))->OnEvent(e);
		}
	}

	bool Application::OnWindowResize(Event& e)
	{
		
		return true;
	}

	bool Application::OnWindowsClose(Event& e)
	{
		bGameWorldRunning = false;
		return bGameWorldRunning;
	}

}

