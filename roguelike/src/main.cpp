#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include "room.h"
#include "floor.h"

#define X 175
#define Y 57

char map[Y][X];
std::vector<Room> rooms;

std::vector<Room> GenerateRooms(int numberOfRooms)
{
	srand(time(NULL));
	std::vector<Room> rooms;
	int w, h, x, y;
	for (int i = 0; i < numberOfRooms; i++)
	{
		x = rand() % (90 - 68 + 1) + 68;
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
	for (int i = 0; i < Y; i++)
		for (int j = 0; j < X; j++)
			map[i][j] = '.';

	drawRooms(rooms, map);
}
void mapToFile(std::string fileName)
{
	std::ofstream file(fileName);
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
			file << map[y][x];
		file << std::endl;
	}
}
void separateRooms()
{
	int dx, dy, dxa, dxb, dya, dyb;
	bool touching = true;
	int step = 0;
	do
	{
		std::cout << "Separating Rooms. Iteration: " << ++step << std::endl;
		touching = false;

		for (int a = 0; a < rooms.size(); a++)
		{
			for (int b = a + 1; b < rooms.size(); b++)
			{
				if (rooms[a].touches(rooms[b]))
				{
					touching = true;
					
					dx = fmin(rooms[a].getR() - rooms[b].getL() + 1, rooms[a].getL() - rooms[b].getR() - 1);
					dy = fmin(rooms[a].getB() - rooms[b].getT() - 1, rooms[a].getT() - rooms[b].getB() + 1);

					if (abs(dx) < abs(dy)) dy = 0;
					else dx = 0;

					dxa = -dx / 2;
					dxb = dx + dxa;

					dya = -dy / 2;
					dyb = dy + dya;

					rooms[a].shift(dxa, dya);
					rooms[b].shift(dxb, dyb);
				}
			}
		}
	} while (touching);
}
void toFiles()
{
	makeMap(rooms);
	mapToFile("map.txt");

	separateRooms();

	makeMap(rooms);
	mapToFile("map_new.txt");
}

int main()
{
	int numberOfRooms = 2;
	rooms = GenerateRooms(numberOfRooms);
		
	toFiles();
	//system("PAUSE");
	return 0;
}