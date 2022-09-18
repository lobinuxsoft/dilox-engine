#include "dgepch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace DiloxGE
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}