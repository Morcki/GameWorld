#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GameWorld
{
	// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
	enum class CameraMovement {
		kForward,
		kBackward,
		kLeft,
		kRight
	};

	enum class CameraType
	{
		kCamera2D,
		kCamera3D,
	};

	enum class ProjectionType
	{
		kOrthographic,
		kPerspective,
	};

	class CameraBase
	{// Only Care about view matrix part
	public:
		CameraBase();
		CameraBase(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
		virtual ~CameraBase() = default;

	    const glm::mat4& GetViewMatrix() const { return view_matrix_; };
	    const glm::mat4 GetViewMatrixWithoutTranslate() { return glm::mat4(glm::mat3(view_matrix_)); };

		const glm::mat4& GetProjectionMatrix()     const { return projection_matrix_; };
		const glm::mat4& GetViewProjectionMatrix() const { return view_projection_matrix_; };

		glm::vec3  GetCameraPosition() const { return position_; };
		GW_FLOAT32 GetCameraYaw()      const { return yaw_; };
		GW_FLOAT32 GetCameraPitch()    const { return pitch_; };
		glm::vec3  GetCameraFront()    const { return front_; };
		glm::vec3  GetCameraRight()    const { return right_; };

		void UpdateCameraPosition(glm::vec3 camera_pos);
		void UpdateCameraWorldUp(glm::vec3 up);
		void UpdateCameraAttitude(GW_FLOAT32 yaw, GW_FLOAT32 pitch);
		void UpdateCameraState(glm::vec3 camera_pos, GW_FLOAT32 yaw, GW_FLOAT32 pitch);

		// virtual interface function
		virtual void UpdateNearPlane(GW_FLOAT32 near_plane)                          = 0;
		virtual void UpdateFarPlane(GW_FLOAT32 far_plane)                            = 0;
		virtual void UpdateNearFarPlane(GW_FLOAT32 near_plane, GW_FLOAT32 far_plane) = 0;
		
	
	private:
		void UpdateCameraViewMatrix();

	protected:
		CameraType camera_type_;
		ProjectionType projection_type_;

		glm::vec3 position_                { glm::vec3(0.0f) };
		glm::vec3 world_up_                { glm::vec3(0.0f, 1.0f, 0.0f) };

		GW_FLOAT32 yaw_                    { -90.0f };
		GW_FLOAT32 pitch_                  {   0.0f };

		glm::mat4 view_matrix_             { glm::mat4(1.0f) };
		glm::mat4 projection_matrix_       { glm::mat4(1.0f) };
		glm::mat4 view_projection_matrix_  { glm::mat4(1.0f) };

		glm::vec3 front_;
		glm::vec3 right_;
	};

	class CameraProjection : public CameraBase
	{
	public:
		CameraProjection() 
			: CameraBase::CameraBase() {};
		CameraProjection(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		    : CameraBase(position, up, yaw, pitch) {};

		CameraProjection(CameraProjection&)             = delete;
		CameraProjection(CameraProjection&&)            = delete;

		CameraProjection& operator=(CameraProjection&)  = delete;
		CameraProjection& operator=(CameraProjection&&) = delete;

		virtual ~CameraProjection() override { };

		virtual void UpdateNearPlane(GW_FLOAT32 zn)                   override { znear_ = zn; UpdateProjectionMatrix(); };
		virtual void UpdateFarPlane(GW_FLOAT32 zf)                    override { zfar_ = zf; UpdateProjectionMatrix(); };
		virtual void UpdateNearFarPlane(GW_FLOAT32 zn, GW_FLOAT32 zf) override { znear_ = zn; zfar_ = zf; UpdateProjectionMatrix(); };

	protected:
		// virtual interface function
		virtual void UpdateProjectionMatrix() = 0;

	protected:
		GW_FLOAT32 znear_{ 0.3f };
		GW_FLOAT32 zfar_ { 3000.0f };
	};
}
