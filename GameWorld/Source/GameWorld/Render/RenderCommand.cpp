#include <PrecompiledHeader.h>

#include "RenderCommand.h"

namespace GameWorld
{
	
	Scope<RHI> RenderCommand::RenderHardwareAPI = RHI::CreateRHI();

}