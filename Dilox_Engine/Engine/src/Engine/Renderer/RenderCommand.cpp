#include "dgepch.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace DiloxGE
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}