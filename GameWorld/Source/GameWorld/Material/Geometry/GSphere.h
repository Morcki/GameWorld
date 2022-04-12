#pragma once

#include "GameWorld/Component/GComponent.h"
#include "GameWorld/Core/math/MTransform.h"

#include "GameWorld/Render/RenderArray.h"
#include "GameWorld/Material/GMaterial.h"

namespace GameWorld
{
	class GSphereSingleton final : public GSingletonPublic<GSphereSingleton>
	{
	public:
		GSphereSingleton();
		virtual ~GSphereSingleton();

		void DrawCall();

	protected:
		Ref<RenderArray>   render_vao;
	};

	class GSphereInstance : public GComponent
	{
	public:
		GSphereInstance();
		GSphereInstance(MTransform transform);
		virtual ~GSphereInstance();

	private:
		virtual void Init();

	public:
		virtual void TickUpdate() override;

	private:
		inline static GW_INT32 s_num_sphere_instance = 0;

	};
}