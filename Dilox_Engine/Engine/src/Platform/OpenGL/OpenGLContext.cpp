#include "dgepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace DiloxGE
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		DGE_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);  // initialize Glad
		DGE_CORE_ASSERT(status, "Failed to initialize Glad!");

		DGE_CORE_INFO("OpenGL Info:");
		DGE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		DGE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		DGE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}