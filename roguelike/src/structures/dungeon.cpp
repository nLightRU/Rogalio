#include "dungeon.h"
#include <time.h>
#include <string>
#include <iostream>
Dungeon::Dungeon()
{
	srand(time(NULL));
	_currentFloorNumber = 0;
}

Dungeon::Dungeon(int numberOfFloors)
{
	_currentFloorNumber = 0;
	for (int i = 0; i < numberOfFloors; i++)
	{
		srand(time(NULL));
		_floors.push_back(Floor(i, 50));
	}
}
