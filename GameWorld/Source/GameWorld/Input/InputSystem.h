#pragma once
#include "GameWorld/Events/KeyCodes.h"
#include "GameWorld/Events/MouseCodes.h"

#include <glm/glm.hpp>

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