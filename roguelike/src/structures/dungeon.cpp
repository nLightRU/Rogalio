#include "dungeon.h"
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
Dungeon::Dungeon()
{
	srand(time(NULL));
	_currentFloorNumber = 0;
}

Dungeon::Dungeon(int numberOfFloors)
{
	std::vector<int> numbersOfRooms;
	std::vector<int> widths; 
	std::vector<int> heights;
	std::vector<int> xcoords;
	std::vector<int> ycoords;
	for (int i = 0; i < numberOfFloors; i++)
	{
		numbersOfRooms.push_back(rand() % (50 - 40 + 1) + 40);
		widths.push_back(rand() % (20 - 15 + 1) + 15);
		heights.push_back(rand() % (20 - 15 + 1) + 15);
		xcoords.push_back(rand() % (200 - 150 + 1) + 150);
		ycoords.push_back(rand() % (200 - 150 + 1) + 150);
	}

	_currentFloorNumber = 0;

	for (int i = 0; i < numberOfFloors; i++)
	{
		srand(time(NULL));
		_floors.push_back(Floor(i, numbersOfRooms[i], widths[i], 
			heights[i], xcoords[i], ycoords[i]));
	}
}
