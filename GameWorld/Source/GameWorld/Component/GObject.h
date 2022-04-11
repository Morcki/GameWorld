#pragma once

namespace GameWorld
{
	class GObject
	{
	public:
		GObject() {};
		virtual ~GObject() {};

		virtual void TickUpdate() {};
	};
}