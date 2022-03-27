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

	void RenderBase::ResizeWindow(GW_UINT32 x, GW_UINT32 y, GW_UINT32 width, GW_UINT32 height)
	{
		RenderCommand::SetViewport(x, y, width, height);
	}

}