#include "gppch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Graphite {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GP_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GP_CORE_ASSERT(status, "Failed to initialize Glad!");

		GP_CORE_INFO("OpenGL Info:");
		GP_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		GP_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		GP_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}