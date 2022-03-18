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

		GW_UINT32 GetWidth() const override { return m_Data.Width; }
		GW_UINT32 GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		GW_BOOL IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		RenderContext* RenderGraphicsContext;

		struct WindowData
		{
			std::string Title;
			GW_UINT32 Width, Height;
			GW_BOOL bVerticalSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}