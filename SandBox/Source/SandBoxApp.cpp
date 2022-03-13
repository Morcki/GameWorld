#include <GameWorld.h>

class TestLayer : public GameWorld::Layer
{
public:
	TestLayer(const std::string& name = "Example")
		: Layer(name)
	{
	}
	virtual	~TestLayer()
	{
	}

	void OnUpdate(GameWorld::Timestep ts) override
	{
		GAMEWORLD_INFO("For Layer Test : update");
	}

	void OnEvent(GameWorld::Event& event) override
	{
		GAMEWORLD_INFO("For Layer Test : {0}", event);
	}

};

class SandBox : public GameWorld::Application
{
public:

	SandBox() 
	{
		GAMEWORLD_WARN("Application is running on sandbox");
		PushLayer(new TestLayer());
	};

	virtual ~SandBox()
	{

	};

};

GameWorld::Application* GameWorld::CreateApplication()
{
	return new SandBox();
}