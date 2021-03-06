#pragma once

#include "GameWorld/Component/GComponent.h"
#include "GameWorld/Core/math/MTransform.h"

#include "GameWorld/Render/RenderArray.h"
#include "GameWorld/Material/GMaterial.h"

namespace GameWorld
{
	class GCubeSingleton final : public GSingletonPublic<GCubeSingleton>
	{
	public:
		GCubeSingleton();
		virtual ~GCubeSingleton();

		void DrawCall();

	protected:
		Ref<RenderArray>   render_vao;
	};

	class GCubeInstance : public GComponent
	{
	public:
		GCubeInstance();
		GCubeInstance(MTransform transform);
		virtual ~GCubeInstance();

	private:
		virtual void Init();

	public:
		virtual void TickUpdate() override;

	private:
		inline static GW_INT32 s_num_cube_instance = 0;

		//Ref<GTexture>      render_texture_;
	};

}