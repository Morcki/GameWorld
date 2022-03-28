#include <PrecompiledHeader.h>
#include "TextureBase.h"

#include "GameWorld/Render/RHI.h"
#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLTexture.h"

namespace GameWorld
{
	TextureInfo::TextureInfo(const std::string& image_file)
	{
		LoadImgFile(image_file);
	}


	TextureInfo::~TextureInfo()
	{
		data ? stbi_image_free(data) : free(data);
	}

	GW_BOOL TextureInfo::LoadImgFile(const std::string& image_file)
	{
		if (image_file.empty()) return false;
		if (data)
		{
			stbi_image_free(data);
			data = nullptr;
		}

		data = stbi_load(image_file.c_str(), &width, &height, &channels, 0);

		if (!data)
		{
			GAMEWORLD_CORE_ERROR("Failed to load image file : {0}", image_file);
			return false;
		}

		return true;
	}

	GameWorld::Ref<GameWorld::Texture2D> Texture2D::CreateTexture2D(const std::string& path)
	{
		switch (RHI::GetAPIType())
		{
		case RenderAPIType::kNone:break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLTexture2D>(path);
		}
		return nullptr;
	}

	GameWorld::Ref<GameWorld::TextureCube3D> TextureCube3D::CreateTextureCube3D(const std::array<TextureInfo, 6>& faces)
	{
		switch (RHI::GetAPIType())
		{
		case RenderAPIType::kNone:break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLTextureCube3D>(faces);
		}
		return nullptr;
	}

	

}