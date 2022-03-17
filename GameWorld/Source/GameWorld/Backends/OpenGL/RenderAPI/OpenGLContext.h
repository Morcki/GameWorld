#pragma once
#include "GameWorld/Render/RenderContext.h"

#include <GLFW/glfw3.h>

namespace GameWorld
{
	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		virtual ~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;


	private:
		GLFWwindow* WindowHandle;
	};

}