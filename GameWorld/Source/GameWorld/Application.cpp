#include "PrecompiledHeader.h"

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
		GAMEWORLD_TRACE(e);
		if (e.IsInCategory(EventCategoryApplication))
		{
			GAMEWORLD_INFO("Application");
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			GAMEWORLD_INFO("Input");
		}
		while (true);
	}


}

