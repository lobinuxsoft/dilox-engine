#pragma once
#include "Tools/Entity2D.h"
#include "Tools/Shape.h"

namespace DiloxGE
{
	class Triangle :
		public Shape
	{
	private:
		Renderer2D* renderer2D;
		float* vertexPos[];

	public:
		Triangle(Renderer2D* renderer2D, float vertexPos[], bool isStatic);
		~Triangle();

		void Draw();
	};
}


