#pragma once
#include "../structures/floor.h"
#include "../math/vec2.h"
#include "../units/monster.h"
#include <vector>
class FloorManager 
{
private:
	Floor _flatMap;
	Graph _floorGraph; 

	const int _height = 300, _width = 300;
	char _flat[300][300];
	vec2 _playersPosition;
	std::vector<Monster> _monsters;	

	int _monstersNumber = 1;

	void RespawnPlayer();
	void RespawnMonsters();
	void toFile();

	void PlaceMonsters();

	void moveMonster(int index, vec2 position);
	void placePoint(vec2 position, char symbol);
	void placePoint(int x, int y, char symbol);
public:
	FloorManager();
	void movePlayer(vec2 position);
	void makeMonstersTurn();

	vec2 getPlayersPosition() { return _playersPosition; }
	char getFlatTile(vec2 position) { return _flat[position.y][position.x]; }
	char getFlatTile(int i, int j) { return _flat[i][j]; }
	std::vector<Monster> getMonsters() { return _monsters; }
};