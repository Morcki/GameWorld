#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log/Log.h"


namespace GameWorld
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		GAMEWORLD_CORE_TRACE(e);

		while (true);
	}


}

