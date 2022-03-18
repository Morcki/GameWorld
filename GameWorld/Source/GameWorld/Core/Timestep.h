#pragma once
namespace GameWorld 
{

	class Timestep
	{
	public:
		Timestep(GW_FLOAT32 time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		GW_FLOAT32 m_Time;
	};

}