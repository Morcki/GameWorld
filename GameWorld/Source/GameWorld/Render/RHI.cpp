#include <PrecompiledHeader.h>

#include "RHI.h"
#include "RenderCore.h"
#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLRHI.h"

namespace GameWorld
{
	RenderAPIType RHI::render_api_ = RenderAPIType::kOpenGl;

	RHI* RHI::CreateRHI()
	{
		switch (render_api_)
		{
		case RenderAPIType::kNone:   break;
		case RenderAPIType::kOpenGl: return new OpenGLRHI();
		}
		GAMEWORLD_CORE_ASSERT(false, "Unkown Render API");
		return nullptr;
	}

}