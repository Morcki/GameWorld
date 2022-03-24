#include <PrecompiledHeader.h>
#include "RenderCore.h"

#include "RenderCommand.h"
#include "RenderArray.h"
#include "ShaderBase.h"

namespace GameWorld
{
	
	void RenderBase::Init()
	{
		RenderCommand::Init();
	}

	void RenderBase::DrawCall(const Ref<RenderArray>& vertex_buffer)
	{
		RenderCommand::DrawElements(vertex_buffer);
	}

	void RenderBase::ResizeWindow(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

}