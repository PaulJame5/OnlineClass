#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
}

TransformComponent::TransformComponent(ge::Vector2f position)
{
	this->position = position;
	initialPosition = position;
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::init()
{
	position = initialPosition;
}
