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

Floor::Floor(int number, int numberOfRooms)
{
	_number = number;
	GenerateRooms(numberOfRooms);
	//toFile("rooms.txt");
	SeparateRooms();
	toFile("separated rooms.txt");
	AddLoot();
}

Floor::Floor(int numberOfRooms, std::string filePath)
{
	_number = 0;
	GenerateRooms(numberOfRooms);
	SeparateRooms();
	toFile(filePath);
}

void Floor::GenerateRooms(int numberOfRooms)
{
	srand(time(NULL));

	int w, h, x, y, j;

	Room tempRoom;

	for (int i = 0; i < numberOfRooms; i++)
	{
		x = rand() % (80 - 50 + 1) + 50;
		y = rand() % (40 - 15 + 1) + 15;
		w = rand() % (15 - 3 + 1) + 3; //15;
		h = rand() % (15 - 3 + 1) + 3; //15; 

		if (w / h < 1) continue;
		_rooms.push_back(Room(x, y, w, h));

		/*j = i;

		while (j > 0)
		{
			if (_rooms[j].getSquare() > _rooms[j - 1].getSquare())
			{
				tempRoom = _rooms[j];
				_rooms[j] = _rooms[j + 1];
				_rooms[j + 1] = tempRoom;
			}
			j--;
		}*/

		for (int j = 0; j < _rooms.size(); j++)
			for (int k = 0; k < _rooms.size() - 1 - j; k++)
				if (_rooms[k].getSquare() < _rooms[k + 1].getSquare())
				{
					tempRoom = _rooms[k];
					_rooms[k] = _rooms[k + 1]; 
					_rooms[k + 1] = tempRoom;
				}
	}
}

void Floor::SeparateRooms()
{
	int dx, dy, dxa, dxb, dya, dyb;
	bool touching = true;

	int step = 1;

	while (touching)
	{
		touching = false;
		for (unsigned int a = 0; a < _rooms.size(); a++)
		{
			for (unsigned int b = a + 1; b < _rooms.size(); b++)
				if (_rooms[a].touches(_rooms[b]))
				{
					touching = true;

					dx = fmin(
						abs(_rooms[a].getR() - _rooms[b].getL()) + 2,
						abs(_rooms[a].getL() - _rooms[b].getR()) + 2
					);

					dy = fmin(
						abs(_rooms[a].getB() - _rooms[b].getT()) + 2,
						abs(_rooms[a].getT() - _rooms[b].getB()) + 2
					);

					if (dx < dy) dy = 0;
					else dx = 0;

					if (_rooms[a].getL() < _rooms[b].getL())
						dx *= -1;

					if (_rooms[a].getT() < _rooms[b].getT())
						dy *= -1;

					dxa = dx / 2 + 1;
					dya = dy / 2 + 1;

					dxb = -dx / 2;
					dyb = -dy / 2;

					_rooms[a].shift(dxa, dya);
					_rooms[b].shift(dxb, dyb);
				}
		}
	}
}

void Floor::ConnectRooms()
{

}

void Floor::MadeGraph() 
{
	int distance;
	int temp_distance;
	int rightJoining, leftJoining;

	for (unsigned int i = 0; i < _rooms.size(); i++) 
	{

	}
}

void Floor::AddEnemies()
{

}

void Floor::AddLoot()
{

}

void Floor::toFile(std::string filePath)
{
	std::ofstream map_f(filePath);

	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_flat[y][x] = ' ';

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
	int x, y;
	char chNumber;

	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_flat[y][x] = '.';

	for (int i = 0; i < _rooms.size(); i++)
	{
		for (int x = 0; x <= _rooms[i].getW(); x++)
		{
			_flat[_rooms[i].getY()][_rooms[i].getX() + x] = '#';
			_flat[_rooms[i].getY() + _rooms[i].getH()][_rooms[i].getX() + x] = '#';
		}
		for (int y = 0; y <= _rooms[i].getH(); y++)
		{
			_flat[_rooms[i].getY() + y][_rooms[i].getX()] = '#';
			_flat[_rooms[i].getY() + y][_rooms[i].getX() + _rooms[i].getW()] = '#';
		}
	}

	for (int i = 0; i < 8; i++) 
		_flat[_rooms[i].getCenter().y][_rooms[i].getCenter().x] = 'X';
}




















