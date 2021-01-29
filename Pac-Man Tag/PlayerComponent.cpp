#include "PlayerComponent.h"

PlayerComponent::PlayerComponent()
{
	init();
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::init()
{
	pebblesAte = 0;
	chaser = true;
	caught = false;
}

void PlayerComponent::increasePebblesAte()
{
	pebblesAte++;
}

void PlayerComponent::resetPebbles()
{
	pebblesAte = 0;
}

void PlayerComponent::setAsChaser()
{
	chaser = true;
}

void PlayerComponent::setBeingChased()
{
	chaser = false;
}

bool PlayerComponent::isChaser()
{
	return chaser;
}

int PlayerComponent::getPebblesAte()
{
	return pebblesAte;
}

void PlayerComponent::setAsCaught()
{
	caught = true;
}

bool PlayerComponent::isCaught()
{
	return caught;
}
