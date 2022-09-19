#pragma once
#include <Tools/Renderer2D.h>

namespace DiloxGE
{
	class Shape
	{
	private:
		float* vertexPosition;
		int vertexCount;

	public:
		Shape();
		~Shape();

		void SetVertices(int vertexCount, float* vertexPosition);

		void Draw();

		float* GetVertexPosition()
		{
			return vertexPosition;
		}
		int getVertexCount()
		{
			return vertexCount;
		}

	};
}

