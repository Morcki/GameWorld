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

		GDirectionalLight dir_light;
		dir_light.m_color = glm::vec3(300.f, 300.f, 300.f);
		dir_light.m_direction = glm::vec3(-10.0f, -10.0f, -10.0f);
		GAmbientLight amb_light;
		amb_light.m_irradiance = glm::vec3(0.2f);

		Application::GetInst().GetSceneManager().PlaceDirecionalLight(dir_light);
		Application::GetInst().GetSceneManager().PlaceAmbientLight(amb_light);
	}

	virtual void Run() override
	{
		Application::Run();
	}

	virtual ~SandBox3DExample()
	{

	};
};

class SandBoxTest : public GameWorld::Application
{
public:
	SandBoxTest()
	{
		GAMEWORLD_WARN("Application is running on sandbox 3d example");
	};

	virtual void Init() override
	{
		Application::Init();

		glm::vec3 Pos = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::quat Rot = glm::vec3(0.0f, 0.0f, glm::radians(45.0f));
		glm::vec3 Sca = glm::vec3(1.0f, 2.0f, 3.0f);

		MTransform transform(Pos, Rot, Sca);

		glm::mat4 trans_mat = transform.ToTransformMat();
	}

	virtual ~SandBoxTest()
	{

	};
};

GameWorld::Application* GameWorld::GetApplication()
{
	return new SandBox3DExample();
}