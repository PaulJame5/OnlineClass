#pragma once
#include "Component.h"



class BigDotComponent : public Component
{
public:
	BigDotComponent();
	~BigDotComponent();
	void Kill();
	void SetAcive();
	void init();
	bool isActive();
	void setRespawnTimeAt(int ticks);
	void decreaseRespawnTimer();
	int getTimeRemainingTorespawn();
	bool canRespawn();
private:
	bool active;
	int timeLeftToRespawn = 0;
};