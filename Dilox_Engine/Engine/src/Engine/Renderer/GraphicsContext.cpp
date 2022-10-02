#include "dgepch.h"
#include "Engine/Renderer/GraphicsContext.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace DiloxGE {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    DGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		DGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}