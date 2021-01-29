#include "PlayerStateHandlers.h"

PlayerStateHandler::PlayerStateHandler()
{
}

PlayerStateHandler::~PlayerStateHandler()
{
}

int PlayerStateHandler::myEntity = -1;
std::vector<int> PlayerStateHandler::playerEntityIDs = std::vector<int>();
ConnectionType PlayerStateHandler::myConnectionType = ConnectionType::DISCONNECTED; 

char PlayerStateHandler::lastInputOtherPlayer = ' ';