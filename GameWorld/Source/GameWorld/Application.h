#pragma once
#include "Core.h"


namespace GameWorld
{
	class GAMEWORLD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in Client
	Application* CreateApplication();
}

