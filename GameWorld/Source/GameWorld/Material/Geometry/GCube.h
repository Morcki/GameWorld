#pragma once

#include "GameWorld/Component/GComponent.h"
#include "GameWorld/Core/math/MTransform.h"

#include "GameWorld/Render/RenderArray.h"
#include "GameWorld/Material/GMaterial.h"

#include "GameWorld/Material/Light/GLight.h"

namespace GameWorld
{
	class GCube : public GComponent
	{
	public:
		GCube();
		GCube(MTransform transform);
		virtual ~GCube();

	public:
		inline MTransform GetTransform() { return m_transform; };
		inline GMaterial  GetMaterial() { return m_material; };

		void SetTransform(const MTransform& transform) { m_transform = transform; };
		void SetMaterial(const GMaterial& material) { m_material = material; };
	private:
		virtual void Init();

	public:
		virtual void TickUpdate() override;

	private:
		inline static GW_INT32 s_num_cube_instance = 0;

		MTransform m_transform { MTransform() };
		GMaterial  m_material{ GMaterial(std::string("Cube_") + std::to_string(s_num_cube_instance++)) };

		Ref<RenderArray>   render_vao_;
		//Ref<GTexture>      render_texture_;
	};

}