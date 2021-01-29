#include "PathsComponent.h"

PathComponent::PathComponent()
{
}

PathComponent::PathComponent(const PathComponent& other)
{
	canMoveDown = other.canMoveDown;
	canMoveLeft = other.canMoveLeft;
	canMoveRight = other.canMoveRight;
	canMoveUp = other.canMoveUp;
}

PathComponent::PathComponent(bool up, bool down, bool left, bool right)
{
	canMoveDown = down;
	canMoveUp = up;
	canMoveLeft = left;
	canMoveRight = right;
}

PathComponent::~PathComponent()
{
}
