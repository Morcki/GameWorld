#pragma once
#pragma once

#include <functional>

#include "GameWorld/Events/Event.h"

namespace GameWorld {

	struct WindowProps
	{
		std::string Title;
		GW_UINT32 Width;
		GW_UINT32 Height;

		WindowProps(const std::string& title = "GameWorld Engine",
			GW_UINT32 width = 1280,
			GW_UINT32 height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual GW_UINT32 GetWidth() const = 0;
		virtual GW_UINT32 GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual GW_BOOL IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}