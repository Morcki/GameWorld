#include <PrecompiledHeader.h>
#include "CameraPersp.h"

#include "GameWorld/Application.h"

namespace GameWorld
{
	CameraPersp::CameraPersp()
		: aspect_ratio_(Application::GetInst().GetWindow().GetAspectRatio())
	{
		UpdateProjectionMatrix();
	}

	CameraPersp::CameraPersp(GW_FLOAT32 fov_y, GW_FLOAT32 aspect)
		: 
		CameraProjection::CameraProjection(),
		fov_y_(fov_y), aspect_ratio_(aspect)
	{
		UpdateProjectionMatrix();
	}

	CameraPersp::~CameraPersp()
	{

	}

	void CameraPersp::UpdateProjectionMatrix()
	{
		projection_matrix_ = glm::perspective(glm::radians(fov_y_), aspect_ratio_, znear_, zfar_);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

}
