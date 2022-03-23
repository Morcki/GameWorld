#pragma once
#include "CameraBase.h"

namespace GameWorld
{
	class CameraPersp : public CameraProjection
	{
	public:
		CameraPersp(GW_FLOAT32 fov_y, GW_FLOAT32 aspect);
		virtual ~CameraPersp() override;
		
		GW_FLOAT32 GetFovY() { return fov_y_; };
		GW_FLOAT32 GetAspectRatio() { return aspect_ratio_; };
		void UpdateFovY(GW_FLOAT32 foy_y) { fov_y_ = foy_y; UpdateProjectionMatrix(); };
		void UpdateAspectRatio(GW_FLOAT32 aspect) { aspect = aspect_ratio_; UpdateProjectionMatrix(); };

	protected:
		virtual void UpdateProjectionMatrix() override;

	private:
		GW_FLOAT32 fov_y_;
		GW_FLOAT32 aspect_ratio_;
	};

}