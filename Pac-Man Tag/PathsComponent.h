#pragma once
#include "Component.h"


class PathComponent : public Component
{
public :
	PathComponent();
	PathComponent(const PathComponent& other);
	PathComponent(bool up, bool down, bool left, bool right);
	~PathComponent();

	bool canMoveDown;
	bool canMoveLeft;
	bool canMoveRight;
	bool canMoveUp;

private:
};