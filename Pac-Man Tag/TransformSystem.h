#pragma once
#include "I_ComponentSystem.h"
#include "TransformComponent.h"


class TransformSystem : public I_ComponentSystem<TransformComponent>
{
public:
	TransformSystem();
	~TransformSystem();
	void update() override;
	static void syncOtherPosition(ge::Vector2i pos);
	void restart();
private:
};
