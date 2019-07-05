#include "ntpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Noctis {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		NT_CORE_ASSERT(m_WindowHandle, "handle is null!");
	}


	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NT_CORE_ASSERT(status, "failed to initialize!");
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}