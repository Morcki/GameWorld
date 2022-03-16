#include "PrecompiledHeader.h"

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/ApplicationEvent.h"
#include "Input/InputSystem.h"
#include "GameWorld/GUI/ImGuiLayer.h"

namespace GameWorld
{
	Application* Application::ApplicationInstance = nullptr;

	Application::Application()
	{
		GAMEWORLD_CORE_ASSERT(!ApplicationInstance, "Application already been created!");
		ApplicationInstance = this;

		GameWorldWindow = Scope<Window>(Window::Create());
		GameWorldWindow->SetEventCallback(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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

			m_ImGuiLayer->RenderTickBegin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->RenderTickEnd();

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
		//GAMEWORLD_CORE_INFO("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnWindowsClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnWindowResize));

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

	bool Application::OnWindowResize(Event& e)
	{
		WindowResizeEvent& event = (WindowResizeEvent&)e;
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			bSetMinSize = true;
			return false;
		}

		bSetMinSize = false;
		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}

