#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "math\vec2.h"
#include "structures\floor.h"
#include "managers\game.h"

const int height = 20, width = 20; 
char map[height][width];
vec2 playersPos;
vec2 monsterPos;
std::vector<vec2> verticities;

struct Tile 
{
	vec2 coords;
	vec2 parent;
	int f, g, h;
	void countDistance(vec2 goal) { this->h = this->coords.squareDistance(goal); }
	void countFunction() { this->f = this->g + this->h; }
};

void makeVerticities() 
{
	for (int i = 1; i < 19; i++)
		for (int j = 1; j < 19; j++)
			verticities.push_back(vec2(i, j));
	for (unsigned int i = 0; i < verticities.size(); i++)
		map[verticities[i].y][verticities[i].x] = '.';
}

int findInClosedList(Tile _tile, std::vector<Tile> closedlist)
{
	for (unsigned int i = 0; i < closedlist.size(); i++) 
		if (_tile.coords == closedlist[i].coords) return i;
	return -1;
}

int findInClosedList(vec2 point, std::vector<Tile> closedlist)
{
	for (unsigned int i = 0; i < closedlist.size(); i++)
		if (point == closedlist[i].coords) return i;
	return -1;
}

bool inGraph(vec2 point)
{
	for (unsigned int i = 0; i < verticities.size(); i++)
		if (verticities[i] == point) return true; 
	return false;
}

std::vector<vec2> findPath(vec2 start, vec2 goal) 
{
	std::cout << "start " << start.x << " " << start.y <<std::endl;
	std::cout << "goal " << goal.x << " " << goal.y << std::endl;

	std::vector<Tile> openedList;
	std::vector<Tile> closedList;
	std::vector<vec2> localityDirs;
	localityDirs.push_back(vec2(-1, 0));
	localityDirs.push_back(vec2(1, 0));
	localityDirs.push_back(vec2(0, 1));
	localityDirs.push_back(vec2(0, -1));

	Tile startTile; 
	startTile.g = 0; 
	startTile.h = start.squareDistance(goal);
	startTile.coords = start;

	Tile startLocalityTile;
	startLocalityTile.g = 1;
	startLocalityTile.parent = start;
	for (int i = 0; i < 4; i++) 
	{
		startLocalityTile.coords = start + localityDirs[i];
		if (!inGraph(startLocalityTile.coords)) {
			continue;
		}
		startLocalityTile.countDistance(goal);
		startLocalityTile.countFunction();
		openedList.push_back(startLocalityTile);
	}

	closedList.push_back(startTile);

	while (!openedList.empty()) 
	{
		Tile currentTile = openedList[0]; 
		int currentTileIndex = 0;
		for(unsigned int i = 1; i < openedList.size(); i++)
			if (openedList[i].f < currentTile.f) 
			{
				currentTile = openedList[i];
				currentTileIndex = i;
			}

		openedList.erase(openedList.begin() + currentTileIndex);
		closedList.push_back(currentTile);
	
		Tile localityTile;
		for(int i = 0; i < 4; i++)
		{
			localityTile.coords = currentTile.coords + localityDirs[i];
			localityTile.parent = currentTile.coords;
			localityTile.countDistance(goal);
			localityTile.g = currentTile.g + 1;
			localityTile.countFunction();

			if (!inGraph(localityTile.coords))
				continue;
			
			if (localityTile.coords == goal)
			{
				closedList.push_back(localityTile);
				openedList.clear();
				break;
			}

			int indexOfTile = findInClosedList(localityTile, closedList);
			if (indexOfTile == -1) 
				openedList.push_back(localityTile);
			else 
				if (localityTile.g < closedList[indexOfTile].g) 
					closedList[indexOfTile] = localityTile;
		}
	}

	std::vector<vec2> path; 
	Tile pathTile = closedList[closedList.size() - 1];
	vec2 point;
	std::cout << point.x << " " << point.y << std::endl;
	int indexOfPoint;
	while(point != start) 
	{
		point = pathTile.parent;
		indexOfPoint = findInClosedList(point, closedList);
		pathTile = closedList[indexOfPoint];
		path.push_back(point);
	}
	std::cout << "returning" << std::endl;
	return path;
}

void makePath() 
{
	std::vector<vec2> path = findPath(monsterPos, playersPos);
	for (unsigned int i = 0; i < path.size(); i++)
		map[path[i].y][path[i].x] = 'X';
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
	map[playersPos.x][playersPos.y] = '@';
	monsterPos.x = rand() % (18 - 1) + 1;
	monsterPos.y = rand() % (18 - 1) + 1;
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

int main() 
{

	srand(time(NULL));
	makeFlat();

	makePath();

	printFlat();

	system("pause");
	return 0;
}