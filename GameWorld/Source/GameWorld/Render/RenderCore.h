#pragma once

#include "RHI.h"

namespace GameWorld
{

	class RenderBase
	{
	public:
		inline static RenderAPIType GetRenderAPI() { return RHI::GetAPIType(); };

		static void ResizeWindow(uint32_t width, uint32_t height);

	private:
		
	};

}

