#pragma once
#include "../structures/floor.h"
#include "../math/vec2.h"
#include "../units/monster.h"
#include <vector>
class FloorManager 
{
private:
	Floor _floor;
	Graph _floorGraph; 

	const int _height = 300, _width = 300;
	char _flat[300][300];

	vec2 _playersPosition;
	vec2 _trapPosition;
	std::vector<Monster> _monsters;	
	std::vector<char> _forbiddenTextures;
	int _monstersNumber;

	void moveMonster(int index, vec2 position);

	void PlaceMonsters();
	void placePoint(vec2 position, char symbol);
	void placePoint(int x, int y, char symbol);

	bool checkTileIsAMonsterPosition(vec2 position);
	bool checkPlayerNear(Monster monster);
public:
	FloorManager();
	FloorManager(Floor floor);

	void initialize(Floor floor);

	void movePlayer(vec2 position);
	int makeMonstersTurn();
	void hitMonster(int damage, vec2 position);

	vec2 getTrapPosition() { return _trapPosition; }
	vec2 getPlayersPosition() { return _playersPosition; }

	char getFlatTile(vec2 position) { return _flat[position.y][position.x]; }
	char getFlatTile(int i, int j) { return _flat[i][j]; }

	std::vector<Monster> getMonsters() { return _monsters; }

	bool checkTile(vec2 tile);
};