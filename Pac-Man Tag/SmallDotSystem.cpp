#include "SmallDotSystem.h"
#include "PlayerSystem.h"
#include "TransformSystem.h"
#include "SpriteSystem.h"

SmallDotSystem::SmallDotSystem()
{
}

SmallDotSystem::~SmallDotSystem()
{
}

void SmallDotSystem::update(sf::Sound sound[])
{
	std::map<int, std::vector<SmallDotComponent> >::iterator it = SmallDotSystem::getEntities().begin();
	std::vector<int> ids = std::vector<int>();
	
	std::map<int, std::vector<PlayerComponent> >::iterator itPlayer = PlayerSystem::getEntities().begin();
	std::vector<int> playerIds = std::vector<int>();
	std::vector<TransformComponent> playerTransforms;

	for (; itPlayer != PlayerSystem::getEntities().end(); ++itPlayer)
	{
		if (itPlayer->second.size() < 1)
		{
			continue;
		}
		playerIds.push_back(itPlayer->first);
	}
	if (playerIds.size() > 0)
	{
		playerTransforms.push_back(TransformSystem::getComponent(playerIds.at(0)));
	}

	if (playerIds.size() > 1)
	{
		playerTransforms.push_back(TransformSystem::getComponent(playerIds.at(1)));
	}

	for (; it != SmallDotSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		if (it->second.at(0).isActive() == false)
		{
			continue;
		}
		for (int i = 0; i < playerTransforms.size(); i++)
		{
			if (playerTransforms.at(i).position.distanceFromSelf(TransformSystem::getComponent(it->first).position) < 15)
			{
				it->second.at(0).Kill();
				for (int k = 0; k < 5; k++)
				{
					if (sound[k].getStatus() != sound->Playing)
					{
						sound[k].play();
						break;
					}
				}
				
				SpriteSystem::getComponent(it->first).disable();
				PlayerSystem::getComponent(playerIds.at(i)).increasePebblesAte();
			}
		}

		
		
	}
}

void SmallDotSystem::update()
{
}

void SmallDotSystem::restart()
{
	std::map<int, std::vector<SmallDotComponent> >::iterator it = SmallDotSystem::getEntities().begin();
	for (; it != SmallDotSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		it->second.at(0).init();
		SpriteSystem::getComponent(it->first).setEnabled();
	}
}
