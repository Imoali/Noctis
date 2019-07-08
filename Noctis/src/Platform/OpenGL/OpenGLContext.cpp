#include "ntpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <gl/GL.h>

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

		NT_CORE_INFO("OpenGL  Renderer:");
		NT_CORE_INFO("	vendor: {0}", glGetString(GL_VENDOR));
		NT_CORE_INFO("	renderer: {0}", glGetString(GL_RENDERER));
		NT_CORE_INFO("	version: {0}", glGetString(GL_VERSION));
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}