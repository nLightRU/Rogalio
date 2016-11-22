#include "floor.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

Floor::Floor()
{
	_number = 0; 

	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_flat[y][x] = '.';
}

Floor::Floor(int number, int numberOfRooms, std::string style)
{
	_number = number;
	GenerateRooms(numberOfRooms);
	SeparateRooms();
	AddLoot();

	// this funcs for ASCII graph
	PlaceRooms();
}

void Floor::GenerateRooms(int numberOfRooms)
{
	srand(time(NULL));
	int w, h, x, y;
	for (int i = 0; i < numberOfRooms; i++)
	{
		x = rand() % (80 - 68 + 1) + 68;
		y = rand() % (15 - 10 + 1) + 15;
		w = 7; //rand() % (20 - 15 + 1) + 15;
		h = 7; // rand() % (10 - 8 + 1) + 8;

		_rooms.push_back(Room(x, y, w, h));
	}
}

void Floor::SeparateRooms()
{
	int dx, dy, dxa, dxb, dya, dyb;
	bool touching = true;

	while (touching)
	{
		for (unsigned int a = 0; a < _rooms.size(); a++) 
		{
			std::cout << "Separate iteration " << a+1 << std::endl; 
			for (unsigned int b = a + 1; b < _rooms.size(); b++)
				if (_rooms[a].touches(_rooms[b]))
				{

					dx = fmin(abs(_rooms[a].getR() - _rooms[b].getL()) + 1, abs(_rooms[a].getL() - _rooms[b].getR()) + 1);
					dy = fmin(abs(_rooms[a].getB() - _rooms[b].getT()) - 1, abs(_rooms[a].getT() - _rooms[b].getB()) - 1);

					if (dx < dy) dy = 0;
					else dx = 0;

					dxa = -dx / 2;
					dya = -dy / 2;

					dxb = dx / 2;
					dyb = dy / 2;

					_rooms[a].shift(dxa, dya);
					_rooms[b].shift(dxb, dyb);
				}
			}
		touching = false;
	}
}

void Floor::AddLoot()
{

}

void Floor::AddEnemies()
{

}

void Floor::toFile(std::string filePath)
{
	std::ofstream map_f(filePath);

	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_flat[y][x] = '.';

	PlaceRooms();
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
			map_f << _flat[y][x];
		map_f << std::endl;
	}
}

void Floor::PlaceRooms()
{
	for (int i = 0; i < _rooms.size(); i++)
	{
		// top and bot
		for (int x = 0; x <= _rooms[i].getW(); x++)
		{
			_flat[_rooms[i].getY()][_rooms[i].getX() + x] = '#';
			_flat[_rooms[i].getY() + _rooms[i].getH()][_rooms[i].getX() + x] = '#';
		}

		// left and right
		for (int y = 0; y <= _rooms[i].getH(); y++)
		{
			_flat[_rooms[i].getY() + y][_rooms[i].getX()] = '#';
			_flat[_rooms[i].getY() + y][_rooms[i].getX() + _rooms[i].getW()] = '#';
		}
	}
}