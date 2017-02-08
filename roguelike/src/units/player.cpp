#include "player.h"

Player::Player() 
{
	_maxHealth = 100;
	_health = 100; 
	_mana = 100;
	_position = vec2(10, 10);
}

void Player::shift(int dx, int dy) 
{
	_position.x += dx;
	_position.y += dy;
}