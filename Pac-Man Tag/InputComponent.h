#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class InputComponent : public Component
{
public:
	InputComponent();
	~InputComponent();

	void detectInput(sf::Event& event);
	void detectInputLetGo(sf::Event& event);

	bool getUpKey();
	bool getDownKey();
	bool getLeftKey();
	bool getRightKey();

	void setBelongsToPlayerWithID(int playerEntityID);
	int getEntityControllingID();


private:
	bool upKey = false;
	bool upKeyPressed = false;
	bool downKey = false;
	bool downKeyPressed = false;
	bool leftKey = false;
	bool leftKeyPressed = false;
	bool rightKey = false;
	bool rightKeyPressed = false;

	void setUpKeys();
	void setDownKeys();
	void setLeftKeys();
	void setRightKeys();

	void setUpKeysUp();
	void setDownKeysUp();
	void setLeftKeysUp();
	void setRightKeysUp();


	int belongsToPlayerWithID = -1;
};