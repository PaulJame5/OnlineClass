#include "SmallDotComponent.h"

SmallDotComponent::SmallDotComponent()
{
	active = true;
}

SmallDotComponent::~SmallDotComponent()
{
}

void SmallDotComponent::Kill()
{
	active = false;
}

void SmallDotComponent::SetAcive()
{
	active = true;
}

void SmallDotComponent::init()
{
	active = true;
}

bool SmallDotComponent::isActive()
{
	return active;
}
