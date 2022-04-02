#pragma once

#include <glm/glm.hpp>

#include "GameWorld/Events/Event.h"
#include "GameWorld/Events/KeyEvent.h"
#include "GameWorld/Events/MouseEvent.h"

#include "GameWorld/Application.h"

namespace GameWorld
{

	enum ProjectionMode
	{
		kPerspective,
		kOrtho
	};

	class GCamera
	{
	public:
		GCamera();
		~GCamera();

	public:
		GW_BOOL isConstrainPitch{ true };
		// camera options
		GW_FLOAT32 move_speed{ 2.5f };
		GW_FLOAT32 mouse_sensitive{ 0.35f };

	public:
		const glm::mat4& GetViewMat()           const { return v_mat_; };
		const glm::mat4& GetProjectionMat()     const { return p_mat_; };
		const glm::mat4& GetViewProjectionMat() const { return vp_mat_; };

		ProjectionMode GetProjectionMode() { return projection_mode_; };

		glm::vec3 GetPosition() { return position_; };
		glm::vec3 GetFront()    { return front_; };

		GW_FLOAT32 GetFovY()    { return viewport_fov_y_; };
		GW_FLOAT32 GetRatio()   { return viewport_ratio_; };
		GW_FLOAT32 GetZNear()   { return znear_; };
		GW_FLOAT32 GetZFar()    { return zfar_; };
		
	public: /* Handle Event System */
		void TickUpdate();
		void OnEvent(Event& e);

		GW_BOOL OnKeyPressed(KeyPressedEvent& e);
		GW_BOOL OnMouseMoved(MouseMovedEvent& e);
		GW_BOOL OnMouseScrolled(MouseScrolledEvent& e);
		GW_BOOL OnWindowResized(WindowResizeEvent& e);

	public: /* Handle Input System */
		void UpdateProjectionMode(ProjectionMode pmode);

		void UpdateViewportRatio(GW_FLOAT32 w, GW_FLOAT32 h) { viewport_ratio_ = w / h; UpdateProjectionMatrix(); }
		void UpdateViewportRatio(GW_FLOAT32 ratio)           { viewport_ratio_ = ratio; UpdateProjectionMatrix(); }
		void UpdateFovY(float fovy)                          { fovy = viewport_fov_y_; UpdateProjectionMatrix(); }

		void UpdateState(const glm::vec3& position);
		void UpdateState(GW_FLOAT32 yaw, GW_FLOAT32 pitch);
		void UpdateState(const glm::vec3& position, GW_FLOAT32 yaw, GW_FLOAT32 pitch);

	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

	private:
		ProjectionMode projection_mode_{ ProjectionMode::kPerspective };
		glm::vec3 position_{ glm::vec3(0.0f) };

		glm::vec3 world_up_{ glm::vec3(0.0f, 1.0f, 0.0f) };
		glm::vec3 up_;
		glm::vec3 front_;
		glm::vec3 right_;

		GW_FLOAT32 viewport_fov_y_{ 55.0f }; // Present FovY when Perspective,Viewport Height when Ortho
		GW_FLOAT32 viewport_ratio_{ Application::GetInst().GetWindow().GetAspectRatio() };
		GW_FLOAT32 znear_{ 0.3f };
		GW_FLOAT32 zfar_{ 3000.0f };
		GW_FLOAT32 yaw_{ -90.0f };
		GW_FLOAT32 pitch_{ 0.0f };

		glm::mat4 v_mat_{ glm::mat4(1.0f) };
		glm::mat4 p_mat_{ glm::mat4(1.0f) };
		glm::mat4 vp_mat_;
	};

	class GCamera2D
	{
	public:
		enum ProjectionAxis
		{
			kAxisXpos, // Fixed X axis, assume camera placed on +X.
			kAxisXneg, // Fixed X axis, assume camera placed on -X.
			kAxisYpos, // Fixed Y axis, assume camera placed on +Y.
			kAxisYneg, // Fixed Y axis, assume camera placed on -Y.
			kAxisZpos, // Fixed Z axis, assume camera placed on +Z.
			kAxisZneg, // Fixed Z axis, assume camera placed on -Z.
		};

	public:
		GCamera2D();
		~GCamera2D();

	public:
		GW_BOOL isRotation{ true };

		GW_FLOAT32 move_speed{ 5.0f };
		GW_FLOAT32 rotation_speed{ 45.0f };

	public:
		const glm::mat4& GetViewMat()           const { return v_mat_; };
		const glm::mat4& GetProjectionMat()     const { return p_mat_; };
		const glm::mat4& GetViewProjectionMat() const { return vp_mat_; };

		ProjectionMode GetProjectionMode() { return projection_mode_; };

		glm::vec3 GetPosition() { return position_; };
		GW_FLOAT32 GetRow() { return row_; }

	public: /* Handle Event System */
		void TickUpdate();
		void OnEvent(Event& e);

		GW_BOOL OnKeyPressed(KeyPressedEvent& e);
		GW_BOOL OnMouseRightPressed(MouseButtonPressedEvent& e);
		GW_BOOL OnMouseMoved(MouseMovedEvent& e);
		GW_BOOL OnMouseScrolled(MouseScrolledEvent& e);
		GW_BOOL OnWindowResized(WindowResizeEvent& e);

	public: /* Handle Input System */
		void UpdateProjectionAxis(ProjectionAxis axis) { projection_axis_ = axis; UpdateViewMatrix(); }

		void UpdateViewportRatio(GW_FLOAT32 w, GW_FLOAT32 h) { viewport_ratio_ = w / h; UpdateProjectionMatrix(); }
		void UpdateViewportRatio(GW_FLOAT32 ratio) { viewport_ratio_ = ratio; UpdateProjectionMatrix(); }
		void UpdateFovY(float fovy) { fovy = viewport_fov_y_; UpdateProjectionMatrix(); }

		void UpdateState(const glm::vec3& position);
		void UpdateState(GW_FLOAT32 rotation);
		void UpdateState(const glm::vec3& position, GW_FLOAT32 rotation);
		
	private: 
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();
	
	private:
		ProjectionMode projection_mode_{ ProjectionMode::kOrtho };
		ProjectionAxis projection_axis_{ ProjectionAxis::kAxisZneg };

		glm::vec3 position_{ glm::vec3(0.0f) };
		GW_FLOAT32 row_{ 0.0f };

		GW_FLOAT32 viewport_fov_y_{ 5.0f }; // Present FovY when Perspective,Viewport Height when Ortho
		GW_FLOAT32 viewport_ratio_{ Application::GetInst().GetWindow().GetAspectRatio() };

		// camera options
		glm::vec2 mouse_press_pos_;

		glm::mat4 v_mat_{ glm::mat4(1.0f) };
		glm::mat4 p_mat_{ glm::mat4(1.0f) };
		glm::mat4 vp_mat_;
	};
}