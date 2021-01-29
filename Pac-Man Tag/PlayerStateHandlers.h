#pragma once
#include <vector>
#include "Enums.h"


class PlayerStateHandler
{
public:
	PlayerStateHandler();
	~PlayerStateHandler();

	static int myEntity;

	static std::vector<int> playerEntityIDs;


	static ConnectionType myConnectionType;

	static char lastInputOtherPlayer;

private:
};