#include "room.h"
#include <math.h>
Room::Room() 
{
	_height = 0;
	_width = 0;
	_x = 0;
	_y = 0;
}

// x, y - coordinates of left bottom corner
Room::Room(int x, int y, int width, int height)
{
	_height = height;
	_width = width;
	_x = x;
	_y = y;
}

bool Room::touching(Room b) 
{
	return true;

}