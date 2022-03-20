#pragma once

#include <GLFW/glfw3.h>

#include "GameWorld/Core/Window.h"

#include "GameWorld/Render/RenderContext.h"

namespace GameWorld {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		GW_UINT32 GetWidth() const override { return window_info_.width; }
		GW_UINT32 GetHeight() const override { return window_info_.height; }

		// Window attributes
		void SetEventCallback(const CallbackFunction& callback) override { window_info_.callback_function = callback; }
		void SetVSync(bool enabled) override;
		GW_BOOL IsVSync() const override;

		virtual void* GetNativeWindow() const { return window_; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window_;
		RenderContext* render_graphics_context_;

		struct WindowInfo
		{
			std::string title;
			GW_UINT32 width, height;
			GW_BOOL b_vertical_sync;

			CallbackFunction callback_function;
		};

		WindowInfo window_info_;
	};

}