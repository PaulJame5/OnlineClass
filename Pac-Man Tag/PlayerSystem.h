#pragma once
#include "I_ComponentSystem.h"
#include "PlayerComponent.h"


class PlayerSystem : public I_ComponentSystem<PlayerComponent>
{
public:
	PlayerSystem();
	~PlayerSystem();
	void restart();
	void update() override;
	void checkSpeedIncrease(std::vector<int>& ids);
	void checkPlayersCollide(std::vector<int>& ids);
	void setCanMovePath(std::vector<int>& ids);
	bool playerCaught();
private:
};