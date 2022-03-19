#pragma once

#include "glm/glm.hpp"
#include "RHI.h"

namespace GameWorld
{
	class RenderCommand
	{
	public:
		inline static void ClearColor(glm::vec4 color) { RenderHardwareAPI->SetClearColor(color); };
		inline static void ClearBuffer() { RenderHardwareAPI->ClearBuffer(); };

		inline static void DrawElements(const Ref<RenderArray>& vertexArray, GW_UINT32 indexCount = 0) { RenderHardwareAPI->DrawElements(vertexArray, indexCount); };
		
	private:
		static Scope<RHI> RenderHardwareAPI;
	};

}