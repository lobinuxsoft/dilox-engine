#pragma once

namespace DiloxGE
{
	enum class DGE_API RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class DGE_API Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};
}