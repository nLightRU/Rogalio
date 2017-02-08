#include "dungeon.h"
#include <time.h>

Dungeon::Dungeon()
{
	for (int i = 0; i < 10; i++) 
	{
		srand(time(NULL));
		_floors.push_back(Floor(i, 50));
	}
}

Dungeon::Dungeon(int numberOfFloors)
{
	for (int i = 0; i < numberOfFloors; i++)
	{
		srand(time(NULL));
		_floors.push_back(Floor(i, 50));
	}
}
