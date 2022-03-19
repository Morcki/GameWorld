#include <PrecompiledHeader.h>
#include "RenderBuffer.h"

#include "RenderCore.h"

#include "GameWorld/Backends/OpenGL/RenderAPI/OpenGLRenderBuffer.h"

namespace GameWorld
{

	VertexBuffer* VertexBuffer::CreateVertexBuffer(GW_FLOAT32* buff, GW_UINT32 size)
	{
		switch (RenderBase::GetRenderAPI())
		{
		case RenderAPIType::NONE: break;
		case RenderAPIType::OPENGL: return new OpenGLVertexBuffer(buff, size);
		}
		GAMEWORLD_CORE_ASSERT(false, "No Supported Render API Finded!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::CreateIndexBuffer(GW_UINT32* buff, GW_UINT32 count)
	{
		switch (RenderBase::GetRenderAPI())
		{
		case RenderAPIType::NONE: break;
		case RenderAPIType::OPENGL: return new OpenGLIndexBuffer(buff, count);
		}
		GAMEWORLD_CORE_ASSERT(false, "No Supported Render API Finded!");
		return nullptr;
	}
}