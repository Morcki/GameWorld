#pragma once

#include <string>
#include <array>

#include "stb_image.h"
#include "GameWorld/Core/Core.h"

namespace GameWorld
{
	class TextureInfo 
	{
	public:
		TextureInfo() {};
		TextureInfo(const std::string& image_file);
		~TextureInfo();

		GW_BOOL LoadImgFile(const std::string& image_file);
		
	public:
		GW_UINT8* data{ nullptr };
		GW_INT32  width{ 0 };
		GW_INT32  height{ 0 };
		GW_INT32  channels{ 0 };
		
	};

	class TextureBase
	{
	public:
		virtual ~TextureBase() = default;

		virtual GW_INT32 GetWidth()  const = 0;
		virtual GW_INT32 GetHeight() const = 0;

		virtual void Attach(GW_UINT32 slot = 0) const = 0;

	};

	class Texture2D : public TextureBase
	{
	public:
		static Ref<Texture2D> CreateTexture2D(const std::string& path);
	};

	class TextureCube3D : public TextureBase
	{
	public:
		static Ref<TextureCube3D> CreateTextureCube3D(const std::array<TextureInfo, 6>& faces);
	};
}