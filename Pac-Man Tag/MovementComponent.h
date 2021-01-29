/*
	This is the movement component to be used by the player not the AI
*/
#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "Enums.h"
#include "ClientUDP.h"
#include "Globals.h"


class MovementComponent : public Component
{
public:
	MovementComponent();
	MovementComponent(float speed, TransformComponent& transformComponent);
	MovementComponent(const MovementComponent& movementComponent);
	~MovementComponent();
	void move();
	void increaseSpeed();

	void setPressed(bool pressedUp, bool pressedDown, bool pressedLeft, bool pressedRight);

	void setMyTransform(TransformComponent& transformComponent);
	char movementState = ' ';

	void init();
	static void setClient(ClientUDP* client);
	void setCanMoveRight();
	void setCanMoveLeft();
	void setCanMoveUp();
	void setCanMoveDown();

	void disableMoveRight();
	void disableMoveLeft();
	void disableMoveUp();
	void disableMoveDown();

	int lockToID = -1;
private:
	float speed;
	TransformComponent& myTransform;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	bool canMoveLeft = false;
	bool canMoveRight = false;
	bool canMoveDown = false;
	bool canMoveUp = false;

	const float MAXIMUM_SPEED = 3.0f;
	const float INCREASE_AMOUNT = 0.4f;
	static ClientUDP* client;
};