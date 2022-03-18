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
		virtual	void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& event) override;

		void RenderTickBegin();
		void RenderTickEnd();
		void SetDarkThemeColors();

		inline void SetLayerBlockEvent(GW_BOOL bBlock) { bBlockEvent = bBlock; };

	private:
		
		GW_FLOAT32 LastTickTime = 0.0f;
		GW_BOOL bBlockEvent = false;
	};
}

