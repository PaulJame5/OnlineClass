#pragma once
#include "I_ComponentSystem.h"
#include "BigDotComponent.h"


class BigDotSystem : public I_ComponentSystem<BigDotComponent>
{
public:
	BigDotSystem();
	~BigDotSystem();
	void update() override;
	void restart();
private:

};