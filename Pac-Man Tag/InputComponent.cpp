#include "InputComponent.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "PlayerStateHandlers.h"

InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::detectInput(sf::Event& event)
{

	switch (event.key.code)
	{
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		setUpKeys();
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		setDownKeys();
		break;
	case sf::Keyboard::A:
	case sf::Keyboard::Left:
		setLeftKeys();
		break;
	case sf::Keyboard::D:
	case sf::Keyboard::Right:
		setRightKeys();
		break;
	default:
		break;
	}

}

void InputComponent::detectInputLetGo(sf::Event& event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		setUpKeysUp();
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		setDownKeysUp();
		break;
	case sf::Keyboard::A:
	case sf::Keyboard::Left:
		setLeftKeysUp();
		break;
	case sf::Keyboard::D:
	case sf::Keyboard::Right:
		setRightKeysUp();
		break;
	default:
		break;
	}
}

bool InputComponent::getUpKey()
{
	return upKey;
}

bool InputComponent::getDownKey()
{
	return downKey;
}

bool InputComponent::getLeftKey()
{
	return leftKey;
}

bool InputComponent::getRightKey()
{
	return rightKey;
}

void InputComponent::setBelongsToPlayerWithID(int playerEntityID)
{
	belongsToPlayerWithID = playerEntityID;
}

int InputComponent::getEntityControllingID()
{
	return belongsToPlayerWithID;
}

void InputComponent::setUpKeys()
{
	if (upKey)
	{
		upKeyPressed = false;
		return;
	}
	upKeyPressed = true;
	upKey = true;
}
void InputComponent::setDownKeys()
{
	if (downKey)
	{
		downKeyPressed = false;
		return;
	}
	downKeyPressed = true;
	downKey = true;
}
void InputComponent::setLeftKeys()
{
	if (leftKey)
	{
		leftKeyPressed = false;
		return;
	}
	leftKeyPressed = true;
	leftKey = true;
}
void InputComponent::setRightKeys()
{
	if (rightKey)
	{
		rightKeyPressed = false;
		return;
	}
	rightKeyPressed = true;
	rightKey = true;
}

void InputComponent::setUpKeysUp()
{
	upKey = false;
	upKeyPressed = false;
}

void InputComponent::setDownKeysUp()
{
	downKey = false;
	downKeyPressed = false;
}

void InputComponent::setLeftKeysUp()
{
	leftKey = false;
	leftKeyPressed = false;
}

void InputComponent::setRightKeysUp()
{
	rightKey = false;
	rightKeyPressed = false;
}
