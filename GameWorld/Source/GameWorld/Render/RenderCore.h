#pragma once

#include "RHI.h"
#include "ShaderBase.h"
#include "RenderArray.h"

namespace GameWorld
{

	class RenderBase
	{
	public:
		inline static RenderAPIType GetRenderAPI() { return RHI::GetAPIType(); };

		static void Init();

		static void DrawCall(const Ref<RenderArray>& vertex_buffer);

		static void ResizeWindow(GW_UINT32 x, GW_UINT32 y, GW_UINT32 width, GW_UINT32 height);

	private:
		
	};

	class RenderPass
	{
	public:
		RenderPass(const Ref<ShaderBase>& shader_program)
			: shader_program_(shader_program)
		{};
		
		virtual ~RenderPass()
		{
			shader_program_->UnlockShader();
		}

		RenderPass& begin()
		{
			shader_program_->LockShader();
			return *this;
		};

		template <typename Functor>
		RenderPass& next(Functor functor)
		{
			functor();
			return *this;
		};
		
		RenderPass& draw(const Ref<RenderArray>& vertex_array)
		{// drawcall
			RenderBase::DrawCall(vertex_array);
			return *this;
		};
		
		RenderPass& end()
		{
			return *this;
		};

		template <typename Functor>
		RenderPass& end(Functor functor)
		{// post-process
			functor();
			return *this;
		};		

	private:
		Ref<ShaderBase> shader_program_;
	};


}

