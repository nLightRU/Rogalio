#pragma once
#include "floor.h"
class Dungeon
{
private:
	std::vector<Floor> _floors;
	int _currentFloorNumber;
	vec2 _playerPosition; 
public:
	Dungeon();
	Dungeon(int numberOfFloors);
	Floor getCurrentFloor() { return _floors[_currentFloorNumber]; }
	int getCurrentFloorNumber() { return _currentFloorNumber; }
	void setPlayerPosition(vec2 position) { _floors[_currentFloorNumber].setPlayersPosition(position); }
	void setCurrentFloorNumber(int number) { _currentFloorNumber = number; }
	std::vector<Floor> getFloors() { return _floors; }
};