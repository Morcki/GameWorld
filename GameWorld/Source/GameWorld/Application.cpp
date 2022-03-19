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
	Application* Application::Instance = nullptr;

	Application::Application()
	{
		GAMEWORLD_CORE_ASSERT(!Instance, "Application has already been created!");
		Instance = this;

		GameWorldWindow = Scope<Window>(Window::Create());
		GameWorldWindow->SetEventCallback(BIND_CLASS_CALLBACK_FUNCTRION(Application::OnEvent));

		ImGuiBaseRenderLayer = new ImGuiLayer();
		PushOverlay(ImGuiBaseRenderLayer);

		ShaderVertexArray.reset(RenderArray::CreateRenderArray());
		squad_ShaderVertexArray.reset(RenderArray::CreateRenderArray());

		{
			GW_FLOAT32 vertices[3 * 7] =
			{
				-0.25f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
				-0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
				 0.28f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			};

			auto vertexBuffer = CreateAbstractRef<VertexBuffer>(VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices)));
			vertexBuffer->SetLayout
			({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				});
			ShaderVertexArray->AddVertexBuffer(vertexBuffer);

			GW_UINT32 indices[3] = { 0, 1, 2 };
			auto indexBuffer = CreateAbstractRef<IndexBuffer>(IndexBuffer::CreateIndexBuffer(indices, sizeof(indices) / sizeof(GW_UINT32)));
			ShaderVertexArray->SetIndexBuffer(indexBuffer);

			ShaderProgram = CreateScope<ShaderBase>();
			ShaderProgram->LinkShaderFile
			(
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/test.vs",
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/test.fs"
			);
			ShaderProgram->UseShader();
		}
	
		{
			GW_FLOAT32 squad_vertices[4 * 3] =
			{
				-0.35f, -0.5f, 0.0f,
				-0.35f,  0.5f, 0.0f,
				 0.30f, -0.5f, 0.0f,
				 0.30f,  0.5f, 0.0f,
			};
			auto squad_VertexBuffer = CreateAbstractRef<VertexBuffer>(VertexBuffer::CreateVertexBuffer(squad_vertices, sizeof(squad_vertices)));
			squad_VertexBuffer->SetLayout
			({
				{ShaderDataType::Float3, "aPos"},
			});
			squad_ShaderVertexArray->AddVertexBuffer(squad_VertexBuffer);
			GW_UINT32 squad_indices[] = { 0, 1, 2, 1, 2, 3 };
			auto squad_IndexBuffer = CreateAbstractRef<IndexBuffer>(IndexBuffer::CreateIndexBuffer(squad_indices, sizeof(squad_indices) / sizeof(GW_UINT32)));
			squad_ShaderVertexArray->SetIndexBuffer(squad_IndexBuffer);

			squad_ShaderProgram = CreateScope<ShaderBase>();
			squad_ShaderProgram->LinkShaderFile
			(
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/squad.vs",
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/squad.fs"
			);
			squad_ShaderProgram->UseShader();
		}

		
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (bGameWorldRunning)
		{
			// Fresh window color buffer
			RenderCommand::ClearColor({ WindowBackgroundColor[0], WindowBackgroundColor[1], WindowBackgroundColor[2], WindowBackgroundColor[3] });
			RenderCommand::ClearBuffer();

			squad_ShaderProgram->UseShader();
			squad_ShaderVertexArray->Bind();
			RenderCommand::DrawElements(squad_ShaderVertexArray);

			ShaderProgram->UseShader();
			ShaderVertexArray->Bind();
			RenderCommand::DrawElements(ShaderVertexArray);

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