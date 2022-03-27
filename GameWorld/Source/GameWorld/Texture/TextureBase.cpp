#include <PrecompiledHeader.h>
#include "TextureBase.h"

#include "GameWorld/Render/RHI.h"
#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLTexture.h"

namespace GameWorld
{

	GameWorld::Ref<GameWorld::Texture2D> Texture2D::CreateTexture2D(const std::string& path)
	{
		switch (RHI::GetAPIType())
		{
		case RenderAPIType::kNone:break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLTexture2D>(path);
		}
		return nullptr;
	}

	GameWorld::Ref<GameWorld::TextureCube3D> TextureCube3D::CreateTextureCube3D(const std::array<std::string, 6>& faces)
	{
		switch (RHI::GetAPIType())
		{
		case RenderAPIType::kNone:break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLTextureCube3D>(faces);
		}
		return nullptr;
	}

}