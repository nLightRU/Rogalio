#include "room.h"
#include <math.h>
#include <iostream>
#include <ctime>

Room::Room()
{
	int x, y, w, h;


	srand(time(NULL));
	x = rand() % (125 - 20 + 1) + 20;
	y = rand() % (40 - 4 + 1) + 4;
	w = rand() % (20 - 10 + 1) + 10;
	h = rand() % (10 - 8 + 1) + 8;

	_x = x;
	_y = y; 
	_width = w;
	_height = h;

	_left = x;
	_right = x + _width;
	_top = y;
	_bottom = y + _height;
}

// x, y - coordinates of left bottom corner
Room::Room(int x, int y, int width, int height)
{
	_height = height;
	_width = width;
	_x = x;
	_y = y;

	_left = x; 
	_right = x + width;
	_top = y + height; 
	_bottom = y;
}

bool Room::touches(Room b)
{
	//bool insideA = _left > b._left && _right < b._right && _top > b._top && _bottom < b._bottom;
	//bool insideB = _left < b._left && _right > b._right && _top < b._top && _bottom > b._bottom;
	//if (!insideA) return true; 
	//if (!insideB) return true; 
	return !(_left > b._right || _right < b._left || _top > b._bottom || _bottom < b._top);
}

void Room::shift(int dx, int dy)
{
	_x += dx;
	_y += dy;
}

