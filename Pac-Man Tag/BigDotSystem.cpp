#include "BigDotSystem.h"
#include "PlayerSystem.h"
#include "TransformSystem.h"
#include "SpriteSystem.h"
#include "Factory.h"

BigDotSystem::BigDotSystem()
{
}

BigDotSystem::~BigDotSystem()
{
}

void BigDotSystem::update()
{
	std::map<int, std::vector<BigDotComponent> >::iterator it = BigDotSystem::getEntities().begin();
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

	for (; it != BigDotSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		if (it->second.at(0).isActive() == false)
		{
			it->second.at(0).decreaseRespawnTimer();
			if (it->second.at(0).canRespawn())
			{
				SpriteSystem::getComponent(it->first).setEnabled();
			}
			continue;
		}
		for (int i = 0; i < playerTransforms.size(); i++)
		{
			if (playerTransforms.at(i).position.distanceFromSelf(TransformSystem::getComponent(it->first).position) < 15)
			{
				it->second.at(0).Kill();
				it->second.at(0).setRespawnTimeAt(1200);
				SpriteSystem::getComponent(it->first).disable();

				for (int j = 0; j < playerTransforms.size(); j++)
				{
					//self
					if (playerTransforms.at(j).position == playerTransforms.at(i).position)
					{
						PlayerSystem::getComponent(playerIds.at(j)).setAsChaser();
						SpriteSystem::removeComponent(playerIds.at(j));
						SpriteSystem::addComponent(playerIds.at(j), Factory::playerSprite);
						continue;
					}
					PlayerSystem::getComponent(playerIds.at(j)).setBeingChased();
					SpriteSystem::removeComponent(playerIds.at(j));
					SpriteSystem::addComponent(playerIds.at(j), Factory::ghostSprite);
				}
			}
		}
	}
}

void BigDotSystem::restart()
{
	std::map<int, std::vector<BigDotComponent> >::iterator it = BigDotSystem::getEntities().begin();
	for (; it != BigDotSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		it->second.at(0).init();
		SpriteSystem::getComponent(it->first).setEnabled();
	}
}
