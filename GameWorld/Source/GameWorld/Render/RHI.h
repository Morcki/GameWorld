#pragma once

/*
   Render Hardware API Interface Header File
*/

#include "glm/glm.hpp"
#include "RenderArray.h"

namespace GameWorld
{
	enum class RenderAPIType
	{
		NONE = 0,
		OPENGL = 1,
	};

	class RHI
	{
	public:
		virtual ~RHI() = default;

		virtual void SetClearColor(glm::vec4 color) = 0;
		virtual void ClearBuffer() = 0;

		virtual void DrawElements(const Ref<RenderArray>& vertexArray, GW_UINT32 indexCount = 0) = 0;

		static RenderAPIType GetAPIType() { return RenderAPI; }

		static Scope<RHI> CreateRHI();

	private:
		static RenderAPIType RenderAPI;
	};
}



