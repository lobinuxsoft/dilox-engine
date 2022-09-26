#pragma once
#include <Tools/Renderer2D.h>
#include "Tools/Entity.h"

namespace DiloxGE
{
	class Shape :
		public Entity
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
		int GetVertexCount()
		{
			return vertexCount;
		}

	};
}

