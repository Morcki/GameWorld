#include <GameWorld.h>

class TestLayer : public GameWorld::Layer
{
public:
	TestLayer(const std::string& name = "TestLayer")
		: Layer(name)
	{
	}
	virtual	~TestLayer()
	{
	}

	void OnUpdate(GameWorld::Timestep ts) override
	{
		GAMEWORLD_INFO("For Test Layer : update");
	}

	void OnEvent(GameWorld::Event& event) override
	{
		GAMEWORLD_INFO("For Test Layer : {0}", event);
	}

};

class SandBox : public GameWorld::Application
{
public:

	SandBox() 
	{
		GAMEWORLD_WARN("Application is running on sandbox");
		PushLayer(new TestLayer());
		PushOverlay(new GameWorld::ImGuiLayer());
	};

	virtual ~SandBox()
	{

	};

};

GameWorld::Application* GameWorld::CreateApplication()
{
	return new SandBox();
}