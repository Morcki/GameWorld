#pragma once

namespace GameWorld 
{

	class GTimeSystem final : public GSingletonPublic<GTimeSystem>
	{
	public:
		GTimeSystem();

		void TickUpdate();

		inline GW_FLOAT32 GetLastTickTime()    { return last_tick_time_; }
		inline GW_FLOAT32 GetLastTickTimeMs()  { return last_tick_time_ * 1000.0f; }
											   
		inline GW_FLOAT32 GetDeltaTime()       { return tick_delta_time_; }
		inline GW_FLOAT32 GetDeltaTimeMs()     { return tick_delta_time_ * 1000.0f; }

		//inline GW_INT32   GetFramePerSeconds() { return frame_per_seconds_; }

	private:
		GW_FLOAT32 last_tick_time_;
		GW_FLOAT32 tick_delta_time_ { 0.0f };
		
		//GW_INT32   frame_per_seconds_{ 0 };
		//
		//GW_FLOAT32 hold_time_{ 0.0f };
		//GW_INT32   hold_frames_{ 0 };
	};

}