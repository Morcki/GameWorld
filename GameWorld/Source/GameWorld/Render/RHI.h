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
		kNone   = 0,
		kOpenGl = 1,
	};

	class RHI
	{
	public:
		virtual ~RHI() = default;

		virtual void Init() = 0;
		virtual void Init3DConfig() = 0;
		
		virtual void SetDepthMask(GW_BOOL bWrite) = 0;
		virtual void SetDepthFunc(ShaderCmpFunc cmp) = 0;

		virtual void SetViewport(GW_UINT32 x, GW_UINT32 y, GW_UINT32 width, GW_UINT32 height) = 0;

		virtual void SetClearColor(glm::vec4 color) = 0;
		virtual void ClearBuffer() = 0;

		virtual void DrawElements(const Ref<RenderArray>& vertex_array, GW_UINT32 index_count = 0) = 0;
		virtual void DrawArrays(GW_UINT32 vert_count) = 0;

		static RenderAPIType GetAPIType() { return render_api_; }

		static Scope<RHI> CreateRHI();

	private:
		static RenderAPIType render_api_;
	};
}



