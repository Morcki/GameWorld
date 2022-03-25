#include <PrecompiledHeader.h>

#include "InputSystem.h"

#include <GLFW/glfw3.h>

#include "GameWorld/Application.h"

namespace GameWorld
{
	GW_BOOL    InputSystem::b_first_tick = true;

	GW_FLOAT32 InputSystem::last_tick_mouse_x = 0.0f;
	GW_FLOAT32 InputSystem::last_tick_mouse_y = 0.0f;

	GW_FLOAT32 InputSystem::tick_mouse_xoff = 0.0f;
	GW_FLOAT32 InputSystem::tick_mouse_yoff = 0.0f;

	void InputSystem::UpdateMousePosition(GW_FLOAT32 xpos, GW_FLOAT32 ypos)
	{
		if (b_first_tick)
		{
			last_tick_mouse_x = xpos;
			last_tick_mouse_y = ypos;
			b_first_tick = false;
		}
		
		tick_mouse_xoff = xpos - last_tick_mouse_x;
		tick_mouse_yoff = last_tick_mouse_y - ypos; // reversed since y-coordinates go from bottom to top

		last_tick_mouse_x = xpos;
		last_tick_mouse_y = ypos;
		
	}

	bool InputSystem::IsKeyPressed(const KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetInst().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool InputSystem::IsMouseButtonPressed(const MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetInst().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 InputSystem::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetInst().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float InputSystem::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float InputSystem::GetMouseY()
	{
		return GetMousePosition().y;
	}

	GW_FLOAT32 InputSystem::GetMouseXOffset()
	{
		return tick_mouse_xoff;
	}

	GW_FLOAT32 InputSystem::GetMouseYOffset()
	{
		return tick_mouse_yoff;
	}

}