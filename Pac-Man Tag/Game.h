#pragma once
#include <SFML/Graphics.hpp>
#include "TransformSystem.h"
#include "PlayerSystem.h"
#include "SpriteSystem.h"
#include "SmallDotSystem.h"
#include "BigDotSystem.h"
#include "MovementSystem.h"
#include "InputSystem.h"
#include "ReadFromCSV.h"
#include <thread>
#include "TileMapFileDir.h"

#include "ClientUDP.h"
#include "ServerUDP.h"
#include "Globals.h"

#include <SFML/Audio.hpp>

class Game
{
public:
	Game();
	~Game();

	void run();

	void render(sf::RenderWindow &window);
	// pass window for polling events
	void update();
	


private:
	// Declare our systems here
	TransformSystem transformSystem = TransformSystem();
	MovementSystem movementSystem;
	SpriteSystem spriteSystem;
	InputSystem inputSystem;
	PlayerSystem playerSystem = PlayerSystem();
	SmallDotSystem smallDotSystem;
	BigDotSystem bigDotSystem;


	// for invoking our servers + client
	std::vector<std::thread> serverThreads;

	void setupLevel();
	void setupDirections();

	ge::Vector2i playerOneStartPosition;
	ge::Vector2i playerTwoStartPosition;
	ge::Vector2i playerThreeStartPosition;


	ServerUDP server = ServerUDP();
	ClientUDP* client = new ClientUDP();

	void initGameScene();
	void syncPosition();
	int frameTickToWait = 180;
	bool waitToReset();
	int waitToResetAmount = 180;

	bool gameStarted = false;
	bool jinglePlayed = false;

	// Set Up Sounds
	sf::SoundBuffer munchSFX;
	sf::SoundBuffer startupBuffer;
	// load something into the sound buffer...
	sf::Sound startup;
	sf::Sound munchSound[5];


	sf::Font font;
	sf::Text gameText;

};