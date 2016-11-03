#include "floor.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

Floor::Floor() 
{
	std::cout << "Calling usual constructor for Floor" << std::endl;
}

Floor::Floor(int number, int roomsCount, std::string style)
{
	_number = number;
	GenerateRooms(roomsCount);
	SeparateRooms();
	AddLoot();
}

void Floor::GenerateRooms(int numberOfRooms) 
{
	srand(time(NULL));
	int w, h, x, y;
	for (int i = 0; i < numberOfRooms; i++)
	{
		x = rand() % (90 - 68 + 1) + 68;
		y = rand() % (30 - 20 + 1) + 5;
		w = rand() % (20 - 5 + 1) + 5;
		h = rand() % (20 - 5 + 1) + 5;

		_rooms.push_back(Room(x, y, w, h));
	}
}

void Floor::SeparateRooms()
{

}

void Floor::AddLoot()
{

}

void Floor::AddEnemies() 
{

}

void Floor::toFile() 
{
	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_flat[y][x] = '.';
		
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


	std::ofstream map_f("map.txt");
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
			map_f << _flat[y][x];
		map_f << std::endl;
	}
}