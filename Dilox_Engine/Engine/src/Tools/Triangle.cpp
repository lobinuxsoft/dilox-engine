#include "dgepch.h"
#include "Triangle.h"

namespace DiloxGE
{
	Triangle::Triangle(Renderer2D* renderer2D, float vertexPos[3 * 3], bool isStatic) : Shape(renderer2D)
	{
		this->renderer2D = renderer2D;
		this->vertexPos[3 * 3] = vertexPos;
		Draw();
	}

	Triangle::~Triangle()
	{

	}

	void Triangle::Draw()
	{
		renderer2D->DrawTriangle(vertexPos[3 * 3]);
	}
}
