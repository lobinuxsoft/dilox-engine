#include "dgepch.h"
#include "Shape.h"

namespace DiloxGE
{
	Shape::Shape(Renderer2D* renderer2D) : Entity2D(renderer2D)
	{
		this->renderer2D = renderer2D;
	}

	Shape::~Shape()
	{

	}

	void Shape::SetVertices(int vertexCount, float* vertexPosition)
	{
		this->vertexPosition = vertexPosition;
		this->vertexCount = vertexCount;
	}

	void Shape::Draw()
	{

	}
}

