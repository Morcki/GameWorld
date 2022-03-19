#include <PrecompiledHeader.h>

#include "OpenGLRHI.h"

#include "glad/glad.h"

namespace GameWorld
{
	OpenGLRHI::OpenGLRHI()
	{

	}

	OpenGLRHI::~OpenGLRHI()
	{

	}

	void OpenGLRHI::SetClearColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRHI::ClearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRHI::DrawElements(const Ref<RenderArray>& vertexArray, GW_UINT32 indexCount)
	{
		GW_UINT32 count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->Count();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}