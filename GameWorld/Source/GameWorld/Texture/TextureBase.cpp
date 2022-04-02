#include <PrecompiledHeader.h>
#include "TextureBase.h"

#include "GameWorld/Render/RHI.h"
#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLTexture.h"

namespace GameWorld
{
	GameWorld::Ref<GameWorld::GTexture> GTexture::CreateTexture2D(const std::string path, GW_BOOL bflip /*= true*/, GW_BOOL bgama /*= false*/)
	{
		switch (RHI::GetAPIType())
		{
		case RenderAPIType::kNone:break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLTexture>(path, bflip, bgama);
		}
		return nullptr;
	}

	GameWorld::Ref<GameWorld::GTexture> GTexture::CreateTexture2D(const GImage& image, GW_BOOL bgama /*= false*/)
	{
		switch (RHI::GetAPIType())
		{
		case RenderAPIType::kNone:break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLTexture>(image, bgama);
		}
		return nullptr;
	}

	GameWorld::Ref<GameWorld::GTexture> GTexture::CreateTextureCubeMap(const std::array<std::string, 6> skybox_files, GW_BOOL bflip /*= true*/, GW_BOOL bgama /*= false*/)
	{
		switch (RHI::GetAPIType())
		{
		case RenderAPIType::kNone:break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLTexture>(skybox_files, bflip, bgama);
		}
		return nullptr;
	}

	GameWorld::Ref<GameWorld::GTexture> GTexture::CreateTextureCubeMap(const std::array<GImage, 6>& skybox_images, GW_BOOL bgama /*= false*/)
	{
		switch (RHI::GetAPIType())
		{
		case RenderAPIType::kNone:break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLTexture>(skybox_images, bgama);
		}
		return nullptr;
	}

}