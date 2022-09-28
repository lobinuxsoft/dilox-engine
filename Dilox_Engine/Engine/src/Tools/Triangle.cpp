#include "dgepch.h"
#include "Triangle.h"

namespace DiloxGE
{
	Triangle::Triangle(Renderer2D* renderer2D, float vertexPos[], bool isStatic) : Shape(renderer2D)
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
		renderer2D->Draw(vertexPos[3 * 3]);
	}
}
