#pragma once

/*
   Render Hardware API Interface Header File
*/

#include "glm/glm.hpp"
#include "RenderArray.h"

namespace GameWorld
{
	enum class RenderAPIType : GW_UINT8
	{
		kNone   = 0x0000,
		kOpenGl = 0x0001,
	};

	enum RenderDrawType : GW_UINT8
	{/* BeginMode */
		kPOINTS          =    0x0000,
		kLINES           =    0x0001,
		kLINE_LOOP       =    0x0002,
		kLINE_STRIP      =    0x0003,
		kTRIANGLES       =    0x0004,
		kTRIANGLE_STRIP  =    0x0005,
		kTRIANGLE_FAN    =    0x0006,
		kQUADS           =    0x0007,
		kQUAD_STRIP      =    0x0008,
		kPOLYGON         =    0x0009,
	};

	class RHI
	{
	public:
		virtual ~RHI() = default;

		virtual void Init() = 0;
		virtual void Init3DConfig() = 0;
		
		virtual void SetGamaCorrect(GW_BOOL bGama)   = 0;

		virtual void SetDepthTest(GW_BOOL bDepth)    = 0;
		virtual void SetDepthMask(GW_BOOL bWrite)    = 0;
		virtual void SetDepthFunc(ShaderCmpFunc cmp) = 0;

		virtual void SetCullFace(GW_BOOL bCull)      = 0;

		virtual void SetViewport(GW_UINT32 x, GW_UINT32 y, GW_UINT32 width, GW_UINT32 height) = 0;
		
		virtual void SetDrawMode(RenderDrawType draw_mode) = 0;

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



