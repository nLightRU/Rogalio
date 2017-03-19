#pragma once
#include "../math/vec2.h"
#include <cstdlib>

class Player
{
private:
	int _maxHealth, _health, _maxMana,_mana;
	int _minDamage, _maxDamage;
	char _texture = '@';
	vec2 _position;
	vec2 _moveDirection;
public:
	Player();

	vec2 getPosition() { return _position; }
	int getMaxHealth() { return _maxHealth; }
	int getHealth() { return _health; }
	int getMaxMana() { return _maxMana; }
	int getMana() { return _mana; }

	int makeHit() { return rand() % (_maxDamage - _minDamage + 1) + _minDamage; }

	void decreaseHealth(int damage) { _health -= damage; }
	void decreaseMana(int consumption) { _mana -= consumption; }

	void setPosition(vec2 position);
	void setPosition(int x, int y);
	void shift(int dx, int dy);
	void shift(vec2 direction);
};