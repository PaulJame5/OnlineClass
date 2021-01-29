#include "ReadFromCSV.h"
#include <iostream>

ReadFromCSV::ReadFromCSV()
{
}

ReadFromCSV::~ReadFromCSV()
{
}


/// <summary>
/// Parse tile map data from a CSV file.
/// </summary>
/// <param name="myString">The string to write the data to.</param>
/// <param name="filename">The file name of the tile map.</param>
void ReadFromCSV::readTileMap(std::string& myString, std::string filename)
{
	std::ifstream myFile(filename);
	std::string currentLineRead;

	while (std::getline(myFile, currentLineRead))
	{
		myString += currentLineRead;
	}

	// Close the file
	myFile.close();
}

/// <summary>
/// Parse tile map data into a vector container.
/// </summary>
/// <param name="vec"></param>
/// <param name="filename"></param>
void ReadFromCSV::readTileMapIntoVector(std::vector<int>& vec, std::string filename)
{
	std::ifstream myFile(filename);
	std::string currentLineRead;

	while (std::getline(myFile, currentLineRead, ','))
	{
		vec.push_back(std::atoi(currentLineRead.c_str()));
	}

	// Close the file
	myFile.close();
}
