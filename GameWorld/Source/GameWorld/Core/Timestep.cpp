#include <PrecompiledHeader.h>

#include "Timestep.h"

#include "GLFW/glfw3.h"

namespace GameWorld
{

	void Timestep::TickUpdate()
	{
		GW_FLOAT32 current_tick_time = (GW_FLOAT32)glfwGetTime();
		tick_delta_time_ = current_tick_time - last_tick_time_;
		last_tick_time_ = current_tick_time;
	}
	const GW_FLOAT32 Timestep::ctick_delta_time_ = 0.05f;
	GW_FLOAT32 Timestep::last_tick_time_ = 0.0f;
	GW_FLOAT32 Timestep::tick_delta_time_ = 0.0f;
	
}