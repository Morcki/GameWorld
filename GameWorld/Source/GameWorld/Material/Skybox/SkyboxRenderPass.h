#pragma once

#include <array>

#include "GameWorld/Render/RenderCore.h"

#include "GameWorld/Render/ShaderBase.h"
#include "GameWorld/Render/RenderArray.h"
#include "GameWorld/Texture/TextureBase.h"

#include "GameWorld/Camera/CameraController.h"

namespace GameWorld
{
	class SkyboxRenderPass
	{
	public:
		SkyboxRenderPass(const Ref<CameraPerspController>& camera);
		SkyboxRenderPass(const Ref<CameraPerspController>& camera, const std::array<std::string, 6>& faces);
		~SkyboxRenderPass();

		void SetTexture(GW_INT32 index_face, const std::string& texture_path);
		void SetTexture(const std::array<std::string, 6>& faces);
		void TickUpdate();

	private:
		void ResetShader();
		void ResetTexture();

	private:
		std::array<std::string, 6> skybox_faces_;

		Ref<ShaderBase>    render_shader_;
		Ref<RenderArray>   render_vao_;
		Ref<TextureCube3D> render_texture_;

		Ref<CameraPerspController> camera_;
	};
}