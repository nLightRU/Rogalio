#pragma once
#include "floor.h"
class Dungeon
{
private:
	std::vector<Floor> _floors;
	int _currentFloor;
public:
	Dungeon();
	Dungeon(int numberOfFloors);
	int getCurrentFloor() { return _currentFloor; }
	std::vector<Floor> getFloors() { return _floors; }
};