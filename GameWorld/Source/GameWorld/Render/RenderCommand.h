#pragma once

#include "glm/glm.hpp"
#include "RHI.h"

namespace GameWorld
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			RenderHardwareAPI->Init();
		}

		inline static void Init3DConfig()
		{
			RenderHardwareAPI->Init3DConfig();
		}

		inline static void SetViewport(GW_UINT32 x, GW_UINT32 y, GW_UINT32 width, GW_UINT32 height)
		{
			RenderHardwareAPI->SetViewport(x, y, width, height);
		}

		inline static void ClearColor(glm::vec4 color) 
		{ 
			RenderHardwareAPI->SetClearColor(color); 
		};
		
		inline static void ClearBuffer() 
		{ 
			RenderHardwareAPI->ClearBuffer(); 
		};

		inline static void SetGamaCorrect(GW_BOOL bGama)
		{
			RenderHardwareAPI->SetGamaCorrect(bGama);
		}
		
		inline static void SetDepthTest(GW_BOOL bDepth)
		{
			RenderHardwareAPI->SetDepthTest(bDepth);
		}

		inline static void SetDepthMask(GW_BOOL bWrite)
		{
			RenderHardwareAPI->SetDepthMask(bWrite);
		}

		inline static void SetDepthFunc(ShaderCmpFunc cmp)
		{
			RenderHardwareAPI->SetDepthFunc(cmp);
		}

		inline static void SetCullFace(GW_BOOL bCull)
		{
			RenderHardwareAPI->SetCullFace(bCull);
		}

		inline static void DrawArrays(GW_UINT32 vert_count)
		{
			RenderHardwareAPI->DrawArrays(vert_count);
		}

		inline static void DrawElements(const Ref<RenderArray>& vertexArray, GW_UINT32 indexCount = 0)
		{ 
			RenderHardwareAPI->DrawElements(vertexArray, indexCount); 
		};
		
	private:
		static Scope<RHI> RenderHardwareAPI;
	};

}