#include "TransformSystem.h"
#include "SpriteSystem.h"
#include "PlayerStateHandlers.h"
#include "MovementSystem.h"

TransformSystem::TransformSystem()
{
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::update()
{
	std::map<int, std::vector<TransformComponent> >::iterator it = TransformSystem::getEntities().begin();

	for (; it != TransformSystem::getEntities().end(); ++it)
	{
		int numberOfComponents = it->second.size();

		for (int i = 0; i < numberOfComponents; i++)
		{
			ge::Vector2f pos = it->second.at(i).position;
			SpriteSystem::getComponents(it->first).at(i).setPosition(pos.x, pos.y);
		}

	}
}

void TransformSystem::syncOtherPosition(ge::Vector2i pos)
{
	for (int i = 0; i < PlayerStateHandler::playerEntityIDs.size(); i++)
	{
		if (PlayerStateHandler::playerEntityIDs.at(i) == PlayerStateHandler::myEntity)
		{
			continue;
		}
		MovementComponent& movementComponent = MovementSystem::getComponent(PlayerStateHandler::playerEntityIDs.at(i));
		TransformComponent& transformComponent = TransformSystem::getComponent(PlayerStateHandler::playerEntityIDs.at(i));

		if (movementComponent.movementState == UP)
		{
			if (transformComponent.position.y > pos.y)
			{
				transformComponent.position.y = pos.y;
			}
			transformComponent.position.x = pos.x;
			break;
		}
		if (movementComponent.movementState == DOWN)
		{
			if (transformComponent.position.y < pos.y)
			{
				transformComponent.position.y = pos.y;
			}
			transformComponent.position.x = pos.x;
			break;
		}
		if (movementComponent.movementState == LEFT)
		{
			if (transformComponent.position.x > pos.x)
			{
				transformComponent.position.x = pos.x;
			}
			transformComponent.position.y = pos.y;
			break;
		}
		if (movementComponent.movementState == RIGHT)
		{
			if (transformComponent.position.x < pos.x)
			{
				transformComponent.position.x = pos.x;
			}
			transformComponent.position.y = pos.y;
			break;
		}

	}
	
}
