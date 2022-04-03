#pragma once

#include "GameWorld/Core/Timestep.h"
#include "GameWorld/Events/Event.h"
#include "GameWorld/Events/MouseEvent.h"
#include "GameWorld/Events/ApplicationEvent.h"
#include "GameWorld/Events/KeyEvent.h"
#include "CameraOrtho.h"
#include "CameraPersp.h"

namespace GameWorld
{
	class Camera2DOrthoController
	{
	public:
		[[deprecated("Will Deprecated soon,Use GCamera2D instead.")]]
		Camera2DOrthoController(GW_FLOAT32 aspect_ratio, GW_BOOL b_rotation = false);

		void TickUpdate();
		void OnEvent(Event& e);

		void OnResize(GW_FLOAT32 width, GW_FLOAT32 height);

		Camera2DOrtho& GetCamera() { return camera_2d_ortho_; }
		const Camera2DOrtho& GetCamera() const { return camera_2d_ortho_; }

		GW_FLOAT32 GetZoomLevel() const { return zoom_; }
		void SetZoomLevel(GW_FLOAT32 zoom) { zoom_ = zoom; }

	private:
		GW_BOOL OnKeyPressed(KeyPressedEvent& e);
		GW_BOOL OnMouseLeftPressed(MouseButtonPressedEvent& e);
		GW_BOOL OnMouseMoved(MouseMovedEvent& e);
		GW_BOOL OnMouseScrolled(MouseScrolledEvent& e);
		GW_BOOL OnWindowResized(WindowResizeEvent& e);

	private:
		GW_FLOAT32 aspect_ratio_;
		GW_FLOAT32 zoom_{ 1.0f };
		Camera2DOrtho camera_2d_ortho_;

		bool b_rotation_;
		GW_FLOAT32 translation_speed_{ 5.0f };
		GW_FLOAT32 rotation_speed_{ 180.0f };
		glm::vec2 mouse_press_pos_;
	};
	
	class CameraPerspController
	{
	public:
		[[deprecated("Will Deprecated soon,Use GCamera instead.")]]
		CameraPerspController(GW_BOOL b_constrain_pitch = true);

		void TickUpdate();
		void OnEvent(Event& e);

		CameraPersp& GetCamera() { return camera_; }
		const CameraPersp& GetCamera() const { return camera_; }

	private:
		GW_BOOL OnKeyPressed(KeyPressedEvent& e);
		GW_BOOL OnMouseMoved(MouseMovedEvent& e);
		GW_BOOL OnMouseScrolled(MouseScrolledEvent& e);
		GW_BOOL OnWindowResized(WindowResizeEvent& e);

	private:
		GW_BOOL b_constrain_pitch_ = true;

		GW_FLOAT32 aspect_ratio_;
		CameraPersp camera_;

		// camera options
		GW_FLOAT32 move_speed_{ 2.5f };
		GW_FLOAT32 mouse_sensitive_{ 0.35f };
	};
}