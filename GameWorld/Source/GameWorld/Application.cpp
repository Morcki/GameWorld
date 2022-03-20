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

		shader_vertex_array_.reset(RenderArray::CreateRenderArray());
		squad_shader_vertex_array_.reset(RenderArray::CreateRenderArray());

		{
			GW_FLOAT32 vertices[3 * 7] =
			{
				-0.25f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
				-0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
				 0.28f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			};

			auto vertex_buffer = CreateAbstractRef<VertexBuffer>(VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices)));
			vertex_buffer->SetLayout
			({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				});
			shader_vertex_array_->AddVertexBuffer(vertex_buffer);

			GW_UINT32 indices[3] = { 0, 1, 2 };
			auto index_buffer = CreateAbstractRef<IndexBuffer>(IndexBuffer::CreateIndexBuffer(indices, sizeof(indices) / sizeof(GW_UINT32)));
			shader_vertex_array_->SetIndexBuffer(index_buffer);

			shader_program_ = CreateScope<ShaderBase>();
			shader_program_->LinkShaderFile
			(
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/test.vs",
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/test.fs"
			);
			shader_program_->UseShader();
		}
	
		{
			GW_FLOAT32 squad_vertices[4 * 3] =
			{
				-0.35f, -0.5f, 0.0f,
				-0.35f,  0.5f, 0.0f,
				 0.30f, -0.5f, 0.0f,
				 0.30f,  0.5f, 0.0f,
			};
			auto squad_vertex_buffer = CreateAbstractRef<VertexBuffer>(VertexBuffer::CreateVertexBuffer(squad_vertices, sizeof(squad_vertices)));
			squad_vertex_buffer->SetLayout
			({
				{ShaderDataType::Float3, "aPos"},
			});
			squad_shader_vertex_array_->AddVertexBuffer(squad_vertex_buffer);
			GW_UINT32 squad_indices[] = { 0, 1, 2, 1, 2, 3 };
			auto squad_index_buffer = CreateAbstractRef<IndexBuffer>(IndexBuffer::CreateIndexBuffer(squad_indices, sizeof(squad_indices) / sizeof(GW_UINT32)));
			squad_shader_vertex_array_->SetIndexBuffer(squad_index_buffer);

			squad_shader_program_ = CreateScope<ShaderBase>();
			squad_shader_program_->LinkShaderFile
			(
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/squad.vs",
				"F:\\WorkSpace/Development/GameWorld/GameWorld/GameWorld/Shader/squad.fs"
			);
			squad_shader_program_->UseShader();
		}

		
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

			squad_shader_program_->UseShader();
			squad_shader_vertex_array_->Bind();
			RenderCommand::DrawElements(squad_shader_vertex_array_);

			shader_program_->UseShader();
			shader_vertex_array_->Bind();
			RenderCommand::DrawElements(shader_vertex_array_);

			for (Layer* layer : layerstack_)
			{
				layer->OnUpdate(0.05);
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