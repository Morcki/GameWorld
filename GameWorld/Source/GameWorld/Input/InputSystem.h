#pragma once
#include <glm/glm.hpp>

#include "../Events/KeyCodes.h"
#include "../Events/MouseCodes.h"

namespace GameWorld
{
	class InputSystem
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}