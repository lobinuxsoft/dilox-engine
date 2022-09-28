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

	void Renderer2D::DrawBuffer()
	{
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer2D::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer2D::Draw(float vertexPos[])
	{
		unsigned int indices[6] =
		{
			0,1,2,
			2,3,0 
		};

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		SetBuffers(1, m_IndexBuffer, indices);
		SetBuffers(1, m_IndexBuffer, vertexPos);

		BeginDraw();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void Renderer2D::DrawSquare()
	{

	}

	void Renderer2D::BeginDraw()
	{
		glEnableVertexAttribArray(0);
	}

	//Buffer array tiene los vertices / indices
	void Renderer2D::SetBuffers(int quantity, unsigned int& id, unsigned int bufferArray[])
	{
		glGenBuffers(quantity, &id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * sizeof(float), bufferArray, GL_STATIC_DRAW);
	}

	void Renderer2D::SetBuffers(int quantity, unsigned int& id, float bufferArray[])
	{
		glGenBuffers(quantity, &id);

		glBindBuffer(GL_ARRAY_BUFFER, id);

		glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), bufferArray, GL_STATIC_DRAW);
	}

}

