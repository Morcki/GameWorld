#include <PrecompiledHeader.h>

#include "OpenGLRHI.h"

#include "glad/glad.h"

namespace GameWorld
{
	static GLenum GetOpenGLDepthFunc(ShaderCmpFunc cmp)
	{
		return (GL_NEVER - ShaderCmpFunc::kNever) + cmp;
	};

	OpenGLRHI::OpenGLRHI()
	{

	}

	OpenGLRHI::~OpenGLRHI()
	{

	}

	void OpenGLRHI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRHI::Init3DConfig()
	{
		SetDepthTest(true);
		SetDepthFunc(ShaderCmpFunc::kLess);
	}

	void OpenGLRHI::SetGamaCorrect(GW_BOOL bGama)
	{
		//// 开启自动GAMA矫正
		bGama ? glEnable(GL_FRAMEBUFFER_SRGB) : glDisable(GL_FRAMEBUFFER_SRGB);
	}

	void OpenGLRHI::SetDepthTest(GW_BOOL bDepth)
	{
		bDepth ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRHI::SetDepthMask(GW_BOOL bWrite)
	{
		glDepthMask(bWrite);
	}

	void OpenGLRHI::SetDepthFunc(ShaderCmpFunc cmp)
	{
		glDepthFunc(GetOpenGLDepthFunc(cmp));
	}

	void OpenGLRHI::SetCullFace(GW_BOOL bCull)
	{
		if (bCull)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}

	void OpenGLRHI::SetViewport(GW_UINT32 x, GW_UINT32 y, GW_UINT32 width, GW_UINT32 height)
	{
		glViewport(x, y, width, height);
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
		glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRHI::DrawArrays(GW_UINT32 vert_count)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vert_count);
	}

}