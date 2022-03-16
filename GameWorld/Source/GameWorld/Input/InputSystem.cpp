#include <PrecompiledHeader.h>

#include "InputSystem.h"

#include <GLFW/glfw3.h>

#include "GameWorld/Application.h"

namespace GameWorld
{
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
}