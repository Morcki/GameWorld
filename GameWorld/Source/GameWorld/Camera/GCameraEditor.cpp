#include <PrecompiledHeader.h>
#include "GCameraEditor.h"

#include "GameWorld/Input/InputSystem.h"
#include "GameWorld/Core/GTimeSystem.h"
#include "GameWorld/Events/MouseCodes.h"

namespace GameWorld
{
	GCameraEditor::GCameraEditor()
		: GCamera()
	{

	}

	GCameraEditor::GCameraEditor(CameraOptions opts)
		: GCamera(opts)
	{

	}

	void GCameraEditor::TickUpdate()
	{

	}

	void GCameraEditor::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCameraEditor::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCameraEditor::OnKeyReleased));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCameraEditor::OnMousePressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCameraEditor::OnMouseReleased));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCameraEditor::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCameraEditor::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCameraEditor::OnWindowResized));
	}

	GW_BOOL GCameraEditor::OnKeyPressed(KeyPressedEvent& e)
	{
		GW_FLOAT32 ts = GTimeSystem::GetInst().GetDeltaTime();
		GW_FLOAT32 velocity = move_speed * ts;

		switch (e.GetKeyCode())
		{
		case Key::W:
			opts_.position += opts_.front * velocity;
			break;
		case Key::S:
			opts_.position -= opts_.front * velocity;
			break;
		case Key::A:
			opts_.position -= opts_.right * velocity;
			break;
		case Key::D:
			opts_.position += opts_.right * velocity;
			break;
		default:
			return true;
			break;
		}

		UpdateViewMatrix();
		return false;
	}

	GW_BOOL GCameraEditor::OnKeyReleased(KeyReleasedEvent& e)
	{
		switch (e.GetKeyCode())
		{
		default:
			return true;
			break;
		}
		return false;
	}

	GW_BOOL GCameraEditor::OnMousePressed(MouseButtonPressedEvent& e)
	{
		switch (e.GetMouseButton())
		{
		case Mouse::ButtonRight:
			isMouseRightPressed = true;
			break;

		default:
			return true;
			break;
		}
		return false;
	}

	GW_BOOL GCameraEditor::OnMouseReleased(MouseButtonReleasedEvent& e)
	{
		switch (e.GetMouseButton())
		{
		case Mouse::ButtonRight:
			isMouseRightPressed = false;
			break;

		default:
			return true;
			break;
		}
		return false;
	}

	GW_BOOL GCameraEditor::OnMouseMoved(MouseMovedEvent& e)
	{
		if (!isMouseRightPressed) return true;

		opts_.yaw   += mouse_sensitive * InputSystem::GetMouseXOffset();
		opts_.pitch += mouse_sensitive * InputSystem::GetMouseYOffset();

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (isConstrainPitch)
		{
			if (opts_.pitch > 89.0f)
				opts_.pitch = 89.0f;
			if (opts_.pitch < -89.0f)
				opts_.pitch = -89.0f;
		}
		UpdateViewMatrix();
		return false;
	}

	GW_BOOL GCameraEditor::OnMouseScrolled(MouseScrolledEvent& e)
	{
		opts_.viewport_fov_y -= (float)e.GetYOffset();
		if (opts_.viewport_fov_y < 0.5f)
			opts_.viewport_fov_y = 0.5f;
		if (opts_.viewport_fov_y > 40.0f)
			opts_.viewport_fov_y = 40.0f;
		UpdateProjectionMatrix();
		return false;
	}

	GW_BOOL GCameraEditor::OnWindowResized(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) return true;
		UpdateViewportRatio((GW_FLOAT32)e.GetWidth(), (GW_FLOAT32)e.GetHeight());
		return false;
	}

}