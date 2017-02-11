#include "player.h"

Player::Player() 
{
	_maxHealth = 100;
	_health = 100; 
	_mana = 100;
}

void Player::shift(int dx, int dy) 
{
	_position.x += dx;
	_position.y += dy;
}

void Player::shift(vec2 direction) 
{
	_position.x += direction.x;
	_position.y += direction.y;
}

void Player::setPosition(vec2 position) 
{
	_position = position;
}

void Player::setPosition(int x, int y) 
{
	_position.x = x;
	_position.y = y;
}