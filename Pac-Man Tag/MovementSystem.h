#pragma once
#include "I_ComponentSystem.h"
#include "MovementComponent.h"


class MovementSystem : public I_ComponentSystem<MovementComponent>
{
public:
	MovementSystem();
	~MovementSystem();
	void update() override;
	void restart();
private:
};