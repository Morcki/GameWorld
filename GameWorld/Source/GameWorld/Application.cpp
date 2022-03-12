#include "PrecompiledHeader.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace GameWorld
{
	Application::Application()
	{
		GameWorldWindow = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (bGameWorldRunning)
		{
			//glClearColor(1, 0, 1, 1);
			//glClear(GL_COLOR_BUFFER_BIT);
			GameWorldWindow->OnUpdate();
		}
	}


}

