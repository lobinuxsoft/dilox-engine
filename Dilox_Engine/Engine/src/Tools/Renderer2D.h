#pragma once

//En el constructor del triangulo poner

/// <summary>
/// shouldDispose = false;
/// material = NULL
/// vertex = NULL
/// bufferId= 1;
/// 
/// vertex = new float[9] {
/// -1,0f,-1,0f,0.0f,
/// 1.0f, -1,0f, 0.0f
/// 0.0f, 1.0f, 0.0f}
/// </summary>

namespace DiloxGE
{
	class Renderer2D
	{
	private:
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	public:
		Renderer2D();
		~Renderer2D();

		void DrawBuffer(int size);
		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void DrawTriangle(float vertexPos[3 * 3]);
		void BeginDraw();
	};
}

