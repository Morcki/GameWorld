#pragma once
#include "GObject.h"

#include <string>

#include "GameWorld/Core/math/MTransform.h"
#include "GameWorld/Material/GMaterial.h"

namespace GameWorld
{
	class GComponent : public GObject
	{
	public:
		GComponent() {};
		GComponent(const std::string& name)
			: m_name(name)
		{};
		virtual ~GComponent() {};

		virtual void TickUpdate() override {};
		inline const std::string& GetName() { return m_name; };

	public:
		MTransform GetTransform() { return m_transform; };
		GMaterial  GetMaterial() { return m_material; };

		void SetTransform(const MTransform& transform) { m_transform = transform; };
		void SetMaterial(const GMaterial& material) { m_material = material; };

	protected:

		inline static GW_INT32 s_num_component = 0;

		std::string m_name{ std::string("Component_") + std::to_string(s_num_component++) };

		MTransform m_transform{ MTransform() };
		GMaterial  m_material{ m_name };
	};
}