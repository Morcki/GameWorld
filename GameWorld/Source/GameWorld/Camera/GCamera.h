#pragma once

#include <glm/glm.hpp>

#include "GameWorld/Events/Event.h"
#include "GameWorld/Events/KeyEvent.h"
#include "GameWorld/Events/MouseEvent.h"

#include "GameWorld/Application.h"

namespace GameWorld
{
	enum class ECameraMode : GW_UINT8
	{
		kInvalid,
		kEditor,
		kThirdPerson,
		kFirstPerson,
		kFree
	};

	enum EProjectionMode : GW_UINT8
	{
		kPerspective,
		kOrtho
	};

	struct CameraOptions
	{
		ECameraMode     camera_mode{ ECameraMode::kEditor };
		EProjectionMode projection_mode{ EProjectionMode::kPerspective };
		glm::vec3 position{ glm::vec3(0.0f, 0.0f, -1.0f) };

		glm::vec3 world_up{ glm::vec3(0.0f, 1.0f, 0.0f) };
		glm::vec3 up{ NULL };
		glm::vec3 front{ NULL };
		glm::vec3 right{ NULL };

		GW_FLOAT32 viewport_fov_x{ 0.0f };
		GW_FLOAT32 viewport_fov_y{ 55.0f }; // Present FovY when Perspective,Viewport Height when Ortho
		GW_FLOAT32 viewport_ratio{ Application::GetInst().GetWindow().GetAspectRatio() };
		GW_FLOAT32 znear{ 0.3f };
		GW_FLOAT32 zfar{ 3000.0f };
		GW_FLOAT32 yaw{ -90.0f };
		GW_FLOAT32 pitch{ 0.0f };
	};

	class GCamera
	{
	public:
		GCamera();
		GCamera(CameraOptions opts);
		virtual ~GCamera() = default;

	public:
		const glm::mat4& GetViewMat()           const { return v_mat_; };
		const glm::mat4& GetProjectionMat()     const { return p_mat_; };
		const glm::mat4& GetViewProjectionMat() const { return vp_mat_; };

		EProjectionMode GetProjectionMode() { return opts_.projection_mode; };

		glm::vec3 GetPosition() { return opts_.position; };
		glm::vec3 GetFront()    { return opts_.front; };

		GW_FLOAT32 GetFovY()    { return opts_.viewport_fov_y; };
		GW_FLOAT32 GetRatio()   { return opts_.viewport_ratio; };
		GW_FLOAT32 GetZNear()   { return opts_.znear; };
		GW_FLOAT32 GetZFar()    { return opts_.zfar; };
		
	public: /* Handle Event System */
		virtual void TickUpdate()                                    = 0;
		virtual void OnEvent(Event& e)                               = 0;

		virtual GW_BOOL OnKeyPressed(KeyPressedEvent& e)             = 0;
		virtual GW_BOOL OnKeyReleased(KeyReleasedEvent& e)           = 0;
		virtual GW_BOOL OnMousePressed(MouseButtonPressedEvent& e)   = 0;
		virtual GW_BOOL OnMouseReleased(MouseButtonReleasedEvent& e) = 0;
		virtual GW_BOOL OnMouseMoved(MouseMovedEvent& e)             = 0;
		virtual GW_BOOL OnMouseScrolled(MouseScrolledEvent& e)       = 0;
		virtual GW_BOOL OnWindowResized(WindowResizeEvent& e)        = 0;

	public: /* Handle Input System */
		void UpdateProjectionMode(EProjectionMode pmode);

		void UpdateViewportRatio(GW_FLOAT32 w, GW_FLOAT32 h) { opts_.viewport_ratio = w / h; UpdateProjectionMatrix(); }
		void UpdateViewportRatio(GW_FLOAT32 ratio)           { opts_.viewport_ratio = ratio; UpdateProjectionMatrix(); }
		void UpdateFovY(float fovy)                          { opts_.viewport_fov_y = fovy; UpdateProjectionMatrix(); }

		void UpdateState(const glm::vec3& position);
		void UpdateState(GW_FLOAT32 yaw, GW_FLOAT32 pitch);
		void UpdateState(const glm::vec3& position, GW_FLOAT32 yaw, GW_FLOAT32 pitch);

	protected:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

	protected:
		CameraOptions opts_{ CameraOptions() };

	private:
		glm::mat4 v_mat_{ glm::mat4(1.0f) };
		glm::mat4 p_mat_{ glm::mat4(1.0f) };
		glm::mat4 vp_mat_;
	};

	class GCamera2D
	{
	public:
		enum EProjectionAxis
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
		GW_FLOAT32 rotation_speed{ 150.0f };

	public:
		const glm::mat4& GetViewMat()           const { return v_mat_; };
		const glm::mat4& GetProjectionMat()     const { return p_mat_; };
		const glm::mat4& GetViewProjectionMat() const { return vp_mat_; };

		EProjectionMode GetProjectionMode() { return projection_mode_; };

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
		void UpdateProjectionAxis(EProjectionAxis axis) { projection_axis_ = axis; UpdateViewMatrix(); }

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
		EProjectionMode projection_mode_{ EProjectionMode::kOrtho };
		EProjectionAxis projection_axis_{ EProjectionAxis::kAxisZneg };

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