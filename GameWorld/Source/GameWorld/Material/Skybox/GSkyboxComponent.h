#pragma once

#include <array>

#include "GameWorld/Component/GComponent.h"

#include "GameWorld/Render/ShaderBase.h"
#include "GameWorld/Texture/TextureBase.h"
#include "GameWorld/Render/RenderArray.h"

namespace GameWorld
{
	class GSkyboxComponent : public GComponent
	{
	public:
		GSkyboxComponent();
		GSkyboxComponent(const std::array<std::string, 6>& faces);
		~GSkyboxComponent();

		void SetTexture(GW_INT32 index_face, const std::string& image_path);
		void SetTexture(const std::array<std::string, 6>& faces);
		virtual void TickUpdate() override;

	private:
		void ResetShader();
		void ResetTexture();

	private:
		std::array<GImage, 6> skybox_textureinfo_;

		Ref<ShaderBase>    render_shader_;
		Ref<RenderArray>   render_vao_;
		Ref<GTexture>      render_texture_;

	};
}