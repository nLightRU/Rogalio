#pragma once
#include "../math/vec2.h"
class Player
{
private:
	int _maxHealth, _health, _mana; 
	int _minDamage, _maxDamage;
	char _texture = '@'; 
	vec2 _position;
	vec2 _moveDirection;
public:
	Player();

	vec2 getPosition() { return _position; }

	void shift(int dx, int dy);
};