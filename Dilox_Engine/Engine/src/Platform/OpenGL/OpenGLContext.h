#pragma once

#include "Engine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace DiloxGE
{
	class DGE_API OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;

	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}