#pragma once

#include "glm/glm.hpp"

namespace GameWorld
{
	struct GDirectionalLight
	{
		glm::vec3 m_direction{ glm::vec3(-1.0f) };
		glm::vec3 m_color{ glm::vec3(0.0f) };
	};

	struct GAmbientLight
	{
		glm::vec3 m_irradiance{ glm::vec3(0.0f) };
	};

	struct GPointLight
	{
		glm::vec3 m_position;
		// radiant flux in W
		glm::vec3 m_flux;

		// calculate an appropriate radius for light culling
		// a windowing function in the shader will perform a smooth transition to zero
		// this is not physically based and usually artist controlled
		float calculateRadius() const
		{
			// radius = where attenuation would lead to an intensity of 1W/m^2
			const float INTENSITY_CUTOFF = 1.0f;
			const float ATTENTUATION_CUTOFF = 0.05f;
			glm::vec3   intensity = m_flux / (4.0f * M_PI);
			float       maxIntensity = std::max({ intensity.x, intensity.y, intensity.z });
			float       attenuation = std::max(INTENSITY_CUTOFF, ATTENTUATION_CUTOFF * maxIntensity) / maxIntensity;
			return 1.0f / sqrtf(attenuation);
		}
	};

}