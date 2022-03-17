#include <PrecompiledHeader.h>

#include "OpenGLContext.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace GameWorld
{

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: WindowHandle(window)
	{
		GAMEWORLD_CORE_ASSERT(window, "Window is nullptr!");
	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GAMEWORLD_CORE_ASSERT(status, "Failed to initialize GLAD!");
		
		GAMEWORLD_CORE_INFO("=============================================");
		GAMEWORLD_CORE_INFO("OpenGL Info:");
		GAMEWORLD_CORE_INFO("  Vender   : {0}", glGetString(GL_VENDOR));
		GAMEWORLD_CORE_INFO("  Renderer : {0}", glGetString(GL_RENDERER));
		GAMEWORLD_CORE_INFO("  Version  : {0}", glGetString(GL_VERSION));
		GAMEWORLD_CORE_INFO("=============================================");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(WindowHandle); // must do this at the end of render tick, swap the buffer of screen and the buffer of rendering results.
	}

}