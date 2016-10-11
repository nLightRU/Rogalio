#pragma once
#include "room.h"
#include <vector>

class Floor 
{
private:
	std::vector<Room> _rooms;
	int _number;
public: 
	int getNumber() { return _number; }
};