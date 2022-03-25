#pragma once
#include "GameWorld/Layer/Layer.h"

#include "GameWorld/Events/ApplicationEvent.h"
#include "GameWorld/Events/MouseEvent.h"
#include "GameWorld/Events/KeyEvent.h"
namespace GameWorld
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual	void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

		void RenderTickBegin();
		void RenderTickEnd();
		void SetDarkThemeColors();

		inline void SetLayerBlockEvent(GW_BOOL b_block) { b_blockevent_ = b_block; };

	private:
		
		GW_FLOAT32 last_ticktime_ = 0.0f;
		GW_BOOL b_blockevent_ = false;
	};
}

