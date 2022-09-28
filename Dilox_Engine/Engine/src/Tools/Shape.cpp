#include "dgepch.h"
#include "Shape.h"

namespace DiloxGE
{
	Shape::Shape(Renderer2D* renderer2D, float vertexPos[], bool isStatic) : Entity2D(renderer2D)
	{
		this->renderer2D = renderer2D;
		this->vertexPos[3 * 3] = vertexPos;
		Draw();
	}

	Shape::~Shape()
	{

	}

	void Shape::SetVertices(int vertexCount, float* vertexPosition)
	{
		vertexPos[3 * 3] = vertexPosition;
		this->vertexCount = vertexCount;
	}

	void Shape::Draw()
	{
		renderer2D->Draw(vertexPos[3 * 3]);
	}
}

