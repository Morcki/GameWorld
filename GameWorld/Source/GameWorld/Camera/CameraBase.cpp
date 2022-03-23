#include <PrecompiledHeader.h>
#include "CameraBase.h"


namespace GameWorld
{

	CameraBase::CameraBase(glm::vec3 positon, glm::vec3 up, GW_FLOAT32 yaw, GW_FLOAT32 pitch)
		: position_(positon), world_up_(up), yaw_(yaw), pitch_(pitch)
	{
		UpdateCameraViewMatrix();
	}

	void CameraBase::UpdateCameraPosition(glm::vec3 camera_pos)
	{
		position_ = camera_pos;
		UpdateCameraViewMatrix();
	}

	void CameraBase::UpdateCameraWorldUp(glm::vec3 up)
	{
		world_up_ = up;
		UpdateCameraViewMatrix();
	}

	void CameraBase::UpdateCameraAttitude(GW_FLOAT32 yaw, GW_FLOAT32 pitch)
	{
		yaw_ = yaw;
		pitch_ = pitch;
		UpdateCameraViewMatrix();
	}

	void CameraBase::UpdateCameraState(glm::vec3 camera_pos, GW_FLOAT32 yaw, GW_FLOAT32 pitch)
	{
		position_ = camera_pos;
		yaw_ = yaw;
		pitch_ = pitch;
		UpdateCameraViewMatrix();
	}

	void CameraBase::UpdateCameraViewMatrix()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front.y = sin(glm::radians(pitch_));
		front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front_ = glm::normalize(front);
		// also re-calculate the Right and Up vector
		right_ = glm::normalize(glm::cross(front_, world_up_));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		// get the view matrix calculated using Euler Angles and the LookAt Matrix
		view_matrix_ = glm::lookAt(position_, position_ + front_, glm::normalize(glm::cross(right_, front_)));
	}
}