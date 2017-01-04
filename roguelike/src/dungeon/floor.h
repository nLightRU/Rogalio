#pragma once
#include "room.h"
#include <vector>
#include <string>

class Floor 
{
private:
	std::vector<Room> _rooms;
	int _number;

	const int _height = 56, _width = 175;

	char _flat[56][175];
	
	void GenerateRooms(int numberOfRooms);
	void AddLoot();
	void AddEnemies();
	void PlaceRooms();


public: 
	Floor();
	Floor(int number, int numberOfRooms);

	int getNumber() { return _number; }
	char getFlatTile(int i, int j) { return _flat[i][j]; }
	int getW() { return _width; }
	int getH() { return _height; }
	Room getRoom(int i) { return _rooms[i]; }

	void SeparateRooms();
	void AddRoom(Room room) { _rooms.push_back(room); }
	void toFile(std::string FilePath);
};