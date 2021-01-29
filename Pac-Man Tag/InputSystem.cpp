#include "InputSystem.h"
#include "MovementSystem.h"
#include "PlayerStateHandlers.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	std::map<int, std::vector<InputComponent> >::iterator it = InputSystem::getEntities().begin();

	for (; it != InputSystem::getEntities().end(); ++it)
	{
		int numberOfComponents = it->second.size();

		for (int i = 0; i < numberOfComponents; i++)
		{
			if (!MovementSystem::hasComponent(it->first))
			{
				continue;
			}

			bool up = it->second.at(i).getUpKey();
			bool down = it->second.at(i).getDownKey();
			bool left = it->second.at(i).getLeftKey();
			bool right = it->second.at(i).getRightKey();
			MovementSystem::getComponent(it->first).setPressed(up, down, left, right);


			if (it->first != PlayerStateHandler::myEntity)
			{
				MovementSystem::getComponent(it->first).movementState = PlayerStateHandler::lastInputOtherPlayer;
			}
		}

	}
}

void InputSystem::inputCheck(sf::Event& event)
{
	std::map<int, std::vector<InputComponent> >::iterator it = InputSystem::getEntities().begin();

	for (; it != InputSystem::getEntities().end(); ++it)
	{
		int numberOfComponents = it->second.size();

		for (int i = 0; i < numberOfComponents; i++)
		{
			if (it->first == PlayerStateHandler::myEntity)
			{
				it->second.at(i).detectInput(event);
				continue;
			}
		}

	}
}

void InputSystem::inputLetGoCheck(sf::Event& event)
{
	std::map<int, std::vector<InputComponent> >::iterator it = InputSystem::getEntities().begin();

	for (; it != InputSystem::getEntities().end(); ++it)
	{
		int numberOfComponents = it->second.size();

		for (int i = 0; i < numberOfComponents; i++)
		{
			it->second.at(i).detectInputLetGo(event);
		}

	}
}
