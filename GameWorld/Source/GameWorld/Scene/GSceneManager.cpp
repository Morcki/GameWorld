#include <PrecompiledHeader.h>
#include "GSceneManager.h"

namespace GameWorld
{

	GSceneManager::GSceneManager()
	{

	}

	GSceneManager::GSceneManager(const std::string name)
		: m_name(name)
	{

	}

	GSceneManager::~GSceneManager()
	{

	}

	void GSceneManager::Init()
	{
		m_skybox = nullptr;
		m_directional_light.m_color = glm::vec3(1.0f);
		m_directional_light.m_direction = { 5.0f, -5.0f, -5.0f };

		m_ambient_light.m_irradiance = glm::vec3(0.2f);
	}

	void GSceneManager::TickUpdate()
	{
		if (m_skybox)
		{
			m_skybox->TickUpdate();
		}

		for (auto& object : m_gameobject_list)
		{
			object->TickUpdate();
		}
	}

}