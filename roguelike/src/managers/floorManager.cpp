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

	_forbiddenTextures.push_back('#');
	_forbiddenTextures.push_back('m');
	_forbiddenTextures.push_back('@');

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
	
	if (checkTileIsAMonsterPosition(position)) 
		return;

	_flat[_playersPosition.y][_playersPosition.x] = _flatMap.getFlatTile(_playersPosition);
	_flat[position.y][position.x] = '@';
	_playersPosition = position;
}

void FloorManager::moveMonster(int index, vec2 position)
{
	vec2 monstersOldPos = _monsters[index].getPosition();
	_flat[monstersOldPos.y][monstersOldPos.x] = _flatMap.getFlatTile(monstersOldPos);
	_monsters[index].setPosition(position);
	_flat[position.y][position.x] = _monsters[index].getTexture();
}

int FloorManager::makeMonstersTurn() 
{
	vec2 positionToMove;
	bool moveFlag;
	int damage = 0;
	for(int i = 0; i < _monsters.size(); i++)
	{
		moveFlag = false;
		if (_playersPosition.squareDistance(_monsters[i].getPosition()) <= 400) 
		{
			positionToMove = _floorGraph.findPathStep(_monsters[i].getPosition(), _playersPosition);
			moveFlag = true;
		}

		if (checkPlayerNear(_monsters[i]))
		{
			damage += _monsters[i].makeHit();
			continue;
		}

		if (moveFlag && checkTile(positionToMove))
			moveMonster(i, positionToMove);

	}
	return damage;
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

bool FloorManager::checkTileIsAMonsterPosition(vec2 position)
{
	for (unsigned int i = 0; i < _monsters.size(); i++)
		if (_monsters[i].getPosition() == position)
			return true;

	return false;
}

void FloorManager::hitMonster(int damage, vec2 position) 
{
	for (unsigned int i = 0; i < _monsters.size(); i++)
		if (_monsters[i].getPosition() == position) 
		{
			_monsters[i].decreaseHealth(damage);

			if (_monsters[i].getHealth() <= 0)
				_monsters.erase(_monsters.begin() + i);
		}
}

bool FloorManager::checkPlayerNear(Monster monster)
{
	std::vector<vec2> localityDirs;
	localityDirs.push_back(vec2(-1, 0));
	localityDirs.push_back(vec2(1, 0));
	localityDirs.push_back(vec2(0, 1));
	localityDirs.push_back(vec2(0, -1));

	for (int i = 0; i < 4; i++) 
	{
		vec2 position = monster.getPosition() + localityDirs[i];
		if (_flat[position.y][position.x] == '@') return true;
	}

	return false;
}

bool FloorManager::checkTile(vec2 tile) 
{
	for (unsigned int i = 0; i < _forbiddenTextures.size(); i++)
		if (_flat[tile.y][tile.x] == _forbiddenTextures[i]) return false;
	return true;
}