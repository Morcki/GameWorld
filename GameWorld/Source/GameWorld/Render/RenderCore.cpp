#include <PrecompiledHeader.h>
#include "RenderCore.h"

#include "RenderCommand.h"

namespace GameWorld
{
	
	void RenderBase::ResizeWindow(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

}