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

	std::ofstream log("FloorManager units.txt");
	_floorGraph.addVerticies(_flatMap.collectPoints());


	RespawnPlayer();
	RespawnMonsters();
	PlaceMonsters();


	// logging stuff
	log << "PLAYERS POSITION " << _playersPosition.x << " " << _playersPosition.y << " ";
	if (!_floorGraph.existPoint(_playersPosition))
		log << "out";
	log << std::endl;
	
	for (unsigned int i = 0; i < _monsters.size(); i++) 
	{
		log << "MONSTER " << i + 1 << " " << _monsters[i].getPosition().x << " "
			<< _monsters[i].getPosition().y << " ";
		if (!_floorGraph.existPoint(_monsters[i].getPosition()))
			log << "out";
		log << std::endl;
	}

	log << "VERTICIES" << std::endl;

	for (unsigned int i = 0; i < _floorGraph.getVerticies().size(); i++) 
	{
		log << _floorGraph.getVerticies()[i].x << " ";
		log << _floorGraph.getVerticies()[i].y << std::endl;
	}

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
	std::ofstream monstersList("FloorManager monsters.txt");

	srand(time(NULL));

	Monster tempMonster;

	for (unsigned int i = 0; i < _monstersNumber; i++) 
	{
		tempMonster.setPosition(_floorGraph.getRandomVertex());

		_monsters.push_back(tempMonster);

		placePoint(tempMonster.getPosition(), tempMonster.getTexture());

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

void FloorManager::placePoint(vec2 position, char symbol) 
{
	_flat[position.y][position.x] = symbol;
}

void FloorManager::placePoint(int x, int y, char symbol)
{
	_flat[y][x] = symbol;
}
