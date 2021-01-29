#pragma once

#include "InputSystem.h"
#include "TransformSystem.h"
#include "Entity.h"
#include "MovementSystem.h"
#include "SpriteSystem.h"
#include "SpriteSheetFileDir.h"
#include "PlayerSystem.h"
#include <SFML/Graphics.hpp>
#include "SmallDotSystem.h"
#include "BigDotSystem.h"
#include "PathSystem.h"


class Factory
{
public:
	Factory();
	~Factory();

	static void createPlayer(ge::Vector2i startPosition);
	static void createWall(ge::Vector2i position);
	static void createDot(ge::Vector2i position);
	static void createBigDot(ge::Vector2i position);
	static void createDirectionTile(bool up, bool down, bool left, bool right, ge::Vector2i position);
	void test();

	static SpriteComponent playerSprite;
	static SpriteComponent wallSprite;
	static SpriteComponent dotSprite;
	static SpriteComponent bigDotSprite;
	static SpriteComponent ghostSprite;
private:
};