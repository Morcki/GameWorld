#pragma once
#include "Core/Core.h"
#include "Core/Window.h"

namespace GameWorld
{
	class GAMEWORLD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> GameWorldWindow;
		bool bGameWorldRunning = true;
	
	};

	// To be defined in Client
	Application* CreateApplication();
}

