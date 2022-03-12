#include <PrecompiledHeader.h>
#include "../Core/Core.h"
#include "Window.h"

#ifdef GAMEWORLD_PLATFORM_WINDOWS
	#include "../Platform//WindowsWindow.h"
#endif

namespace GameWorld
{
	Window* Window::Create(const WindowProps& props)
	{
#ifdef GAMEWORLD_PLATFORM_WINDOWS
		return new WindowsWindow(props);
#else
		GAMEWORLD_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}