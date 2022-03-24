#include <PrecompiledHeader.h>

#include "RenderArray.h"

#include "RenderCore.h"
#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLRenderArray.h"

namespace GameWorld
{

	Ref<RenderArray> RenderArray::CreateRenderArray()
	{
		switch (RenderBase::GetRenderAPI())
		{
		case RenderAPIType::kNone   : break;
		case RenderAPIType::kOpenGl : return CreateRef<OpenGLRenderArray>();
		}
		GAMEWORLD_CORE_ASSERT(false, "Unknown Render API.");
		return nullptr;
	}

}