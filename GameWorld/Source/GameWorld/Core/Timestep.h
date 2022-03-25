#pragma once

namespace GameWorld 
{

	class Timestep
	{
	public:
	
		static void TickUpdate();

		static GW_FLOAT32 GetLastTickTime()    { return last_tick_time_; }
		static GW_FLOAT32 GetLastTickTimeMs()  { return last_tick_time_ * 1000.0f; }
											   
		static GW_FLOAT32 GetStaticDeltaTime() { return ctick_delta_time_; }
											   
		static GW_FLOAT32 GetDeltaTime()       { return tick_delta_time_; }
		static GW_FLOAT32 GetDeltaTimeMs()     { return tick_delta_time_ * 1000.0f; }

	private:
		const static GW_FLOAT32 ctick_delta_time_;
		static GW_FLOAT32 last_tick_time_;
		static GW_FLOAT32 tick_delta_time_;
	};

}