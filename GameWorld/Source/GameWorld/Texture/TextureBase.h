#pragma once

#include <string>
#include <array>

#include "GameWorld/Core/Core.h"

#include "GImage.h"

namespace GameWorld
{
	enum ETextureType
	{
		kInValid,
		kTexture2D,
		kCubeMap
	};
	class GTexture
	{
	public:
		virtual ~GTexture() = default;

		virtual GW_UINT32     GetID()      const = 0;
		virtual ETextureType  GetType()    const = 0;
		virtual GW_BOOL       IsValid()    const = 0;

		virtual GW_INT32      GetWidth()   const = 0;
		virtual GW_INT32      GetHeight()  const = 0;
		virtual GW_INT32      GetChannel() const = 0;

		virtual void Bind(GW_UINT32 slot = 0)   const = 0;
		virtual void UnBind(GW_UINT32 slot = 0) const = 0;

	protected:
		ETextureType texture_type_{ ETextureType::kInValid };
		GW_UINT32    texture_id_{ 0 };

	public:
		static Ref<GTexture> CreateTexture2D(const std::string path, GW_BOOL bflip = true, GW_BOOL bgama = false);
		static Ref<GTexture> CreateTexture2D(const GImage& image, GW_BOOL bgama = false);
		static Ref<GTexture> CreateTextureCubeMap(const std::array<std::string, 6> skybox_files, GW_BOOL bflip = true, GW_BOOL bgama = false);
		static Ref<GTexture> CreateTextureCubeMap(const std::array<GImage, 6>& skybox_images, GW_BOOL bgama = false);

	};

}