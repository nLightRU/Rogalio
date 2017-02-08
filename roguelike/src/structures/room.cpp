#include "room.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <math.h>
#include "../math/vec2.h"

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

	_joiningLeft = -1;
	_joiningRight = -1;
}

// x, y - coordinates of left top corner
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

	_center.x = x / 2;
	_center.y = y / 2;
}

bool Room::touches(Room b)
{
	return !(_left >= b._right ||
		_right <= b._left ||
		_top >= b._bottom ||
		_bottom <= b._top);
}

void Room::shift(int dx, int dy)
{
	_x += dx;
	_y += dy;

	_left = _x;
	_right = _x + _width;

	_top = _y;
	_bottom = _y + _height;

	_center.x = _x + _width / 2;
	_center.y = _y + _height / 2;
}

void Room::setX(int x)
{
	_x = x;
	_left = _x;
	_right = _x + _width;
	_center.x = x / 2;
}

void Room::setY(int y)
{
	_y += y;
	_top = _y;
	_bottom = _y + _height;
	_center.y = y / 2;
}

void Room::setJoinings(int right, int left)
{
	_joiningRight = right;
	_joiningLeft = left;
}

void Room::setLeftJoining(int index)
{
	_joiningLeft = index;
}

void Room::setRightJoining(int index)
{
	_joiningRight = index;
}

void Room::setParent(int index)
{
	_parent = index;
}

int Room::countDistance(Room b)
{
	return _center.squareDistance(b.getCenter());
}

bool Room::includePoint(vec2 point)
{
	bool first = point.x > _left &&
		point.x < _right &&
		point.y < _bottom &&
		point.y > _top;
	return first;
}