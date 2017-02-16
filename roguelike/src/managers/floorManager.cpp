#include "floorManager.h"
#include <time.h>
#include <iostream>
#include <fstream>
FloorManager::FloorManager() 
{
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			_flat[i][j] = _floor.getFlatTile(i, j);

	RespawnPlayer();
	RespawnMonsters();
	PlaceMonsters();

	std::ofstream map_f("floor.txt");

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
			map_f << _flat[y][x];
		map_f << std::endl;
	}
}	

void FloorManager::RespawnPlayer() 
{
	_playersPosition = _floor.getHalls()[0].getCenter();
}

void FloorManager::RespawnMonsters()
{
	srand(time(NULL));
	int hall; // number of hall for monster
	Monster tempMonster;
	vec2 positionOfMonster;
	for (unsigned int i = 0; i < 15; i++) 
	{
		
		positionOfMonster = _floor.createRandomPointInHall();

		tempMonster.setPosition(positionOfMonster);

		_monsters.push_back(tempMonster);
	}
}

void FloorManager::PlaceMonsters() 
{
	for (unsigned int i = 0; i < _monsters.size(); i++)
		_flat[_monsters[i].getPosition().y][_monsters[i].getPosition().x] = _monsters[i].getTexture();
}

void FloorManager::movePlayer(vec2 position) 
{
	_flat[_playersPosition.y][_playersPosition.x] = _floor.getFlatTile(_playersPosition);
	_flat[position.y][position.x] = '@';
	_playersPosition = position;
}