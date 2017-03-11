#pragma once
#include "../math/vec2.h"
#include <string>
#include <vector>
class Monster
{
private:
	int _health = 10, _maxHealth = 10, _mana = 0;
	int _minDamage = 0, _maxDamage = 1;
	int _rarity = 1;
	char _texture = 'm';
	std::string _name = "Monster";
	vec2 _position;

	std::vector<vec2> _way;
public:
	Monster();
	Monster(vec2 position);
	Monster(int health, int mana, vec2 position);
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
	void setTexture(char texture);

	int makeHit();
	void move(int dx, int dy); 

};