#include "dgepch.h"
#include "Platform/OpenGL/OpenGLContext.h"

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
		DGE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);  // initialize Glad
		DGE_CORE_ASSERT(status, "Failed to initialize Glad!");

		DGE_CORE_INFO("OpenGL Info:");
		DGE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		DGE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		DGE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef DGE_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		DGE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "DiloxGE requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		DGE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}