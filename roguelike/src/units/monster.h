#pragma once
#include "../math/vec2.h"
#include <string>
#include <vector>
class Monster
{
private:
	int _health, _maxHealth, _mana;
	int _minDamage, _maxDamage;
	int _rarity;
	char _texture;
	std::string _name;
	vec2 _position;
	std::vector<vec2> _way;

	void MakeWay();

public:
	Monster();
	int getHealth() { return _health; }
	char getTexture() { return _texture; }
	int getMana() { return _mana; }
	std::string getName() { return _name; }
	vec2 getPosition() { return _position; }

	void setMaxHealth(int maxHealth);
	void setHealth(int health);
	void setMana(int mana);
	void setRarity(int rarity);
	void setName(std::string name);
	void setPosition(vec2 coords);
	void setDamage(int minDamage, int maxDamage);

	int makeHit();
	void move(int dx, int dy); 

};