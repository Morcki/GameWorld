#include <PrecompiledHeader.h>

#include "WindowsWindow.h"

#include "glad/glad.h"

#include "GameWorld/Application.h"

#include "GameWorld/Events/ApplicationEvent.h"
#include "GameWorld/Events/MouseEvent.h"
#include "GameWorld/Events/KeyEvent.h"

#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLContext.h"

namespace GameWorld 
{

	static GW_UINT8 s_GLFW_window_count = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		GAMEWORLD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		window_info_.title = props.title;
		window_info_.width = props.width;
		window_info_.height = props.height;

		window_resolution_ = { 1.0f / window_info_.width, 1.0f / window_info_.height };
		window_aspect_ratio = (window_info_.width * 1.0) / window_info_.height;

		GAMEWORLD_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (s_GLFW_window_count == 0)
		{
			int success = glfwInit();
			GAMEWORLD_CORE_ASSERT(success, "Failed to initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			window_ = glfwCreateWindow((int)props.width, (int)props.height, window_info_.title.c_str(), nullptr, nullptr);
			++s_GLFW_window_count;
		}

		render_graphics_context_ = new OpenGLContext(window_);
		render_graphics_context_->Init();

		glfwSetWindowUserPointer(window_, &window_info_); // set the structure of data transporting between engine and glfw-window.
		SetVSync(true);

		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.callback_function(event);
			});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.callback_function(event);
			});
		
		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.callback_function(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.callback_function(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.callback_function(event);
					break;
				}
				}
			});

		glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.callback_function(event);
			});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.callback_function(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.callback_function(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.callback_function(event);
			});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xpos, (float)ypos);
				data.callback_function(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window_);
		--s_GLFW_window_count;

		if (s_GLFW_window_count == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		render_graphics_context_->SwapBuffers(); // must do this at the end of render tick, swap the buffer of screen and the buffer of rendering results.
	}

	void WindowsWindow::SetVSync(bool enabled)
	{//´¹Ö±Í¬²½ v-sync

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		window_info_.b_vertical_sync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return window_info_.b_vertical_sync;
	}

}