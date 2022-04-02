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
		PushLayer(new Game2DLayer());
	};

	virtual ~SandBox2DExample()
	{

	};

};

class SandBox3DExample : public GameWorld::Application
{
public:
	SandBox3DExample()
	{
		RenderCommand::Init3DConfig();
		GAMEWORLD_WARN("Application is running on sandbox 3d example");
		PushLayer(new Game3DLayer());
	};

	virtual ~SandBox3DExample()
	{

	};
};

GameWorld::Application* GameWorld::CreateApplication()
{
	return new SandBox2DExample();
}