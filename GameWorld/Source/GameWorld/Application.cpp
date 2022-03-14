#include "PrecompiledHeader.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameWorld
{
	Application* Application::ApplicationInstance = nullptr;

	Application::Application()
	{
		GAMEWORLD_CORE_ASSERT(!ApplicationInstance, "Application already been created!");
		ApplicationInstance = this;

		GameWorldWindow = std::unique_ptr<Window>(Window::Create());
		GameWorldWindow->SetEventCallback(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (bGameWorldRunning)
		{
			// Fresh window color buffer
			glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(0.05);
			}
			GameWorldWindow->OnUpdate();
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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnWindowsClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*(--it))->OnEvent(e);
		}
	}

	bool Application::OnWindowsClose(Event& e)
	{
		bGameWorldRunning = false;
		return bGameWorldRunning;
	}

}

