#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "math\vec2.h"
#include "structures\floor.h"
#include "math\graph.h"
#include "managers\game.h"

const int height = 20, width = 20;
char map[height][width];
vec2 playersPos;
vec2 monsterPos;
std::vector<vec2> verticities;

void makeVerticities()
{
	for (int i = 1; i < 19; i++)
		for (int j = 1; j < 19; j++)
			verticities.push_back(vec2(i, j));
	for (unsigned int i = 0; i < verticities.size(); i++)
		map[verticities[i].y][verticities[i].x] = '.';
}

void fillMap()
{
	for (unsigned int i = 0; i < verticities.size(); i++) 
	{
		map[verticities[i].y][verticities[i].x] = '.';
	}
	for (int i = 0; i < 20; i++)
	{
		map[0][i] = '#';
		map[height - 1][i] = '#';
		map[i][0] = '#';
		map[i][width - 1] = '#';
	}
}

void respawnPlayerAndMonster()
{
	playersPos.x = rand() % (18 - 1) + 1;
	playersPos.y = rand() % (18 - 1) + 1;
	playersPos.y = 18 - playersPos.y;

	monsterPos.x = rand() % (18 - 1) + 1;
	monsterPos.y = rand() % (18 - 1) + 1;
	monsterPos.y = 18 - monsterPos.y;

	map[playersPos.x][playersPos.y] = '@';
	map[monsterPos.x][monsterPos.y] = 'm';
}

void printFlat()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			std::cout << map[y][x];
		std::cout << std::endl;
	}
}

void makeFlat()
{
	makeVerticities();
	fillMap();
	respawnPlayerAndMonster();
}

void showAStar() 
{
	srand(time(NULL));
	makeFlat();
	Graph graph;
	graph.addVerticies(verticities);
	std::vector<vec2> path = graph.findPath(playersPos, monsterPos);
	for (unsigned int i = 0; i < path.size(); i++)
		map[path[i].y][path[i].x] = 'o';
	printFlat();
}

int main()
{
	showAStar();
	system("pause");
	return 0;
}