#include "MovementComponent.h"
#include "PacketData.h"
#include "PathSystem.h"

MovementComponent::MovementComponent() : myTransform(myTransform)
{
	speed = 1;
}

MovementComponent::MovementComponent(float speed, TransformComponent& transformComponent) : myTransform(transformComponent)
{
	this->speed = speed;
}

MovementComponent::MovementComponent(const MovementComponent& movementComponent) : myTransform ( movementComponent.myTransform)
{
	speed = movementComponent.speed;
	movementState = movementComponent.movementState;
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::move()
{
	switch (movementState)
	{
	case UP:
		moveUp();
		disableMoveLeft();
		disableMoveRight();
		setCanMoveDown();
		setCanMoveUp();
		break;
	case DOWN:
		moveDown();
		disableMoveLeft();
		disableMoveRight();
		setCanMoveDown();
		setCanMoveUp();
		break;
	case LEFT:
		moveLeft();
		disableMoveUp();
		disableMoveDown();
		setCanMoveLeft();
		setCanMoveRight();
		break;
	case RIGHT:
		moveRight();
		disableMoveUp();
		disableMoveDown();
		setCanMoveLeft();
		setCanMoveRight();
		break;
	default:
		break;
	}

}

void MovementComponent::increaseSpeed()
{
	if (speed < MAXIMUM_SPEED)
	{
		speed += INCREASE_AMOUNT;
	}
}


void MovementComponent::setPressed(bool pressedUp, bool pressedDown, bool pressedLeft, bool pressedRight)
{
	if (!pressedUp && !pressedDown && !pressedLeft && !pressedRight)
	{
		return;
	}
	if (pressedUp)
	{
		if (!canMoveUp)
		{
			return;
		}
		if (movementState == UP)
		{
			return;
		}
		movementState = UP;
		client->sendMessage(UP_PACKET);
		return;
	}
	if (pressedDown)
	{
		if (!canMoveDown)
		{
			return;
		}
		if (movementState == DOWN)
		{
			return;
		}
		movementState = DOWN;
		client->sendMessage(DOWN_PACKET);
		return;
	}
	if (pressedLeft)
	{
		if (!canMoveLeft)
		{
			return;
		}
		if (movementState == LEFT)
		{
			return;
		}
		movementState = LEFT;
		client->sendMessage(LEFT_PACKET);
		return;
	}
	if (pressedRight)
	{
		if (!canMoveRight)
		{
			return;
		}
		if (movementState == RIGHT)
		{
			return;
		}

		movementState = RIGHT;
		client->sendMessage(RIGHT_PACKET);
		return;
	}
}

void MovementComponent::setMyTransform(TransformComponent& transformComponent)
{
	myTransform = transformComponent;
}

void MovementComponent::init()
{
	movementState = ' ';
	speed = 1;
	lockToID = -1;
}

void MovementComponent::setClient(ClientUDP* clientPtr)
{
	client = clientPtr;
}

void MovementComponent::setCanMoveRight()
{
	canMoveRight = true;
}

void MovementComponent::setCanMoveLeft()
{
	canMoveLeft = true;
}

void MovementComponent::setCanMoveUp()
{
	canMoveUp = true;
}

void MovementComponent::setCanMoveDown()
{
	canMoveDown = true;
}

void MovementComponent::disableMoveRight()
{
	canMoveRight = false;
}

void MovementComponent::disableMoveLeft()
{
	canMoveLeft = false;
}

void MovementComponent::disableMoveUp()
{
	canMoveUp = false;
}

void MovementComponent::disableMoveDown()
{
	canMoveDown = false;
}

void MovementComponent::moveLeft()
{
	if (!canMoveLeft)
	{
		return;
	}
	myTransform.position.x -= speed;
	if (lockToID != -1)
	{
		if (myTransform.position.distanceFromSelf(TransformSystem::getComponent(lockToID).position) < 15)
		{
			myTransform.position.y = TransformSystem::getComponent(PathSystem::getClosestPathID(myTransform)).position.y;
		}
		sync = true;
	}
	if (myTransform.position.x < 0)
	{
		myTransform.position.x = 805;
	}
}

void MovementComponent::moveRight()
{
	if (!canMoveRight)
	{
		return;
	}
	myTransform.position.x += speed;
	if (lockToID != -1)
	{
		if (myTransform.position.distanceFromSelf(TransformSystem::getComponent(lockToID).position) < 15)
		{
			myTransform.position.y = TransformSystem::getComponent(PathSystem::getClosestPathID(myTransform)).position.y;
		}
		sync = true;
	}
	if (myTransform.position.x > 800)
	{
		myTransform.position.x = -5;
	}
}

void MovementComponent::moveUp()
{
	if (!canMoveUp)
	{
		return;
	}
	myTransform.position.y -= speed;
	if (lockToID != -1)
	{
		if (myTransform.position.distanceFromSelf(TransformSystem::getComponent(lockToID).position) < 15)
		{
			myTransform.position.x = TransformSystem::getComponent(PathSystem::getClosestPathID(myTransform)).position.x;
		}
		sync = true;
	}
	if (myTransform.position.y < 0)
	{
		myTransform.position.y = 950;
	}
}

void MovementComponent::moveDown()
{
	if (!canMoveDown)
	{
		return;
	}
	myTransform.position.y += speed;
	if (lockToID != -1)
	{
		if (myTransform.position.distanceFromSelf(TransformSystem::getComponent(lockToID).position) < 15)
		{
			myTransform.position.x = TransformSystem::getComponent(PathSystem::getClosestPathID(myTransform)).position.x;
		}
		
		sync = true;
	}
	if (myTransform.position.y > 950)
	{
		myTransform.position.y = -5;
	}
}

ClientUDP* MovementComponent::client = nullptr;
