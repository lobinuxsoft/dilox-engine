#include "dgepch.h"
#include "Tools/Entity.h"

namespace DiloxGE
{
	Entity::Entity(Renderer2D* renderer2D)
	{
		this->renderer2D = renderer2D;
	}

	Entity::~Entity()
	{

	}

	void Entity::SetPosition(Coordinates newPos)
	{
		pos = newPos;
	}

	Coordinates Entity::GetPosition()
	{
		return pos;
	}

	void Entity::SetRotation(Coordinates newRotation)
	{
		rotation = newRotation;
	}

	Coordinates Entity::GetRotation()
	{
		return rotation;
	}

	void Entity::SetScale(Coordinates newScale)
	{
		scale = newScale;
	}

	Coordinates Entity::GetScale()
	{
		return scale;
	}
}