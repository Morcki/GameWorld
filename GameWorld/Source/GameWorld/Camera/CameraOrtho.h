#pragma once
#include "CameraBase.h"

namespace GameWorld
{
	class Camera2DOrtho
	{
	public:
		[[deprecated("Will Deprecated soon,Use GCamera2D instead.")]]
		Camera2DOrtho(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top);
		~Camera2DOrtho();

		void SetProjection(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top);

		glm::vec3 GetPosition() { return position_; }
		const glm::vec3& GetPosition() const { return position_; }
		void SetPosition(const glm::vec3& position) { position_ = position; RecalculateViewMatrix(); }

		GW_FLOAT32 GetRotation() { return rotation_; }
		void SetRotation(GW_FLOAT32 rotation) { rotation_ = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetViewMatrix() const { return view_matrix_; }
		const glm::mat4& GetProjectionMatrix() const { return projection_matrix_; }
		const glm::mat4& GetViewProjectionMatrix() const { return view_projection_matrix_; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 view_matrix_;
		glm::mat4 projection_matrix_;
		glm::mat4 view_projection_matrix_;

		glm::vec3 position_ = { 0.0f, 0.0f, 0.0f };
		GW_FLOAT32 rotation_ = 0.0f;
	};
	
	class CameraOrtho : public CameraProjection
	{
	public:
		[[deprecated("Will Deprecated soon,Use GCamera instead.")]]
		CameraOrtho(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top);
		virtual ~CameraOrtho() override;
		
		glm::vec4 GetOrthoBox() { return ortho_box_; };
		const glm::vec4& GetOrthoBox() const { return ortho_box_; };
		void UpdateOrthoBox(GW_FLOAT32 left, GW_FLOAT32 right, GW_FLOAT32 bottom, GW_FLOAT32 top);

	protected:
		virtual void UpdateProjectionMatrix() override;
	private:
		glm::vec4 ortho_box_;
	};
}