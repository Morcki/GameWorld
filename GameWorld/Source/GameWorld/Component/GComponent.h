#pragma once
#include "GObject.h"

namespace GameWorld
{
	class GComponent : public GObject
	{
	public:
		GComponent() {};
		virtual ~GComponent() {};

		virtual void TickUpdate() override {};

	};
}