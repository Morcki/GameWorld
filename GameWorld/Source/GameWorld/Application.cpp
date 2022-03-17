#include "PrecompiledHeader.h"

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/ApplicationEvent.h"
#include "Input/InputSystem.h"
#include "GameWorld/GUI/ImGuiLayer.h"

namespace GameWorld
{
	Application* Application::Instance = nullptr;

	Application::Application()
	{
		GAMEWORLD_CORE_ASSERT(!Instance, "Application has already been created!");
		Instance = this;

		GameWorldWindow = Scope<Window>(Window::Create());
		GameWorldWindow->SetEventCallback(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnEvent));

		ImGuiBaseRenderLayer = new ImGuiLayer();
		PushOverlay(ImGuiBaseRenderLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] =
		{
			-0.25f,  0.5f, 0.0f,
			-0.25f, -0.5f, 0.0f,
			 0.28f,  0.0f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);


		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (bGameWorldRunning)
		{
			// Fresh window color buffer
			glClearColor(WindowBackgroundColor[0], WindowBackgroundColor[1], WindowBackgroundColor[2], WindowBackgroundColor[3]);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : GameWorldLayerStack)
			{
				layer->OnUpdate(0.05);
			}

			ImGuiBaseRenderLayer->RenderTickBegin();
			for (Layer* layer : GameWorldLayerStack)
			{
				layer->OnImGuiRender();
			}
			ImGuiBaseRenderLayer->RenderTickEnd();

			GameWorldWindow->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		GameWorldLayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		GameWorldLayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		//GAMEWORLD_CORE_INFO("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnWindowsClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnWindowResize));

		for (auto it = GameWorldLayerStack.end(); it != GameWorldLayerStack.begin();)
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

