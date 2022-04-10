#include <PrecompiledHeader.h>
#include "GTimeSystem.h"

#include "GLFW/glfw3.h"

namespace GameWorld
{
	GTimeSystem::GTimeSystem()
		: last_tick_time_((GW_FLOAT32)glfwGetTime())
	{

	}

	void GTimeSystem::TickUpdate()
	{
		GW_FLOAT32 current_tick_time = (GW_FLOAT32)glfwGetTime();
		tick_delta_time_ = current_tick_time - last_tick_time_;
		last_tick_time_ = current_tick_time;

		hold_time_ += tick_delta_time_;
		hold_frames_++;

		if (hold_time_ >= 1.0f)
		{// calculate frame
			frame_per_seconds_ = hold_frames_;
			GAMEWORLD_CORE_TRACE("GTimeSystem::TickUpdate => FPS:{0}", frame_per_seconds_);
			
			hold_time_ = 0.0f;
			hold_frames_ = 0;
		}
	}

	


}