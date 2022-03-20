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

	void OpenGLRHI::DrawElements(const Ref<RenderArray>& vertex_array, GW_UINT32 index_count)
	{
		GW_UINT32 count = index_count ? index_count : vertex_array->GetIndexBuffer()->Count();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}