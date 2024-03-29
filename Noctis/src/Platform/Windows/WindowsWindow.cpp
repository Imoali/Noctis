#include "ntpch.h"
#include "WindowsWindow.h"

#include "Noctis/Events/ApplicationEvent.h"
#include "Noctis/Events/KeyEvent.h"
#include "Noctis/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Noctis {

	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int error, const char* description) {
		NT_CORE_ERROR("{0}: {1}", error, description);
	};

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
			NT_CORE_ASSERT( success, "Could Not Initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		
		//set glfw callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window,int width,int height) {
			WindowData data = *((WindowData*)glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;

			WindowResizeEvent e(width, height);
			data.EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
			WindowData data = *((WindowData*)glfwGetWindowUserPointer(window));
			WindowCloseEvent e;
			data.EventCallback(e);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData data = *((WindowData*)glfwGetWindowUserPointer(window));
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent e(key, 0);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent e(key, 1);
					data.EventCallback(e);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode){
			WindowData data = *((WindowData*)glfwGetWindowUserPointer(window));
			KeyTypedEvent e(keycode);
			data.EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData data = *((WindowData*)glfwGetWindowUserPointer(window));
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent e(button);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double XOffset, double YOffset) {
			WindowData data = *((WindowData*)glfwGetWindowUserPointer(window));
			MouseScrolledEvent e((float)XOffset, (float)YOffset);
			data.EventCallback(e);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos,  double yPos) {
			WindowData data = *((WindowData*)glfwGetWindowUserPointer(window));
			MouseMovedEvent e(float(xPos),(float)yPos);
			data.EventCallback(e);
		});
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		m_Context->SwapBuffers();
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
	void * WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}
}