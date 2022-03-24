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

		static void ResizeWindow(uint32_t width, uint32_t height);

	private:
		
	};

	class RenderPass
	{
	public:
		RenderPass(const Ref<ShaderBase>& shader_program)
			: shader_program_(shader_program)
		{};
		
		~RenderPass()
		{
			//shader_program_->UnlockShader();
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
		
		RenderPass& end(const Ref<RenderArray>& vertex_array) 
		{// will automatically call drawcall
			RenderBase::DrawCall(vertex_array);
			return *this;
		};

	private:
		Ref<ShaderBase> shader_program_;
	};


}

