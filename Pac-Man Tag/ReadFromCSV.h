#pragma once
#include <fstream>
#include <vector>
#include <string>
class ReadFromCSV
{
public:
	ReadFromCSV();
	~ReadFromCSV();

	static void readTileMap(std::string& myString, std::string filename);
	static void readTileMapIntoVector(std::vector<int>& vec, std::string filename);
};