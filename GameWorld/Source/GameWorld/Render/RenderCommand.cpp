#include <PrecompiledHeader.h>

#include "RenderCommand.h"

namespace GameWorld
{
	
	Scope<RHI> RenderCommand::RenderHardwareAPI = std::unique_ptr<RHI>(RHI::CreateRHI());

}