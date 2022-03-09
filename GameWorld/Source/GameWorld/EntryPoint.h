#pragma once
#ifdef GAMEWORLD_PLATFORM_WINDOWS

extern GameWorld::Application* GameWorld::CreateApplication();

int main(int argc, char** argv)
{
	GameWorld::Log::Init();

	GAMEWORLD_CORE_INFO("Welcome to Game World!");

	GAMEWORLD_WARN("app is running on sandbox");

	auto app = GameWorld::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif