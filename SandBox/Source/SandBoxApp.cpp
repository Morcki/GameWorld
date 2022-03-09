#include <GameWorld.h>

class SandBox : public GameWorld::Application
{
public:

	SandBox() 
	{

	};

	virtual ~SandBox()
	{

	};

};

GameWorld::Application* GameWorld::CreateApplication()
{
	return new SandBox();
}