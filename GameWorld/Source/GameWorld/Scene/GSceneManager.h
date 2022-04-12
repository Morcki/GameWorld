#pragma once

#include <string>

#include "GameWorld/Component/GObject.h"
#include "GameWorld/Material/GMaterial.h"
#include "GameWorld/Material/Light/GLight.h"
#include "GameWorld/Material/Skybox/GSkyboxComponent.h"

namespace GameWorld
{
	class GSceneManager
	{
	public:
		GSceneManager();
		GSceneManager(const std::string name);

		~GSceneManager();

	public:
		void Init();
		void TickUpdate();

	public:
		void PlaceDirecionalLight(const GDirectionalLight& light)    { m_directional_light = light; }
		void PlaceAmbientLight   (const GAmbientLight& light)        { m_ambient_light = light; }
		void PlaceSkybox         (const Ref<GSkyboxComponent>& skybox) { m_skybox = skybox; }
		void PlaceGameObject   (Ref<GObject> object)                 { m_gameobject_list.emplace_back(object); }

		GDirectionalLight GetDirectgionalLight() { return m_directional_light; };
		GAmbientLight     GetAmbientLight()      { return m_ambient_light; };
		

	private:
		inline static GW_INT32 s_num_of_scene_instance = 0;
		std::string m_name{ std::string("Scene_") + std::to_string(s_num_of_scene_instance++) };

		GDirectionalLight  m_directional_light{ GDirectionalLight() };
		GAmbientLight      m_ambient_light{ GAmbientLight() };

		Ref<GSkyboxComponent> m_skybox;
		std::vector<Ref<GObject>> m_gameobject_list;
	};
}