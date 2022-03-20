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

		virtual void DrawElements(const Ref<RenderArray>& vertex_array, GW_UINT32 index_count = 0) override;
	};


}

