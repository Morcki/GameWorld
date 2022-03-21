#include <PrecompiledHeader.h>
#include "CameraOrtho.h"

namespace GameWorld
{
	////////////////////////////////////
	///// Orthogonal 2D Camera /////////
	////////////////////////////////////
	Camera2DOrtho::Camera2DOrtho(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top)
		: projection_matrix_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view_matrix_(1.0f)
	{
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	void Camera2DOrtho::SetProjection(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top)
	{
		projection_matrix_ = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	void Camera2DOrtho::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position_) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0, 0, 1));

		view_matrix_ = glm::inverse(transform);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}
}