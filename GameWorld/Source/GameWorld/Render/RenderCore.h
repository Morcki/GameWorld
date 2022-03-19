#pragma once

#include "RHI.h"

namespace GameWorld
{

	class RenderBase
	{
	public:
		inline static RenderAPIType GetRenderAPI() { return RHI::GetAPIType(); };
	private:
		
	};

}

