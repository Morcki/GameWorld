#pragma once

#include "GameWorld/Render/RHI.h"


namespace GameWorld
{

	class OpenGLRHI : public RHI
	{
	public:

		OpenGLRHI();
		virtual ~OpenGLRHI();

		virtual void SetClearColor(glm::vec4 color) override;
		virtual void ClearBuffer() override;

		virtual void DrawElements(const Ref<RenderArray>& vertexArray, GW_UINT32 indexCount = 0) override;
	};


}

