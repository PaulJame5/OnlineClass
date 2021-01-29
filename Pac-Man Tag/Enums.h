#pragma once

enum GameState
{
	WAITING_FOR_PLAYER,
	PLAYING,
	FINISHED
};


enum WinnerState
{
	PLAYER_ONE,
	PLAYER_TWO,
	DRAW
};


enum ConnectionType
{
	HOST,
	CLIENT,
	DISCONNECTED
};

enum PlayerState
{
	Chaser,
	Ghost
};