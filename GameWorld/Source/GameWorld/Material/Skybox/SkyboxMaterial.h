#pragma once

#include <array>

#include "GameWorld/Render/RenderCore.h"

#include "GameWorld/Render/ShaderBase.h"
#include "GameWorld/Render/RenderArray.h"
#include "GameWorld/Texture/TextureBase.h"

#include "GameWorld/Camera/CameraController.h"
#include "GameWorld/Texture/TextureBase.h"

namespace GameWorld
{
	class SkyboxMaterial
	{
	public:
		SkyboxMaterial(const Ref<CameraPerspController>& camera);
		SkyboxMaterial(const Ref<CameraPerspController>& camera, const std::array<std::string, 6>& faces);
		~SkyboxMaterial();

		void SetTexture(GW_INT32 index_face, const std::string& image_path);
		void SetTexture(const std::array<std::string, 6>& faces);
		void TickUpdate();

	private:
		void ResetShader();
		void ResetTexture();

	private:
		std::array<TextureInfo, 6> skybox_textureinfo_;

		Ref<ShaderBase>    render_shader_;
		Ref<RenderArray>   render_vao_;
		Ref<TextureCube3D> render_texture_;

		Ref<CameraPerspController> camera_;
	};
}