#pragma once

#include "window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Noctis {

	class WindowsWindow: public Window
	{
	public:

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window Attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* m_Window;
		struct WindowData {
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			std::string Title;
			EventCallbackFn EventCallback;
		} m_Data;
	};
}