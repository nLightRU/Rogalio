#pragma once
#include "../structures/floor.h"
#include "../math/vec2.h"
#include "../units/monster.h"
#include <vector>
class FloorManager 
{
private:
	Floor _floor;

	const int _height = 300, _width = 300;
	char _flat[300][300];
	vec2 _playersPosition;
	std::vector<Monster> _monsters;

	void RespawnPlayer();
	void RespawnMonsters();

	void PlaceMonsters();

	void moveMonster(int index, vec2 position);
public:
	FloorManager();
	void movePlayer(vec2 position);
	void makeMonstersTurn();

	vec2 getPlayersPosition() { return _playersPosition; }
	char getFlatTile(vec2 position) { return _flat[position.y][position.x]; }
	char getFlatTile(int i, int j) { return _flat[i][j]; }
};