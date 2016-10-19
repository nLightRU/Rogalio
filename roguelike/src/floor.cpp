#include "floor.h"
#include <math.h>

Floor::Floor(int n)
{
	_number = n;
	int w, h, x, y;
	for (int i = 0; i < 15; i++)
	{
		w = rand() % (15 - 5 + 1) + 5;
		h = w;

		x = 50 + rand() % 20 + 1;
		y = 28 + rand() % 15 + 1;

		_rooms.push_back(Room(x, y, w, h));
	}

	for (int i = 0; i < 55; i++)
		for (int j = 0; j < 150; j++)
			_flat[i][j] = '.';

	for (int i = 0; i < _rooms.size(); i++) 
		_flat[_rooms[i].getY()][_rooms[i].getX()] = 'x';

	/*
	for (unsigned int i = 0; i < _rooms.size(); i++) 
	{
		// top and bottom walls
		for (int j = 0; j <= _rooms[i].getW(); j++)
		{
			_flat[_height - _rooms[i].getY() - _rooms[i].getH()][_rooms[i].getX() + j] = '#';
			_flat[_height - _rooms[i].getY()][_rooms[i].getX() + j] = '#';
		}

		//left and right walls
		for (int j = 0; j <= _rooms[i].getH(); j++)
		{
			_flat[_height - _rooms[i].getY() - _rooms[i].getH() + j][_rooms[i].getX() + _rooms[i].getW()] = '#';
			_flat[_height - _rooms[i].getY() - _rooms[i].getH() + j][_rooms[i].getX()] = '#';
		}
	}*/

}
