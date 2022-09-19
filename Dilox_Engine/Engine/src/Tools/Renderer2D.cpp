#include "dgepch.h"
#include "Renderer2D.h"
#include <glad/glad.h>

namespace DiloxGE
{
	Renderer2D::Renderer2D()
	{

	}

	Renderer2D::~Renderer2D()
	{

	}

	void Renderer2D::DrawBuffer(int size)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, size);
	}

	void Renderer2D::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer2D::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer2D::DrawTriangle(float vertexPos[3 * 3])
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos) * 9, vertexPos, GL_STATIC_DRAW);

		BeginDraw();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void Renderer2D::BeginDraw()
	{
		glEnableVertexAttribArray(0);
	}

}

