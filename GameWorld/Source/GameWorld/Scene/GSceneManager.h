#pragma once

#include <string>

#include "GameWorld/Component/GObject.h"
#include "GameWorld/Material/GMaterial.h"
#include "GameWorld/Material/Light/GLight.h"
#include "GameWorld/Material/Skybox/SkyboxMaterial.h"

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
		void SetDirecionalLight(const GDirectionalLight& light)    { m_directional_light = light; }
		void SetAmbientLight   (const GAmbientLight& light)        { m_ambient_light = light; }
		void SetSkybox         (const Ref<SkyboxMaterial>& skybox) { m_skybox = skybox; }
		void PlaceGameObject   (Ref<GObject> object)               { m_gameobject_list.emplace_back(object); }

		GDirectionalLight GetDirectgionalLight() { return m_directional_light; };
		GAmbientLight     GetAmbientLight()      { return m_ambient_light; };
		

	private:
		inline static GW_INT32 s_num_of_scene_instance = 0;
		std::string m_name{ std::string("Scene_") + std::to_string(s_num_of_scene_instance++) };

		GDirectionalLight  m_directional_light;
		GAmbientLight      m_ambient_light;

		Ref<SkyboxMaterial> m_skybox;
		std::vector<Ref<GObject>> m_gameobject_list;
	};
}