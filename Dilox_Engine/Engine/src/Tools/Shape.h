#pragma once
#include <Tools/Renderer2D.h>
#include "Tools/Entity2D.h"

namespace DiloxGE
{
	class Shape :
		public Entity2D
	{
	private:
		Renderer2D* renderer2D;
		float* vertexPosition;
		int vertexCount;

	public:
		Shape(Renderer2D* renderer2D);
		~Shape();

		void SetVertices(int vertexCount, float* vertexPosition);

		void Draw();

		float* GetVertexPosition()
		{
			return vertexPosition;
		}
		int GetVertexCount()
		{
			return vertexCount;
		}
	};
}

