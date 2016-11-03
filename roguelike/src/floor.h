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

	char _flat[48][155];
	int _height = 48, _width = 155;
	
	void GenerateRooms(int numberOfRooms);
	void SeparateRooms();
	void AddLoot();
	void AddEnemies();


public: 
	Floor();
	Floor(int number, int roomsCount, std::string style);

	int getNumber() { return _number; }
	char getFlatTile(int i, int j) { return _flat[i][j]; }
	int getW() { return _width; }
	int getH() { return _height; }
	Room getRoom(int i) { return _rooms[i]; }
	std::string getStyle() { return _style; }

	void toFile();
};