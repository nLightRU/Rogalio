#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "math\vec2.h"
#include "managers\game.h"
#include <Windows.h>

void settTextColor(unsigned char attr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}

const int height = 60, width = 60;
char map[height][width];
vec2 playersPos;
vec2 monsterPos;
std::vector<vec2> verticities;

void makeVerticities()
{
	for (int i = 1; i < width - 1; i++)
		for (int j = 1; j < height - 1; j++)
			if(map[i][j] == '.') verticities.push_back(vec2(i, j));
}

void fillMap()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			map[x][y] = '.';
		}
	}

	for (int i = 1; i < height - 1; i++) 
	{
		for (int j = 1; j < width - 1; j++)
			if(rand() % 100  <= 25)
				map[i][j] = '#';
	}

	for (int i = 0; i < width; i++)
	{
		map[0][i] = '#';
		map[height - 1][i] = '#';
		map[i][0] = '#';
		map[i][width - 1] = '#';
	}
}

void respawnPlayerAndMonster()
{
	playersPos.x = rand() % (height - 2 - 1) + 1;
	playersPos.y = rand() % (height -2  - 1) + 1;
	/*vec2 re; 
	re.x = playersPos.x;
	playersPos.x = playersPos.y;
	playersPos.y = re.x;*/

	monsterPos.x = rand() % (height - 2 - 1) + 1;
	monsterPos.y = rand() % (height - 2 - 1) + 1;
	/*re.x = monsterPos.x;
	monsterPos.x = monsterPos.y;
	monsterPos.y = re.x;*/
}

void printFlat()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			if (map[y][x] == 'x') 
			{
				settTextColor(FOREGROUND_RED + FOREGROUND_INTENSITY);
				std::cout << map[y][x];
				settTextColor(FOREGROUND_BLUE + FOREGROUND_GREEN + FOREGROUND_RED);
			}
			else std::cout << map[y][x];
		std::cout << std::endl;
	}
}

void makeFlat()
{
	fillMap();
	makeVerticities();
	respawnPlayerAndMonster();
}


void showAStar()
{
	srand(time(NULL));
	Graph graph;
	makeFlat();

	graph.addVerticies(verticities);
	std::vector<vec2> path = graph.findPath(monsterPos, playersPos);
	std::cout << path.size() << std::endl;

	settTextColor(FOREGROUND_RED + FOREGROUND_INTENSITY);
	for (unsigned int i = 0; i < path.size(); i++)
		map[path[i].y][path[i].x] = 'x';
	settTextColor(FOREGROUND_BLUE + FOREGROUND_GREEN + FOREGROUND_RED);
	map[playersPos.y][playersPos.x] = '@';
	map[monsterPos.y][monsterPos.x] = 'm';

	printFlat();
}

/*
FOREGROUND_BLUE
FOREGROUND_GREEN
FOREGROUND_RED
FOREGROUND_INTENSITY

BACKGROUND_BLUE
BACKGROUND_GREEN
BACKGROUND_RED
BACKGROUND_INTENSITY
*/

int main()
{
	
	Game game;
	game.gameLoop();



	system("pause");
	return 0;
}