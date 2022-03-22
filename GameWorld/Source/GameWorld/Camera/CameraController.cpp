#include <PrecompiledHeader.h>
#include "CameraController.h"

#include "GameWorld/Application.h"
#include "GameWorld/Input/InputSystem.h"

namespace GameWorld
{
	Camera2DOrthoController::Camera2DOrthoController(GW_FLOAT32 aspect_ratio, GW_BOOL b_rotation)
		: aspect_ratio_(aspect_ratio), camera_2d_ortho_(-aspect_ratio * zoom_, aspect_ratio * zoom_, -zoom_, zoom_), b_rotation_(b_rotation)
	{
	}

	void Camera2DOrthoController::TickUpdate(Timestep ts)
	{
		glm::vec3 camera_position = camera_2d_ortho_.GetPosition();
		GW_FLOAT32 camera_rotation = camera_2d_ortho_.GetRotation();
		if (InputSystem::IsKeyPressed(Key::A))
		{
			camera_position.x -= cos(glm::radians(camera_rotation)) * translation_speed_ * ts;
			camera_position.y -= sin(glm::radians(camera_rotation)) * translation_speed_ * ts;
		}
		else if (InputSystem::IsKeyPressed(Key::D))
		{
			camera_position.x += cos(glm::radians(camera_rotation)) * translation_speed_ * ts;
			camera_position.y += sin(glm::radians(camera_rotation)) * translation_speed_ * ts;
		}

		if (InputSystem::IsKeyPressed(Key::W))
		{
			camera_position.x += -sin(glm::radians(camera_rotation)) * translation_speed_ * ts;
			camera_position.y += cos(glm::radians(camera_rotation)) * translation_speed_ * ts;
		}
		else if (InputSystem::IsKeyPressed(Key::S))
		{
			camera_position.x -= -sin(glm::radians(camera_rotation)) * translation_speed_ * ts;
			camera_position.y -= cos(glm::radians(camera_rotation)) * translation_speed_ * ts;
		}

		if (b_rotation_)
		{
			if (InputSystem::IsKeyPressed(Key::Q))
				camera_rotation += rotation_speed_ * ts;
			if (InputSystem::IsKeyPressed(Key::E))
				camera_rotation -= rotation_speed_ * ts;

			if (camera_rotation > 180.0f)
				camera_rotation -= 360.0f;
			else if (camera_rotation <= -180.0f)
				camera_rotation += 360.0f;

			camera_2d_ortho_.SetRotation(camera_rotation);
		}

		camera_2d_ortho_.SetPosition(camera_position);

		translation_speed_ = zoom_;

		glm::vec2 mouse_pos_ = InputSystem::GetMousePosition();
	}

	void Camera2DOrthoController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Camera2DOrthoController::OnMouseLeftPressed));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Camera2DOrthoController::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Camera2DOrthoController::OnMouseScrolled));
		//dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_CALLBACK_FUNCTRION(Camera2DOrthoController::OnWindowResized));
	}

	void Camera2DOrthoController::OnResize(GW_FLOAT32 width, GW_FLOAT32 height)
	{
		aspect_ratio_ = width / height;
		camera_2d_ortho_.SetProjection(-aspect_ratio_ * zoom_, aspect_ratio_ * zoom_, -zoom_, zoom_);
	}

	GW_BOOL Camera2DOrthoController::OnMouseLeftPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			mouse_press_pos_ = InputSystem::GetMousePosition();
			return false;
		}
		return true;
	}

	GW_BOOL Camera2DOrthoController::OnMouseMoved(MouseMovedEvent& e)
	{
		if (InputSystem::IsMouseButtonPressed(Mouse::ButtonLeft))
		{
			GW_FLOAT32 mouse_sensitivity = 2 * zoom_;
			glm::vec3 camera_pos = camera_2d_ortho_.GetPosition();
			glm::vec2 window_resolution = Application::GetInst().GetWindow().GetResolution();
			camera_pos.x -= mouse_sensitivity * (e.GetX() - mouse_press_pos_.x) * window_resolution.x;
			camera_pos.y -= mouse_sensitivity * (mouse_press_pos_.y - e.GetY()) * window_resolution.y;
			camera_2d_ortho_.SetPosition(camera_pos);
			mouse_press_pos_ = { e.GetX() , e.GetY() };
			return false;
		}
		return true;
	}

	GW_BOOL Camera2DOrthoController::OnMouseScrolled(MouseScrolledEvent& e)
	{

		zoom_ -= e.GetYOffset() * 0.25f;
		zoom_ = std::max(zoom_, 0.25f);
		camera_2d_ortho_.SetProjection(-aspect_ratio_ * zoom_, aspect_ratio_ * zoom_, -zoom_, zoom_);
		return false;
	}

	GW_BOOL Camera2DOrthoController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((GW_FLOAT32)e.GetWidth(), (GW_FLOAT32)e.GetHeight());
		return false;
	}
}