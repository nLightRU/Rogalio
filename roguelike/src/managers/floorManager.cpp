#include "floorManager.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>

FloorManager::FloorManager() 
{
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			_flat[i][j] = _flatMap.getFlatTile(i, j);

	std::vector<vec2> points = _flatMap.collectPoints();
	_floorGraph.addVerticies(points);

	RespawnPlayer();
	RespawnMonsters();
	PlaceMonsters();

	toFile();
}	

void FloorManager::RespawnPlayer() 
{
	placePoint(_playersPosition, ' ');
	_playersPosition = _flatMap.getHalls()[0].getCenter();
	placePoint(_playersPosition, '@');
}

void FloorManager::RespawnMonsters()
{
	srand(time(NULL));

	Monster tempMonster;

	for (unsigned int i = 0; i < _monstersNumber; i++) 
	{
		tempMonster.setPosition(_floorGraph.getRandomVertex());

		_monsters.push_back(tempMonster);

		placePoint(tempMonster.getPosition(), tempMonster.getTexture());
	}
}

void FloorManager::PlaceMonsters() 
{
	for (unsigned int i = 0; i < _monsters.size(); i++)
		_flat[_monsters[i].getPosition().y][_monsters[i].getPosition().x] = _monsters[i].getTexture();
}

void FloorManager::movePlayer(vec2 position) 
{
	_flat[_playersPosition.y][_playersPosition.x] = _flatMap.getFlatTile(_playersPosition);
	_flat[position.y][position.x] = '@';
	_playersPosition = position;
}

void FloorManager::moveMonster(int index, vec2 position)
{
	vec2 monstersOldPosition = _monsters[index].getPosition();
	_flat[monstersOldPosition.y][monstersOldPosition.x] = _flatMap.getFlatTile(monstersOldPosition);
	_monsters[index].setPosition(position);
	_flat[position.y][position.x] = _monsters[index].getTexture();
}

void FloorManager::makeMonstersTurn() 
{
	vec2 position;
	for(int i = 0; i < _monsters.size(); i++)
	{
		position = _floorGraph.findPathStep(_monsters[i].getPosition(), _playersPosition);
		moveMonster(i, position);
	}
}

void FloorManager::toFile() 
{
	std::ofstream flatMap("flat map.txt");
	for (int y = 0; y < _height; y++) 
	{
		for (int x = 0; x < _width; x++)
			flatMap << _flat[y][x];
		flatMap << std::endl;
	}
}

void FloorManager::placePoint(vec2 position, char symbol) 
{
	_flat[position.y][position.x] = symbol;
}

void FloorManager::placePoint(int x, int y, char symbol)
{
	_flat[y][x] = symbol;
}