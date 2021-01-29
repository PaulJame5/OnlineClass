#include "PathSystem.h"

PathSystem::PathSystem()
{
}

PathSystem::~PathSystem()
{
}

void PathSystem::update()
{
}

int PathSystem::getClosestPathID(TransformComponent& playerTransform)
{
	std::map<int, std::vector<PathComponent> >::iterator it = PathSystem::getEntities().begin();
	int id = -1;
	for (; it != PathSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		if (id == -1)
		{
			id = it->first;
			continue;
		}
		if (TransformSystem::getComponent(it->first).position.distanceFromSelf(playerTransform.position) <
			TransformSystem::getComponent(id).position.distanceFromSelf(playerTransform.position))
		{
			id = it->first;
		}
	}
	return id;
}
