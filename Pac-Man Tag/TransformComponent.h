#pragma once
#include "Component.h"
#include "Vector2.h"


class TransformComponent : public Component
{
public:
	TransformComponent();
	TransformComponent(ge::Vector2f position);
	~TransformComponent();

	ge::Vector2f position = ge::Vector2f(0, 0);
	ge::Vector2i initialPosition;
	void init();
private:

};