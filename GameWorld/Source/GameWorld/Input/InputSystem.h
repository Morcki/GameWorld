#pragma once
#include "GameWorld/Events/KeyCodes.h"
#include "GameWorld/Events/MouseCodes.h"

#include <glm/glm.hpp>

namespace GameWorld
{
	class InputSystem
	{
	public:
		static void UpdateMousePosition(GW_FLOAT32 xpo, GW_FLOAT32 ypos);

		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		static GW_FLOAT32 GetMouseXOffset();
		static GW_FLOAT32 GetMouseYOffset();

	public:
		static GW_BOOL    b_first_tick;
		static GW_FLOAT32 last_tick_mouse_x;
		static GW_FLOAT32 last_tick_mouse_y;
		static GW_FLOAT32 tick_mouse_xoff;
		static GW_FLOAT32 tick_mouse_yoff;
	};
}