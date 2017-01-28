#pragma once
#include "room.h"
#include <vector>
#include <string>

class Floor 
{
private:
	std::vector<Room> _rooms;
	std::vector<Room> _halls;
	int _number;

	const int _height = 100, _width = 175;

	char _flat[100][175];
	
	void GenerateRooms(int numberOfRooms);
	void SeparateRooms();
	void MadeGraph();
	void ConnectRooms();
	void AddLoot();
	void AddEnemies();

	void PlaceRooms();
	void toFile(std::string FilePath);

	char getFlatTile(int i, int j) { return _flat[i][j]; }
	Room getRoom(int i) { return _rooms[i]; }
	int getW() { return _width; }
	int getH() { return _height; }
public: 
	Floor();
	Floor(int number, int numberOfRooms);
	Floor(int numberOfRooms, std::string filePath);

	int getNumber() { return _number; }
};