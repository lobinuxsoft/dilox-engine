#pragma once
#include <Tools/Renderer2D.h>
#include "glm/glm.hpp"

namespace DiloxGE
{
	struct Position
	{
		float x = 0;
		float y = 0;
		float z = 0;
	};

	struct Quaternion
	{
		float x = 1;
		float y = 1;
		float z = 1;
		float w = 1;
	};

	struct Scale
	{
		float x = 1;
		float y = 1;
		float z = 1;
	};

	struct Transform
	{
		Position position;
		Quaternion rotation;
		Scale scale;
	};

	class Entity
	{
	public:
		Entity(Renderer2D* renderer2D);
		~Entity();
		void SetPosition(Position newPos);
		Position GetPosition();
		void SetRotation(Quaternion newRotation);
		Quaternion GetRotation();
		void SetScale(Scale newScale);
		Scale GetScale();
		virtual void Draw() = 0;

	protected:
		Renderer2D* renderer2D;
		Transform transform;
	};
}


