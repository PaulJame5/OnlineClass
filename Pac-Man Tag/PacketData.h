#pragma once
#include <string>
// all mesage types that are sent via packets with client to server

// Movement
const char UP = 'u';
const char DOWN = 'd';
const char LEFT = 'l';
const char RIGHT = 'r';

const char UP_PACKET[2] = "u";
const char DOWN_PACKET[2] = "d";
const char LEFT_PACKET[2] = "l";
const char RIGHT_PACKET[2] = "r";

// Swap State
const char SET_AS_GHOST[2] = "g";

// Game State
const char GAME_OVER[2] = "e";
const char START[2] = "c";
const char RESET[2] = "w";

// Server Client
const char JOINED_SERVER[2] = "o";
const char PLAYER_JOINED[2] = "i";

const char CONNECTED_PACKET[2] = "5";
const char EXIT_PACKET[2] = "6";
const char SERVER_CLOSED[2] = "7";

const char SYNC_POSITION_NOTIFICATION[3] = "sy";


