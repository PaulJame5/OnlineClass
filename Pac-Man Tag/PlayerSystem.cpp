#include "PlayerSystem.h"
#include "Factory.h"
#include "TransformSystem.h"
#include "MovementSystem.h"
#include "PathSystem.h"
#include "Globals.h"


PlayerSystem::PlayerSystem()
{
}

PlayerSystem::~PlayerSystem()
{
}

void PlayerSystem::restart()
{
	std::map<int, std::vector<PlayerComponent> >::iterator it = PlayerSystem::getEntities().begin();

	for (; it != PlayerSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		it->second.at(0).init();
		TransformSystem::getComponent(it->first).init();
		SpriteSystem::destroyComponent(it->first);
		SpriteSystem::addComponent(it->first, Factory::playerSprite);
	}
}

void PlayerSystem::update()
{
	std::vector<int> ids = std::vector<int>();
	checkSpeedIncrease(ids);
	checkPlayersCollide(ids);
	setCanMovePath(ids);
}

void PlayerSystem::checkSpeedIncrease(std::vector<int>& ids)
{
	std::map<int, std::vector<PlayerComponent> >::iterator it = PlayerSystem::getEntities().begin();

	for (; it != PlayerSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		ids.push_back(it->first);

		if (it->second.at(0).getPebblesAte() >= 10)
		{
			MovementSystem::getComponent(it->first).increaseSpeed();
			it->second.at(0).resetPebbles();
		}

	}
}

void PlayerSystem::checkPlayersCollide(std::vector<int>& ids)
{
	int size = ids.size();
	if (size <= 1)
	{
		return;
	}

	for (int i = 0; i < size; i++)
	{
		if (TransformSystem::getComponents(ids.at(i)).size() == 0)
		{
			continue;
		}
		for (int j = 1 + i; j < size; j++)
		{
			if (i + j >= size)
			{
				break;
			}
			if (TransformSystem::getComponents(ids.at(i + j)).size() == 0)
			{
				continue;
			}

			if (TransformSystem::getComponent(ids.at(i)).position.distanceFromSelf(TransformSystem::getComponent(ids.at(i + j)).position) < 16)
			{
				if (PlayerSystem::getComponent(ids.at(i)).isChaser() && PlayerSystem::getComponent(ids.at(i + j)).isChaser())
				{
					continue;
				}

				if (PlayerSystem::getComponent(ids.at(i)).isChaser() == false && PlayerSystem::getComponent(ids.at(i + j)).isChaser() == false)
				{
					continue;
				}

				if (PlayerSystem::getComponent(ids.at(i)).isChaser() == false && PlayerSystem::getComponent(ids.at(i + j)).isChaser() == true)
				{
					playerOneWin = false;
					playerTwoWin = true;
					PlayerSystem::getComponent(ids.at(i)).setAsCaught();
					MovementSystem::getComponent(ids.at(i)).movementState = ' ';
					MovementSystem::getComponent(ids.at(i + j)).movementState = ' ';
					break;
				}
				if (PlayerSystem::getComponent(ids.at(i)).isChaser() == true && PlayerSystem::getComponent(ids.at(i + j)).isChaser() == false)
				{
					playerOneWin = true;
					playerTwoWin = false;
					PlayerSystem::getComponent(ids.at(i + j)).setAsCaught();
					MovementSystem::getComponent(ids.at(i)).movementState = ' ';
					MovementSystem::getComponent(ids.at(i + j)).movementState = ' ';
					continue;
				}
			}
		}
	}
}

void PlayerSystem::setCanMovePath(std::vector<int>& ids)
{

	std::map<int, std::vector<PathComponent> >::iterator it = PathSystem::getEntities().begin();

	for (; it != PathSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		for (int i = 0; i < ids.size(); i++)
		{
			if (TransformSystem::getComponent(it->first).position.distanceFromSelf(TransformSystem::getComponent(ids.at(i)).position) <= 9)
			{
				// Down
				if (it->second.at(0).canMoveDown)
				{
					MovementSystem::getComponent(ids.at(i)).setCanMoveDown();
					MovementSystem::getComponent(ids.at(i)).lockToID = it->first;
				}
				else
				{
					MovementSystem::getComponent(ids.at(i)).disableMoveDown();
				}
				// Up
				if (it->second.at(0).canMoveUp)
				{
					MovementSystem::getComponent(ids.at(i)).setCanMoveUp();
					MovementSystem::getComponent(ids.at(i)).lockToID = it->first;
				}
				else
				{
					MovementSystem::getComponent(ids.at(i)).disableMoveUp();
				}
				// Left
				if (it->second.at(0).canMoveLeft)
				{
					MovementSystem::getComponent(ids.at(i)).setCanMoveLeft();
					MovementSystem::getComponent(ids.at(i)).lockToID = it->first;
				}
				else
				{
					MovementSystem::getComponent(ids.at(i)).disableMoveLeft();
				}
				// Right
				if (it->second.at(0).canMoveRight)
				{
					MovementSystem::getComponent(ids.at(i)).setCanMoveRight();
					MovementSystem::getComponent(ids.at(i)).lockToID = it->first;
				}
				else
				{
					MovementSystem::getComponent(ids.at(i)).disableMoveRight();
				}
			}
		}
	}
}

bool PlayerSystem::playerCaught()
{
	std::map<int, std::vector<PlayerComponent> >::iterator it = PlayerSystem::getEntities().begin();

	for (; it != PlayerSystem::getEntities().end(); ++it)
	{
		if (it->second.size() < 1)
		{
			continue;
		}
		if (it->second.at(0).isCaught())
		{
			return true;
		}
	}
	return false;
}
