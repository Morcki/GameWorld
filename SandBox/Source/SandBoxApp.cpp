#include <GameWorld.h>

#include "Layer/Layer2D.h"
#include "Layer/Layer3D.h"

//----Entry Point-----------------
#include "GameWorld/EntryPoint.h"

using namespace GameWorld;

class SandBox2DExample : public GameWorld::Application
{
public:

	SandBox2DExample()
	{
		GAMEWORLD_WARN("Application is running on sandbox 2d example");
	};

	virtual void Init() override
	{
		Application::Init();
		PushLayer(new Game2DLayer());
	}

	virtual void Run() override
	{
		Application::Run();
	}

	virtual ~SandBox2DExample()
	{

	};

};

class SandBox3DExample : public GameWorld::Application
{
public:
	SandBox3DExample()
	{
		GAMEWORLD_WARN("Application is running on sandbox 3d example");
	};

	virtual void Init() override
	{
		Application::Init();
		
		PushLayer(new Game3DLayer());
		RenderCommand::Init3DConfig();
	}

	virtual void Run() override
	{
		Application::Run();
	}

	virtual ~SandBox3DExample()
	{

	};
};

GameWorld::Application* GameWorld::GetApplication()
{
	return new SandBox3DExample();
}