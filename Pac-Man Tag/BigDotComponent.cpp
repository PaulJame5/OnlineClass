#include "BigDotComponent.h"

BigDotComponent::BigDotComponent()
{
	active = true;
}

BigDotComponent::~BigDotComponent()
{
}

void BigDotComponent::Kill()
{
	active = false;
}

void BigDotComponent::SetAcive()
{
	active = true;
}

void BigDotComponent::init()
{
	active = true;
}

bool BigDotComponent::isActive()
{
	return active;
}



void BigDotComponent::setRespawnTimeAt(int ticks)
{
	timeLeftToRespawn = ticks;
}

void BigDotComponent::decreaseRespawnTimer()
{
	--timeLeftToRespawn;
}

int BigDotComponent::getTimeRemainingTorespawn()
{
	return timeLeftToRespawn;
}

bool BigDotComponent::canRespawn()
{
	if (timeLeftToRespawn <= 0)
	{
		active = true;
		return true;
	}
	return false;
}
