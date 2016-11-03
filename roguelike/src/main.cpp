#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include "room.h"
#include "floor.h"

#define X 155
#define Y 48

char map[Y][X];
std::vector<Room> rooms;

std::vector<Room> GenerateRooms(int numberOfRooms) 
{
	srand(time(NULL));
	std::vector<Room> rooms;
	int w, h, x, y;
	for (int i = 0; i < numberOfRooms; i++)
	{
		x = rand() % (75 - 50 + 1) + 20;
		y = rand() % (30 - 20 + 1) + 5;
		w = rand() % (20 - 5 + 1) + 5;
		h = rand() % (20 - 5 + 1) + 5;
		rooms.push_back(Room(x, y, w, h));
	}
	return rooms;
}

void drawRooms(std::vector<Room> rooms, char map[Y][X])
{
	for (int i = 0; i < rooms.size(); i++) 
	{
		// top and bot
		for (int x = 0; x <= rooms[i].getW(); x++)
		{
			map[rooms[i].getY()][rooms[i].getX() + x] = '#';
			map[rooms[i].getY() + rooms[i].getH()][rooms[i].getX() + x] = '#';
		}

		// left and right
		for (int y = 0; y <= rooms[i].getH(); y++)
		{
			map[rooms[i].getY() + y][rooms[i].getX()] = '#';
			map[rooms[i].getY() + y][rooms[i].getX() + rooms[i].getW()] = '#';
		}
	}
}

void makeMap(std::vector<Room> rooms) 
{
	int numberOfRooms = 2;

	for (int i = 0; i < Y; i++)
		for (int j = 0; j < X; j++)
			map[i][j] = '.';

	drawRooms(rooms, map);

	map[rooms[0].getY()][rooms[0].getX()] = 'a';
	map[rooms[1].getY()][rooms[1].getX()] = 'b';
}

void toFile() 
{
	std::ofstream map_f("map.txt");
	makeMap(rooms);
	std::cout << std::endl;
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
			map_f << map[y][x];
		map_f << std::endl;
	}
}

int main()
{	
	int numberOfRooms = 2;
	rooms = GenerateRooms(numberOfRooms);
	toFile();


	// start separation function 
	Room a;
	Room b;

	int dx, dy, dxa, dxb, dya, dyb;
	bool touching = true;
	while (touching) 
	{
		touching = false;
		if a
			
	}

	// end separation func

	system("pause");
	return 0;
}