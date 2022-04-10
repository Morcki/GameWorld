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

	public:
		inline MTransform GetTransform() { return m_transform; };
		inline glm::vec4  GetColor    () { return m_color; };

		void SetTransform(const MTransform& transform) { m_transform = transform; };
		void SetColor    (const glm::vec4& color)      { m_color = color; };

	private:
		void Init();

	public:
		void TickUpdate(const Ref<GCamera>& camera);

	private:
		MTransform m_transform { MTransform() };

		glm::vec4 m_color { glm::vec4(1.0f, 0.5f, 0.0f, 1.0f) };

		Ref<ShaderBase>    render_shader_;
		Ref<RenderArray>   render_vao_;
		//Ref<GTexture>      render_texture_;
	};

}