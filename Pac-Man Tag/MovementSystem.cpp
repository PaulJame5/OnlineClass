#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::update()
{
	std::map<int, std::vector<MovementComponent> >::iterator it = MovementSystem::getEntities().begin();

	for (; it != MovementSystem::getEntities().end(); ++it)
	{
		int numberOfComponents = it->second.size();

		for (int i = 0; i < numberOfComponents; i++)
		{
			it->second.at(i).move();

		}

	}
}

void MovementSystem::restart()
{
	std::map<int, std::vector<MovementComponent> >::iterator it = MovementSystem::getEntities().begin();
	for (; it != MovementSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		it->second.at(0).init();
	}
}
