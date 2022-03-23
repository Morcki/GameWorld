#include <PrecompiledHeader.h>
#include "CameraOrtho.h"

namespace GameWorld
{
	////////////////////////////////
	///// Orthogonal 2D Camera /////
	////////////////////////////////
	Camera2DOrtho::Camera2DOrtho(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top)
		: projection_matrix_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view_matrix_(1.0f)
	{
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	Camera2DOrtho::~Camera2DOrtho()
	{

	}

	void Camera2DOrtho::SetProjection(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top)
	{
		projection_matrix_ = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	void Camera2DOrtho::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), -position_) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0, 0, 1));

		view_matrix_ = transform;
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	////////////////////////////////
	///// Orthogonal 3D Camera /////
	////////////////////////////////
	CameraOrtho::CameraOrtho(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top)
		:
		CameraProjection::CameraProjection(), 
		ortho_box_(glm::vec4(left, right, bottom, top))
	{
		UpdateProjectionMatrix();
	}

	CameraOrtho::~CameraOrtho()
	{

	}

	void CameraOrtho::UpdateOrthoBox(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top)
	{
		ortho_box_ = glm::vec4(left, right, bottom, top);
		UpdateProjectionMatrix();
	}

	void CameraOrtho::UpdateProjectionMatrix()
	{
		projection_matrix_ = glm::ortho(ortho_box_.x, ortho_box_.y, ortho_box_.z, ortho_box_.w, znear_, zfar_);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	

}