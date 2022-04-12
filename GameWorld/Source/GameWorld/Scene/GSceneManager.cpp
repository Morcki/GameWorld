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