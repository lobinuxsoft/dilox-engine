#include "dgepch.h"
#include "Shape.h"

namespace DiloxGE
{
	Shape::Shape()
	{

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

