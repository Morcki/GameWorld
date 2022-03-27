#pragma once

#include "GameWorld/Render/RHI.h"


namespace GameWorld
{

	class OpenGLRHI : public RHI
	{
	public:

		OpenGLRHI();
		virtual ~OpenGLRHI();

		virtual void Init() override;
		virtual void Init3DConfig() override;

		virtual void SetGamaCorrect(GW_BOOL bGama) override;

		virtual void SetDepthTest(GW_BOOL bDepth) override;
		virtual void SetDepthMask(GW_BOOL bWrite) override;
		virtual void SetDepthFunc(ShaderCmpFunc cmp) override;

		virtual void SetCullFace(GW_BOOL bCull) override;

		virtual void SetViewport(GW_UINT32 x, GW_UINT32 y, GW_UINT32 width, GW_UINT32 height) override;

		virtual void SetClearColor(glm::vec4 color) override;
		virtual void ClearBuffer() override;

		virtual void DrawElements(const Ref<RenderArray>& vertex_array, GW_UINT32 index_count = 0) override;
		virtual void DrawArrays(GW_UINT32 vert_count) override;
	};


}

