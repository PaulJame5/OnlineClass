#pragma once
#include <string>

const std::string LEVEL_ONE_TILE_MAP_FILE = "Level/PacLevel.csv";
const std::string LEVEL_ONE_TILE_MAP_DIRECTION_FILE = "Level/PacLevels_DirectionLayer.csv";


const int WALL_TILE = 0;
const int PLAYER_ONE_START_POS_TILE = 2;
const int PLAYER_TWO_START_POS_TILE = 4;
const int DOT_TILE = 8;
const int BIG_DOT_TILE = 7;


// TILE CAN MOVE DIRECTIONS
const int TWO_UP_RIGHT = 13;
const int TWO_UP_LEFT = 14;
const int TWO_DOWN_LEFT = 15;
const int TWO_DOWN_RIGHT = 16;

const int THREE_UP_LEFT_RIGHT  = 17;
const int THREE_UP_LEFT_DOWN = 18;
const int THREE_LEFT_DOWN_RIGHT = 19;
const int THREE_UP_RIGHT_DOWN = 20;

const int FOUR_ALL_DIRECTION = 21;

// Tile Sizes
const int WIDTH = 32;
const int HEIGHT = 32;