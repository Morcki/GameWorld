#include <PrecompiledHeader.h>
#include "CameraPersp.h"

namespace GameWorld
{

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
		projection_matrix_ = glm::perspective(glm::radians(fov_y_), aspect_ratio_, 0.1f, 100.0f);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

}
