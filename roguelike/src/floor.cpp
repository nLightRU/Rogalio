#include "floor.h"
#include <math.h>

Floor::Floor(int n)
{
	_number = n;
	int w, h, x, y;
	for (int i = 0; i < 10; i++)
	{
		w = rand() % (20 - 10 + 1) + 10;
		h = rand() % (20 - 10 + 1) + 10;

		x = rand() % 140 + 1;
		y = rand() % (55 - 20 + 1) + 20;

		_rooms.push_back(Room(x, y, w, h));
	}

	for (int i = 0; i < 55; i++)
		for (int j = 0; j < 150; j++)
			this->_flat[i][j] = '.';


	for (unsigned int i = 0; i < _rooms.size() - 1; i++) 
	{

		// top and bottom walls
		for (int j = 0; j < _rooms[i].getW(); j++)
		{
			_flat[_height - _rooms[i].getY() - _rooms[i].getH()][_rooms[i].getX() + j] = '#';
			_flat[_height - _rooms[i].getY()][_rooms[i].getX() + j] = '#';
		}

		//left and right walls
		for (int j = 0; j < _rooms[i].getH(); j++)
		{
			_flat[_height - _rooms[i].getY() - _rooms[i].getH() + j][_rooms[i].getX()] = '#';
			_flat[_height - _rooms[i].getY() - _rooms[i].getH() + j][_rooms[i].getX() + _rooms[0].getW()] = '#';
		}
	}


}
