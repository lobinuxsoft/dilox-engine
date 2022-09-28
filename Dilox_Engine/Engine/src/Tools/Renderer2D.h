#pragma once

namespace DiloxGE
{
	class Renderer2D
	{
	private:
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	public:
		Renderer2D();
		~Renderer2D();

		void DrawBuffer();
		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void Draw(float vertexPos[]);
		void DrawSquare();
		void BeginDraw();



		void SetBuffers(int quantity, unsigned int& id, unsigned int bufferArray[]);

		void SetBuffers(int quantity, unsigned int& id, float bufferArray[]);
	};
}

