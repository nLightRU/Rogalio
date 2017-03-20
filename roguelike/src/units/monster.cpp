#include "monster.h"
#include <time.h>


Monster::Monster(MonsterInfo info, vec2 position)
{
	_maxHealth = info.generateHealth();
	_maxMana = info.generateMana();
	_info.initialize(info);
	_position = position;
}

void Monster::setHealth(int health)
{
	_health = health;
}

void Monster::setMana(int mana)
{
	_mana = mana;
}

void Monster::setPosition(vec2 position)
{
	_position = position;
}

int Monster::makeHit()
{
	srand(time(NULL));
	return _info.generateHit();
}

void Monster::move(int dx, int dy)
{
	_position.x += dx;
	_position.y += dy;
}
