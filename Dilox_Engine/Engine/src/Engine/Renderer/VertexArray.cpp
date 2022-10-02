#include "dgepch.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace DiloxGE
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		DGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexArray>();
		}

		DGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}