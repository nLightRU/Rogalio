#pragma once
#include "floor.h"
class Dungeon
{
private:
	std::vector<Floor> _floors;
	int _currentFloorNumber;
public:
	Dungeon();
	Dungeon(int numberOfFloors);

	Floor getCurrentFloor() { return _floors[_currentFloorNumber]; }
	Floor getNextFloor() { _currentFloorNumber++; return _floors[_currentFloorNumber]; }

	int getCurrentFloorNumber() { return _currentFloorNumber; }
	std::vector<Floor> getFloors() { return _floors; }

	void setCurrentFloorNumber(int number) { _currentFloorNumber = number; }
};