#pragma once
#include "room.h"
#include <vector>

class Floor 
{
private:
	std::vector<Room> _rooms;
	int _number;
	char _flat[55][150];
	int _height = 55, _width = 140; 
public: 
	Floor();
	Floor(int n);

	int getNumber() { return _number; }
	char getFlat(int i, int j) { return _flat[i][j]; }
	int getW() { return _width; }
	int getH() { return _height; }
};