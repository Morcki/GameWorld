#pragma once
#include "GCamera.h"

namespace GameWorld
{
	class GCameraEditor : public GCamera
	{
	public:
		GCameraEditor();
		GCameraEditor(CameraOptions opts);
		virtual ~GCameraEditor() {};

	public:
		GW_BOOL isConstrainPitch{ true };
		// camera options
		GW_FLOAT32 move_speed{ 2.5f };
		GW_FLOAT32 mouse_sensitive{ 0.35f };

	public: /* Handle Event System */
		virtual void TickUpdate()                                    override;
		virtual void OnEvent(Event& e)                               override;

		virtual GW_BOOL OnKeyPressed(KeyPressedEvent& e)             override;
		virtual GW_BOOL OnKeyReleased(KeyReleasedEvent& e)           override;
		virtual GW_BOOL OnMousePressed(MouseButtonPressedEvent& e)   override;
		virtual GW_BOOL OnMouseReleased(MouseButtonReleasedEvent& e) override;
		virtual GW_BOOL OnMouseMoved(MouseMovedEvent& e)             override;
		virtual GW_BOOL OnMouseScrolled(MouseScrolledEvent& e)       override;
		virtual GW_BOOL OnWindowResized(WindowResizeEvent& e)        override;

	private:
		GW_BOOL isMouseRightPressed { false };
	};

}
