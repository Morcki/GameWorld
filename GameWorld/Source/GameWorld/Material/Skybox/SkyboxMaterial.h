#pragma once

#include <array>

#include "GameWorld/Render/ShaderBase.h"
#include "GameWorld/Texture/TextureBase.h"
#include "GameWorld/Render/RenderArray.h"
#include "GameWorld/Camera/GCamera.h"

namespace GameWorld
{
	class SkyboxMaterial
	{
	public:
		SkyboxMaterial();
		SkyboxMaterial(const std::array<std::string, 6>& faces);
		~SkyboxMaterial();

		void SetTexture(GW_INT32 index_face, const std::string& image_path);
		void SetTexture(const std::array<std::string, 6>& faces);
		void TickUpdate(const Ref<GCamera>& camera);

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