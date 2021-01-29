#pragma once
#include "Factory.h"
#include "PlayerStateHandlers.h"

Factory::Factory()
{
}

Factory::~Factory()
{
}

void Factory::createPlayer(ge::Vector2i startPosition)
{
	Entity entity = Entity();

	SpriteSystem::addComponent(entity.getId(), playerSprite);
	TransformSystem::addComponent(entity.getId());
	TransformSystem::getComponent(entity.getId()).position = startPosition;
	TransformSystem::getComponent(entity.getId()).initialPosition = startPosition;
	MovementComponent movementComponent = MovementComponent(1, TransformSystem::getComponent(entity.getId()));
	MovementSystem::addComponent(entity.getId(), movementComponent);
	InputSystem::addComponent(entity.getId());
	PlayerSystem::addComponent(entity.getId());

	// For our online input
	PlayerStateHandler::playerEntityIDs.push_back(entity.getId());
}

void Factory::createWall(ge::Vector2i position)
{
	Entity entity = Entity();
	wallSprite.setPosition(position.x, position.y);
	SpriteSystem::addComponent(entity.getId(), wallSprite);
}

void Factory::createDot(ge::Vector2i position)
{
	Entity entity = Entity();
	dotSprite.setPosition(position.x, position.y);
	SpriteSystem::addComponent(entity.getId(), dotSprite);
	TransformSystem::addComponent(entity.getId());
	TransformSystem::getComponent(entity.getId()).position = position;
	SmallDotSystem::addComponent(entity.getId());
}

void Factory::createBigDot(ge::Vector2i position)
{
	Entity entity = Entity();
	bigDotSprite.setPosition(position.x, position.y);
	SpriteSystem::addComponent(entity.getId(), bigDotSprite);
	TransformSystem::addComponent(entity.getId());
	TransformSystem::getComponent(entity.getId()).position = position;
	BigDotSystem::addComponent(entity.getId());
}

void Factory::createDirectionTile(bool up, bool down, bool left, bool right, ge::Vector2i position)
{
	Entity entity = Entity();
	bigDotSprite.setPosition(position.x, position.y);
	//SpriteSystem::addComponent(entity.getId(), bigDotSprite);
	////SpriteSystem::getComponent(entity.getId()).disable();
	PathComponent pathComponent = PathComponent(up, down, left, right);
	PathSystem::addComponent(entity.getId(), pathComponent);
	TransformSystem::addComponent(entity.getId());
	TransformSystem::getComponent(entity.getId()).position = position;
}

void Factory::test()
{
	Entity entity = Entity();

	SpriteSystem::addComponent(entity.getId(), playerSprite);
}

// static factory settings
SpriteComponent Factory::playerSprite = SpriteComponent(PLAYER_SPRITE_SHEET, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)), true);
SpriteComponent Factory::wallSprite = SpriteComponent(WALL_SPRITE_IMG, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)), false);
SpriteComponent Factory::dotSprite = SpriteComponent(DOT_SPRITE_IMG, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)), false);
SpriteComponent Factory::bigDotSprite = SpriteComponent(BIG_DOT_SPRITE_IMG, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)), false);
SpriteComponent Factory::ghostSprite = SpriteComponent(GHOST_SPRITE, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)), false);

