#include "Game.h"
#include <SFML/Graphics.hpp>
#include "SpriteSystem.h"
#include "TransformSystem.h"
#include "SpriteSheetFileDir.h"
#include "Entity.h"
#include "Factory.h"
#include <thread>
#include "PlayerStateHandlers.h"



Game::Game()
{
	if (!munchSFX.loadFromFile(MUNCH_SFX_DIR))
	{
		std::cout << "Cannot Find File: " << MUNCH_SFX_DIR << std::endl;
	}
	for (int i = 0; i < 5; i++)
	{
		munchSound[i].setBuffer(munchSFX);
	}
	if (!startupBuffer.loadFromFile(STARTUP_JINGLE_DIR))
	{
		std::cout << "Cannot Find File: " << STARTUP_JINGLE_DIR << std::endl;
	}
	startup.setBuffer(startupBuffer);

	if (!font.loadFromFile(FONT_GAME))
	{
		std::cout << "Cannot Find File: " << FONT_GAME << std::endl;
	}
	gameText.setFont(font);
	gameText.setCharacterSize(12);
	gameText.setFillColor(sf::Color::Red);
	gameText.setPosition(330, 475);
}

Game::~Game()
{
	client = nullptr;
}
void Game::run()
{
	sf::RenderWindow window(sf::VideoMode(800, 950), "Pac-Man Tag!");

	Factory factory;
	MovementComponent::setClient(client);
	setupLevel();
	setupDirections();

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					if (PlayerStateHandler::myConnectionType != ConnectionType::CLIENT
						&& PlayerStateHandler::myConnectionType != ConnectionType::HOST)
					{
						factory.createPlayer(playerOneStartPosition);
						factory.createPlayer(playerTwoStartPosition);
						// Self
						server.setup();
						serverThreads.push_back(std::thread(&ServerUDP::run, server));
						PlayerStateHandler::myConnectionType = ConnectionType::HOST;
						PlayerStateHandler::myEntity = PlayerStateHandler::playerEntityIDs.at(0);
						initGameScene();
						// Clients to self to send and push data
						client->setup(SERVER, PORT);
						serverThreads.push_back(std::thread(&ClientUDP::receive, client));
					}
					break;
				}
				if (event.key.code == sf::Keyboard::C)
				{
					if (PlayerStateHandler::myConnectionType != ConnectionType::CLIENT 
						&& PlayerStateHandler::myConnectionType != ConnectionType::HOST)
					{
						factory.createPlayer(playerOneStartPosition);
						factory.createPlayer(playerTwoStartPosition);
						PlayerStateHandler::myConnectionType = ConnectionType::CLIENT;
						server.numberOfClients = 2;
						PlayerStateHandler::myEntity = PlayerStateHandler::playerEntityIDs.at(1); 
						initGameScene();
						client->setup(SERVER, PORT);
						serverThreads.push_back(std::thread(&ClientUDP::receive, client));
					}
					break;
				}
				inputSystem.inputCheck(event);
				break;
			}
			if (event.type == sf::Event::KeyReleased)
			{
				inputSystem.inputLetGoCheck(event);
				break;
			}

		}

		update();
		render(window);
	}
}

void Game::render(sf::RenderWindow &window)
{
	window.clear();
	SpriteSystem::drawSprites(window);
	window.draw(gameText);
	// Draw UI 
	window.display();
}

void Game::update()
{
	if (!jinglePlayed)
	{
		if (server.numberOfClients < 2)
		{
			gameText.setString("Waiting4Player");
			return;
		}
		startup.play();
		gameText.setString("Get Ready!");
		jinglePlayed = true;
	}
	if (!gameStarted)
	{
		if (startup.getStatus() != startup.Playing)
		{
			gameStarted = true;
			gameText.setString("");
		}
		return;
	}


	if (!playerSystem.playerCaught())
	{
		playerSystem.update();
		inputSystem.update();
		movementSystem.update();
		spriteSystem.update();
		transformSystem.update();
		smallDotSystem.update(munchSound);
		bigDotSystem.update();
	}

	if (playerSystem.playerCaught())
	{
		if (playerSystem.getComponent(PlayerStateHandler::myEntity).isCaught())
		{

			gameText.setString("You Lose!");
		}
		else
		{
			gameText.setString("You Win!");
		}
		if (waitToReset())
		{
			return;
		}
		initGameScene();
		return;
	}


	syncPosition();
}

void Game::setupLevel()
{

	std::vector<int> mapInt = std::vector<int>();
	ReadFromCSV::readTileMapIntoVector(mapInt, LEVEL_ONE_TILE_MAP_FILE);

	int size = mapInt.size();

	int currentX = 0;
	int currentY = 0;

	for (int i = 0; i < size; i++)
	{

		switch (mapInt[i])
		{
		case WALL_TILE:
			Factory::createWall(ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case DOT_TILE:
			Factory::createDot(ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case BIG_DOT_TILE:
			Factory::createBigDot(ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case PLAYER_ONE_START_POS_TILE:
			playerOneStartPosition = ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8);
			break;
		case PLAYER_TWO_START_POS_TILE:
			playerTwoStartPosition = ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8);
			break;
		default:
			break;
		}

		++currentX;
		if (currentX > 31)
		{
			++currentY;
			currentX = 0;
		}
	}
}

void Game::setupDirections()
{
	std::vector<int> mapInt = std::vector<int>();
	ReadFromCSV::readTileMapIntoVector(mapInt, LEVEL_ONE_TILE_MAP_DIRECTION_FILE);

	int size = mapInt.size();

	int currentX = 0;
	int currentY = 0;

	for (int i = 0; i < size; i++)
	{

		switch (mapInt[i])
		{
		case TWO_DOWN_LEFT:
			Factory::createDirectionTile(false, true, true, false, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case TWO_DOWN_RIGHT:
			Factory::createDirectionTile(false, true, false, true, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case TWO_UP_LEFT:
			Factory::createDirectionTile(true, false, true, false, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case TWO_UP_RIGHT:
			Factory::createDirectionTile(true, false, false, true, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case THREE_LEFT_DOWN_RIGHT:
			Factory::createDirectionTile(false, true, true, true, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case THREE_UP_LEFT_DOWN:
			Factory::createDirectionTile(true, true, true, false, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case THREE_UP_LEFT_RIGHT:
			Factory::createDirectionTile(true, false, true, true, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case THREE_UP_RIGHT_DOWN:
			Factory::createDirectionTile(true, true, false, true, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
			break;
		case FOUR_ALL_DIRECTION:
			Factory::createDirectionTile(true, true, true, true, ge::Vector2i((currentX * WIDTH) + 16, (currentY * HEIGHT) + 8));
		default:
			break;
		}

		++currentX;
		if (currentX > 31)
		{
			++currentY;
			currentX = 0;
		}
	}
}

void Game::initGameScene()
{
	playerSystem.restart();
	smallDotSystem.restart();
	bigDotSystem.restart();
	movementSystem.restart();
	MovementSystem::getComponent(PlayerStateHandler::playerEntityIDs.at(0)).setCanMoveLeft();
	MovementSystem::getComponent(PlayerStateHandler::playerEntityIDs.at(0)).setCanMoveRight();
	MovementSystem::getComponent(PlayerStateHandler::playerEntityIDs.at(1)).setCanMoveLeft();
	MovementSystem::getComponent(PlayerStateHandler::playerEntityIDs.at(1)).setCanMoveRight();
	MovementSystem::getComponent(PlayerStateHandler::playerEntityIDs.at(1)).setCanMoveUp();
	gameStarted = false;
	jinglePlayed = false;
	playerOneWin = false;
	playerTwoWin = false;
}

void Game::syncPosition()
{
	frameTickToWait--;

	if (frameTickToWait <= 0 || sync)
	{
		std::string m = SYNC_POSITION_NOTIFICATION;
		m += TransformSystem::getComponent(PlayerStateHandler::myEntity).position.toString();
		client->sendMessage(m.c_str());
		frameTickToWait = 20;
		sync = false;
	}
}

bool Game::waitToReset()
{
	if (--waitToResetAmount > 0)
	{
		return true;
	}
	waitToResetAmount = 180;
	return false;
}
