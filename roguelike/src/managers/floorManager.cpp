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

	_floorGraph.addVerticies(_flatMap.collectPoints());

	std::ofstream verticiesLog("verticies.txt");
	for (unsigned int i = 0; i < _floorGraph.getVerticies().size(); i++) 
	{
		verticiesLog << _floorGraph.getVerticies()[i].x << " ";
		verticiesLog << _floorGraph.getVerticies()[i].y << std::endl;
	}

	RespawnPlayer();
	RespawnMonsters();
	PlaceMonsters();
	
	toFile();
}	

void FloorManager::RespawnPlayer() 
{
	_playersPosition = _flatMap.getHalls()[0].getCenter();
}

void FloorManager::RespawnMonsters()
{
	std::ofstream monstersList("FloorManager monsters.txt");

	srand(time(NULL));

	Monster tempMonster;

	for (unsigned int i = 0; i < 9; i++) 
	{
		tempMonster.setPosition(_floorGraph.getRandomVertex());

		_monsters.push_back(tempMonster);

		monstersList << "Monster " << i + 1 << " " << tempMonster.getPosition().x << " " 
			<< tempMonster.getPosition().y << std::endl;
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
	std::ofstream monstersMoves("FloorManager monsters moves.txt");
	vec2 position;
	for(int i = 0; i < _monsters.size(); i++)
	{
		position = _floorGraph.findPathStep(_monsters[i].getPosition(), _playersPosition);

		monstersMoves << "Monster " << i + 1 << " moved from " << _monsters[i].getPosition().x 
			<< " " << _monsters[i].getPosition().y << " to " << position.x << " " << position.y
			<< std::endl;

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