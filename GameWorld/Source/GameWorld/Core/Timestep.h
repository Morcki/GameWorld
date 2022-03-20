#pragma once
namespace GameWorld 
{

	class Timestep
	{
	public:
		Timestep(GW_FLOAT32 time = 0.0f)
			: time_(time)
		{
		}

		operator float() const { return time_; }

		float GetSeconds() const { return time_; }
		float GetMilliseconds() const { return time_ * 1000.0f; }
	private:
		GW_FLOAT32 time_;
	};

}