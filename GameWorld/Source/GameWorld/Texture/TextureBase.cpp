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
	}

}