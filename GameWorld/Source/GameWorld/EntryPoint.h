#pragma once
#ifdef GAMEWORLD_PLATFORM_WINDOWS

extern GameWorld::Application* GameWorld::GetApplication();

int main(int argc, char** argv)
{

	GAMEWORLD_CORE_INFO("Welcome to Game World!");
	
	auto app = GameWorld::GetApplication();
	
	app->Init();
	app->Run();
	app->Close();

	delete app;

	return 0;
}

#endif