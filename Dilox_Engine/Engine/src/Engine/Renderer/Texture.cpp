#include "dgepch.h"
#include "Engine/Renderer/Texture.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace DiloxGE
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		DGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(width, height);
		}

		DGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		DGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		DGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}