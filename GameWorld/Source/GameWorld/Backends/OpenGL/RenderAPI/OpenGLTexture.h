#pragma once
#include "GameWorld/Texture/TextureBase.h"

namespace GameWorld
{
	class OpenGLTexture : public GTexture
	{
	public:
		OpenGLTexture(const std::string path, GW_BOOL bflip, GW_BOOL bgama);
		OpenGLTexture(const GImage& image, GW_BOOL bgama);
		OpenGLTexture(const std::array<std::string, 6> skybox_files, GW_BOOL bflip, GW_BOOL bgama);
		OpenGLTexture(const std::array<GImage, 6>& skybox_images, GW_BOOL bgama);

		virtual ~OpenGLTexture() override;

		virtual GW_UINT32 GetID()       const override { return texture_id_; };
		virtual ETextureType GetType()  const override { return texture_type_; };
		virtual GW_BOOL IsValid()       const override { return texture_type_ != ETextureType::kInValid; };

		virtual GW_INT32 GetWidth()     const override { return width_; };
		virtual GW_INT32 GetHeight()    const override { return height_; };
		virtual GW_INT32 GetChannel()   const override { return channels_; };

		virtual void Bind(GW_UINT32 slot = 0) const override;
		virtual void UnBind(GW_UINT32 slot = 0) const override;

	public:
		void DynamicLoadImage(const GImage& image, GW_BOOL bgama);
		void DynamicLoadSkybox(const std::array<GImage, 6>& skybox_images, GW_BOOL bgama);
		GW_BOOL GenMipmap();

	private:
		void LoadImage(const GImage& image, GW_BOOL bgama);
		void LoadSkybox(const std::array<GImage, 6>& skybox_images, GW_BOOL bgama);

	private:
		GW_INT32 width_;
		GW_INT32 height_;
		GW_INT32 channels_;
	};

}