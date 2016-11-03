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
	_top = y; 
	_bottom = y + height;
}

bool Room::touching(Room b)
{
	return !(_left > b.getR() || _right < b.getL() || _top > b.getB() || _bottom < b.getT());
}

void Room::shift(int x, int y)
{
	_x += x;
	_y -= y;
}