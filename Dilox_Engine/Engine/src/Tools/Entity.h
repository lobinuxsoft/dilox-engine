#pragma once
#include <Tools/Renderer2D.h>
#include "glm/glm.hpp"

namespace DiloxGE
{
	struct Coordinates
	{
		float x;
		float y;
		float z;
	};

	class Entity
	{
	public:
		Entity(Renderer2D* renderer2D);
		~Entity();
		void SetPosition(Coordinates newPos);
		Coordinates GetPosition();
		void SetRotation(Coordinates newRotation);
		Coordinates GetRotation();
		void SetScale(Coordinates newScale);
		Coordinates GetScale();
		virtual void Draw() = 0;

	private:
		Renderer2D* renderer2D;
		Coordinates pos;
		Coordinates rotation;
		Coordinates scale;
	};
}


