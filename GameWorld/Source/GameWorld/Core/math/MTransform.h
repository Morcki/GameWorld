#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GameWorld
{
	class MTransform
	{
		/* 
			±‰ªªæÿ’Û£®Transformation matrices£©
			Ref : http://www.opengl-tutorial.org/cn/beginners-tutorials/tutorial-3-matrices/
		*/

	public:
		glm::vec3    m_position{ glm::vec3(0.0f) };
		glm::vec3    m_scale{ glm::vec3(1.0f) };
		glm::quat    m_rotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) };

	public:
		MTransform() {}
		MTransform(
			const glm::vec3& position, 
			const glm::quat& rotation, 
			const glm::vec3& scale) 
			: m_position{ position }, m_scale{ scale }, m_rotation{ rotation }
		{}

		glm::mat4 ToTransformMat() const
		{// TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector
			glm::mat4 trans = glm::translate(glm::toMat4(m_rotation) * glm::scale(m_scale), m_position);
			return trans;
		}
	};
}
