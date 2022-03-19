#include <PrecompiledHeader.h>

#include "RHI.h"
#include "RenderCore.h"
#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLRHI.h"

namespace GameWorld
{
	RenderAPIType RHI::RenderAPI = RenderAPIType::OPENGL;

	Scope<RHI> RHI::CreateRHI()
	{
		switch (RenderAPI)
		{
		case RenderAPIType::NONE:break;
		case RenderAPIType::OPENGL: return CreateScope<OpenGLRHI>();
		}
		GAMEWORLD_CORE_ASSERT(false, "Unkown Render API");
	}

}