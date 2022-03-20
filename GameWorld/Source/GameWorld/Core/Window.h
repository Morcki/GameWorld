#pragma once
#pragma once

#include <functional>

#include "GameWorld/Events/Event.h"

namespace GameWorld {

	struct WindowProps
	{
		std::string title;
		GW_UINT32 width;
		GW_UINT32 height;

		WindowProps(const std::string& title_in = "GameWorld Engine",
			GW_UINT32 width_in = 1280,
			GW_UINT32 height_in = 720)
			: title(title_in), width(width_in), height(height_in)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using CallbackFunction = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual GW_UINT32 GetWidth() const = 0;
		virtual GW_UINT32 GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const CallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual GW_BOOL IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}