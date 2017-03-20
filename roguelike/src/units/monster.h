#pragma once
#include "../math/vec2.h"
#include "../data/monsterInfo.h"
#include <string>
#include <vector>

class Monster
{
private:
	MonsterInfo _info;
	int _maxHealth, _maxMana, _health, _mana, _exp;
	vec2 _position;
public:
	Monster(MonsterInfo info, vec2 position);

	char getTexture() { return _info.getTexture(); }
	std::string getName() { return _info.getName(); }

	int getHealth() { return _health; }
	int getMana() { return _mana; }
	vec2 getPosition() { return _position; }

	void setHealth(int health);
	void setMana(int mana);
	void setPosition(vec2 coords);

	int makeHit();
	void move(int dx, int dy); 
	void decreaseHealth(int damage) { _health -= damage; }
	void decreaseMana(int consumption) { _mana -= consumption; }

};