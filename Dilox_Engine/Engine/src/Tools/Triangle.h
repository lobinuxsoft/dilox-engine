#pragma once
#include "Tools/Entity2D.h"

namespace DiloxGE
{
	class Triangle :
		public Entity2D
	{
	private:
		Renderer2D* renderer2D;
		float* vertexPos[];

	public:
		Triangle(Renderer2D* renderer2D, float vertexPos[3 * 3], bool isStatic);
		~Triangle();

		void Draw();
	};
}


