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

	void Entity::SetPosition(Position newPos)
	{
		transform.position = newPos;
	}

	Position Entity::GetPosition()
	{
		return transform.position;
	}

	void Entity::SetRotation(Quaternion newRotation)
	{
		transform.rotation = newRotation;
	}

	Quaternion Entity::GetRotation()
	{
		return transform.rotation;
	}

	void Entity::SetScale(Scale newScale)
	{
		transform.scale = newScale;
	}

	Scale Entity::GetScale()
	{
		return transform.scale;
	}
}