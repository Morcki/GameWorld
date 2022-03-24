#include <PrecompiledHeader.h>

#include "ShaderBase.h"

#include "RenderCore.h"
#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLShader.h"

namespace GameWorld
{
	Ref<ShaderBase> ShaderBase::CreateShaderBase()
	{
		switch (RenderBase::GetRenderAPI())
		{
		case RenderAPIType::kNone: break;
		case RenderAPIType::kOpenGl: return CreateRef<OpenGLShader>();
		}
		GAMEWORLD_CORE_ASSERT(false, "Unkown Rendering API Type");
		return nullptr;
	}
}

