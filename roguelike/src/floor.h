#pragma once
#include "room.h"
#include <vector>
#include <string>

class Floor 
{
private:
	std::vector<Room> _rooms;
	std::string _style; 
	int _number;

	const int _height = 56, _width = 175;

	char _flat[56][175];
	
	void GenerateRooms(int numberOfRooms);
	void AddLoot();
	void AddEnemies();

	void AddRooms();

public: 
	void SeparateRooms();

	Floor();
	Floor(int number, int numberOfRooms, std::string style);

	int getNumber() { return _number; }
	char getFlatTile(int i, int j) { return _flat[i][j]; }
	int getW() { return _width; }
	int getH() { return _height; }
	Room getRoom(int i) { return _rooms[i]; }
	std::string getStyle() { return _style; }

	void toFile(std::string FilePath);
};