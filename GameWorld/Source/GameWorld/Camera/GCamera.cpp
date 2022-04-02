#include <PrecompiledHeader.h>
#include "GCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GameWorld/Core/Timestep.h"
#include "GameWorld/Input/InputSystem.h"
#include "GameWorld/Application.h"

namespace GameWorld
{
	/*
		Camera 3D Scope
	*/

	GCamera::GCamera()
	{
		UpdateViewMatrix();
		UpdateProjectionMatrix();
	}

	GCamera::~GCamera()
	{

	}

	void GCamera::TickUpdate()
	{

	}

	void GCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCamera::OnKeyPressed));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCamera::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCamera::OnMouseScrolled));
	}

	GW_BOOL GCamera::OnKeyPressed(KeyPressedEvent& e)
	{
		GW_FLOAT32 ts = Timestep::GetDeltaTime();
		GW_FLOAT32 velocity = move_speed * ts;
		if (InputSystem::IsKeyPressed(Key::W))
		{
			position_ += right_ * velocity;
		}
		else if (InputSystem::IsKeyPressed(Key::S))
		{
			position_ -= right_ * velocity;
		}
		else if (InputSystem::IsKeyPressed(Key::A))
		{
			position_ -= right_ * velocity;
		}
		else if (InputSystem::IsKeyPressed(Key::D))
		{
			position_ += right_ * velocity;
		}
		else
		{
			return true;
		}
		UpdateViewMatrix();
		return false;
	}

	GW_BOOL GCamera::OnMouseMoved(MouseMovedEvent& e)
	{

		yaw_ += mouse_sensitive * InputSystem::GetMouseXOffset();
		pitch_ += mouse_sensitive * InputSystem::GetMouseYOffset();

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (isConstrainPitch)
		{
			if (pitch_ > 89.0f)
				pitch_ = 89.0f;
			if (pitch_ < -89.0f)
				pitch_ = -89.0f;
		}
		UpdateViewMatrix();
		return false;
	}

	GW_BOOL GCamera::OnMouseScrolled(MouseScrolledEvent& e)
	{
		viewport_fov_y_ -= (float)e.GetYOffset();
		if (viewport_fov_y_ < 1.0f)
			viewport_fov_y_ = 1.0f;
		if (viewport_fov_y_ > 45.0f)
			viewport_fov_y_ = 45.0f;
		UpdateProjectionMatrix();
		return false;
	}

	GW_BOOL GCamera::OnWindowResized(WindowResizeEvent& e)
	{
		UpdateViewportRatio((GW_FLOAT32)e.GetWidth(), (GW_FLOAT32)e.GetHeight());
		return false;
	}

	void GCamera::UpdateProjectionMode(EProjectionMode pmode)
	{
		projection_mode_ = pmode;
		UpdateProjectionMatrix();
	}

	void GCamera::UpdateState(const glm::vec3& position)
	{
		position_ = position;
		UpdateViewMatrix();
	}

	void GCamera::UpdateState(GW_FLOAT32 yaw, GW_FLOAT32 pitch)
	{
		yaw_ = yaw;
		pitch_ = pitch;
		UpdateViewMatrix();
	}

	void GCamera::UpdateState(const glm::vec3& position, GW_FLOAT32 yaw, GW_FLOAT32 pitch)
	{
		position_ = position;
		yaw_ = yaw;
		pitch_ = pitch;
		UpdateViewMatrix();
	}

	void GCamera::UpdateViewMatrix()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front.y = sin(glm::radians(pitch_));
		front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front_ = glm::normalize(front);
		// also re-calculate the Right and Up vector
		// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		right_ = glm::normalize(glm::cross(front_, world_up_)); 
		v_mat_ = glm::lookAt(position_, position_ + front_, glm::normalize(glm::cross(right_, front_)));
		vp_mat_ = p_mat_ * v_mat_;
	}

	void GCamera::UpdateProjectionMatrix()
	{
		GW_FLOAT32 half_width;
		GW_FLOAT32 half_height;
		switch (projection_mode_)
		{
		case EProjectionMode::kPerspective:
			p_mat_ = glm::perspective(glm::radians(viewport_fov_y_), viewport_ratio_, znear_, zfar_);
			
			break;
		case EProjectionMode::kOrtho:
			half_height = viewport_fov_y_ * 0.5f;
			half_width = half_height * viewport_ratio_;
			p_mat_ = glm::ortho(-half_width, half_width,
									-half_height, half_height,
										znear_, zfar_);
			break;
		default:
			p_mat_ = glm::mat4(1.0f);
			break;
		}
		vp_mat_ = p_mat_ * v_mat_;
	}

	/*
		Camera 2D Scope
	*/

	static void GetLocalCameraPoseVector(GCamera2D::EProjectionAxis axis, glm::vec3& front, glm::vec3& up)
	{
		switch (axis)
		{
		case GameWorld::GCamera2D::kAxisXpos:
			front = { 1.0f, 0.0f, 0.0f };
			up = { 0.0f, 1.0f, 0.0f };
			break;
		case GameWorld::GCamera2D::kAxisXneg:
			front = { -1.0f, 0.0f, 0.0f };
			up = { 0.0f, 1.0f, 0.0f };
			break;
		case GameWorld::GCamera2D::kAxisYpos:
			front = { 0.0f, 1.0f, 0.0f };
			up = { 0.0f, 0.0f, -1.0f };
			break;
		case GameWorld::GCamera2D::kAxisYneg:
			front = { 0.0f, -1.0f, 0.0f };
			up = { 0.0f, 0.0f, 1.0f };
			break;
		case GameWorld::GCamera2D::kAxisZpos:
			front = { 0.0f, 0.0f, 1.0f };
			up = { 0.0f, 1.0f, 0.0f };
			break;
		case GameWorld::GCamera2D::kAxisZneg:
			front = { 0.0f, 0.0f, -1.0f };
			up = { 0.0f, 1.0f, 0.0f };
			break;
		default:
			GAMEWORLD_CORE_ASSERT(false, "Invalid Projection Axis Type!");
			break;
		}
	}

	static void GetLocalXY(GCamera2D::EProjectionAxis axis, 
								GW_INT32& x_index, GW_INT32& y_index, 
								GW_INT32& x_sign, GW_INT32& y_sign)
	{
		switch (axis)
		{
		case GameWorld::GCamera2D::kAxisXpos:
			x_index = 2; y_index = 1;
			x_sign = 1; y_sign = 1;
			break;
		case GameWorld::GCamera2D::kAxisXneg:
			x_index = 2; y_index = 1;
			x_sign = -1; y_sign = 1;
			break;
		case GameWorld::GCamera2D::kAxisYpos:
			x_index = 0; y_index = 2;
			x_sign = 1; y_sign = 1;
			break;
		case GameWorld::GCamera2D::kAxisYneg:
			x_index = 0; y_index = 2;
			x_sign = 1; y_sign = -1;
			break;
		case GameWorld::GCamera2D::kAxisZpos:
			x_index = 0; y_index = 1;
			x_sign = -1; y_sign = 1;
			break;
		case GameWorld::GCamera2D::kAxisZneg:
			x_index = 0; y_index = 1;
			x_sign = 1; y_sign = 1;
			break;
		default:
			GAMEWORLD_CORE_ASSERT(false, "Invalid Projection Axis Type!");
			break;
		}
	}

	GCamera2D::GCamera2D()
	{
		UpdateViewMatrix();
		UpdateProjectionMatrix();
	}

	GCamera2D::~GCamera2D()
	{

	}

	void GCamera2D::TickUpdate()
	{

	}

	void GCamera2D::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCamera2D::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCamera2D::OnMouseRightPressed));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCamera2D::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCamera2D::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_CALLBACK_FUNCTRION(GCamera2D::OnWindowResized));
	}

	GW_BOOL GCamera2D::OnKeyPressed(KeyPressedEvent& e)
	{
		GW_FLOAT32 ts = Timestep::GetDeltaTime();
		GW_INT32 x, y, signx, signy;
		GetLocalXY(projection_axis_, x, y, signx, signy);
		if (InputSystem::IsKeyPressed(Key::A))
		{
			position_[x] -= signx * cos(glm::radians(row_)) * move_speed * ts;
			position_[y] -= signy * sin(glm::radians(row_)) * move_speed * ts;
		}
		else if (InputSystem::IsKeyPressed(Key::D))
		{
			position_[x] += signx * cos(glm::radians(row_)) * move_speed * ts;
			position_[y] += signy * sin(glm::radians(row_)) * move_speed * ts;
		}

		if (InputSystem::IsKeyPressed(Key::W))
		{
			position_[x] += -signx * sin(glm::radians(row_)) * move_speed * ts;
			position_[y] += signy * cos(glm::radians(row_)) * move_speed * ts;
		}
		else if (InputSystem::IsKeyPressed(Key::S))
		{
			position_[x] -= -signx * sin(glm::radians(row_)) * move_speed * ts;
			position_[y] -= signy * cos(glm::radians(row_)) * move_speed * ts;
		}

		if (isRotation)
		{
			if (InputSystem::IsKeyPressed(Key::Q))
				row_ += rotation_speed * ts;
			else if (InputSystem::IsKeyPressed(Key::E))
				row_ -= rotation_speed * ts;

			if (row_ > 180.0f)
				row_ -= 360.0f;
			else if (row_ <= -180.0f)
				row_ += 360.0f;
			
		}
		UpdateViewMatrix();
		return false;
	}

	GW_BOOL GCamera2D::OnMouseRightPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Mouse::ButtonRight)
		{
			mouse_press_pos_ = InputSystem::GetMousePosition();
			return false;
		}
		return true;
	}

	GW_BOOL GCamera2D::OnMouseMoved(MouseMovedEvent& e)
	{
		if (InputSystem::IsMouseButtonPressed(Mouse::ButtonRight))
		{
			GW_FLOAT32 mouse_sensitivity = viewport_fov_y_;
			glm::vec2 window_resolution = Application::GetInst().GetWindow().GetResolution();
			GW_INT32 x, y, signx, signy;
			GetLocalXY(projection_axis_, x, y, signx, signy);
			position_[x] -= signx * mouse_sensitivity * (e.GetX() - mouse_press_pos_.x) * window_resolution.x;
			position_[y] -= signy * mouse_sensitivity * (mouse_press_pos_.y - e.GetY()) * window_resolution.y;

			UpdateViewMatrix();
			mouse_press_pos_ = { e.GetX() , e.GetY() };
			return false;
		}
		return true;
	}

	GW_BOOL GCamera2D::OnMouseScrolled(MouseScrolledEvent& e)
	{
		viewport_fov_y_ -= e.GetYOffset() * 0.25f;
		viewport_fov_y_ = viewport_fov_y_ < 0.25f ? 0.25 : viewport_fov_y_;
		UpdateProjectionMatrix();
		return false;
	}

	GW_BOOL GCamera2D::OnWindowResized(WindowResizeEvent& e)
	{
		UpdateViewportRatio((GW_FLOAT32)e.GetWidth(), (GW_FLOAT32)e.GetHeight());
		return false;
	}

	void GCamera2D::UpdateState(const glm::vec3& position)
	{
		position_ = position; 
		UpdateViewMatrix();
	}

	void GCamera2D::UpdateState(GW_FLOAT32 rotation)
	{
		row_ = rotation; 
		UpdateViewMatrix();
	}

	void GCamera2D::UpdateState(const glm::vec3& position, GW_FLOAT32 rotation)
	{
		position_ = position; 
		row_ = rotation; 
		UpdateViewMatrix();
	}

	void GCamera2D::UpdateViewMatrix()
	{
		glm::vec3 front; glm::vec3 up;
		GetLocalCameraPoseVector(projection_axis_, front, up);
		v_mat_ = glm::rotate(glm::lookAt(position_, position_ + front, up), glm::radians(row_), front);
		vp_mat_ = p_mat_ * v_mat_;
	}

	void GCamera2D::UpdateProjectionMatrix()
	{
		GW_FLOAT32 half_width;
		GW_FLOAT32 half_height;
		switch (projection_mode_)
		{
		case EProjectionMode::kPerspective:
			GAMEWORLD_CORE_ASSERT(false, "Camera2D only has Ortho Projection Type!");
			break;
		case EProjectionMode::kOrtho:
			half_height = viewport_fov_y_ * 0.5f;
			half_width = half_height * viewport_ratio_;
			p_mat_ = glm::ortho(-half_width, half_width, -half_height, half_height);
			break;
		default:
			p_mat_ = glm::mat4(1.0f);
			break;
		}
		vp_mat_ = p_mat_ * v_mat_;
	}

}
