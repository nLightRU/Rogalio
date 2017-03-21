#pragma once
#include <string>
#include <cstdlib>
#include <vector>

class MonsterInfo 
{
private: 
	int _minHealth, _maxHealth;
	int _minMana, _maxMana;
	int _minDamage, _maxDamage;
	char _texture;
	unsigned char _color;
	std::string _name;
	std::string _description;
public: 
	MonsterInfo();
	MonsterInfo createRat();
	MonsterInfo createSkeleton();
	MonsterInfo createGremlin();
	MonsterInfo createGoblin();
	MonsterInfo createSpider();
	MonsterInfo createZombie();
	MonsterInfo createGolem();
	MonsterInfo createSlug();
	MonsterInfo createScorpion();
	MonsterInfo createPython();

	int generateHealth() { return rand() % (_maxHealth - _minHealth + 1) + _minHealth; }
	int generateMana() { return rand() % (_maxMana - _minMana + 1) + _minMana; }
	int generateHit() { return rand() % (_maxDamage - _minDamage + 1) + _minDamage; }

	char getTexture() { return _texture; }
	unsigned char getColor() { return _color; }

	std::string getName() { return _name; }
	std::string getDescription() { return _description; }
	std::vector<MonsterInfo> createAllMonsters();

	void initialize(MonsterInfo info);
};