#include "ntpch.h"
#include "WindowsWindow.h"
#include "Noctis/Log.h"

namespace Noctis {

	static bool s_GLFWInitialized = false;
	
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	};

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		NT_CORE_INFO("Creating Window {0}, {1}, {2}", props.Title, props.Height, props.Width);

		if (!s_GLFWInitialized) {
			//TODO glfw terminate on system shutdown
			int success = glfwInit();
			NT_CORE_ASSERT( succes, "Could Not Initialize GLFW!");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}