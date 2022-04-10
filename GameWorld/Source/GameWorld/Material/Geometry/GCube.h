#pragma once

#include "GameWorld/Core/math/MTransform.h"

#include "GameWorld/Render/ShaderBase.h"
#include "GameWorld/Render/RenderArray.h"

#include "GameWorld/Camera/GCamera.h"

namespace GameWorld
{
	class GCube
	{
	public:
		GCube();
		GCube(MTransform transform);
		virtual ~GCube();

	private:
		void Init();

	public:
		void TickUpdate(const Ref<GCamera>& camera);

	private:
		MTransform m_transform{ MTransform() };

		Ref<ShaderBase>    render_shader_;
		Ref<RenderArray>   render_vao_;
		//Ref<GTexture>      render_texture_;
	};

}