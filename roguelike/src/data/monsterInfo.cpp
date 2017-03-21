#include "monsterInfo.h"
#include <Windows.h>

MonsterInfo::MonsterInfo() 
{
	_minHealth = 10;
	_maxHealth = 20;
	_minDamage = 10;
	_maxDamage = 20;
	_name = "Monster";
	_texture = 'm';
}

MonsterInfo MonsterInfo::createGoblin() 
{
	MonsterInfo info;
	info._minHealth = 10; 
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Goblin";
	info._texture = 'G';
	info._color = FOREGROUND_GREEN + FOREGROUND_INTENSITY;
	return info;
}

MonsterInfo MonsterInfo::createGremlin()
{
	MonsterInfo info;
	info._minHealth = 10;
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Gremlin";
	info._texture = 'g';
	info._color = FOREGROUND_GREEN;
	return info;
}

MonsterInfo MonsterInfo::createRat()
{
	MonsterInfo info;
	info._minHealth = 10;
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Rat";
	info._texture = 'r';
	info._color = FOREGROUND_INTENSITY;
	return info;
}

MonsterInfo MonsterInfo::createSkeleton()
{
	MonsterInfo info;
	info._minHealth = 10;
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Skeleton";
	info._texture = 'S';
	info._color = FOREGROUND_BLUE + FOREGROUND_GREEN + FOREGROUND_RED + FOREGROUND_INTENSITY;
	return info;
}

MonsterInfo MonsterInfo::createSpider()
{
	MonsterInfo info;
	info._minHealth = 10;
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Spider";
	info._texture = '3';
	info._color = FOREGROUND_GREEN + FOREGROUND_RED;
	return info;
}

MonsterInfo MonsterInfo::createZombie()
{
	MonsterInfo info;
	info._minHealth = 10;
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Zombie";
	info._texture = '7';
	info._texture = FOREGROUND_GREEN;
	return info;
}

MonsterInfo MonsterInfo::createGolem()
{
	MonsterInfo info;
	info._minHealth = 10;
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Golem";
	info._texture = '8';
	unsigned char attr = FOREGROUND_RED + FOREGROUND_GREEN;
	for (int i = 0; i < 5; i++)
		attr += FOREGROUND_BLUE;
	info._color = attr;
	return info;
}

MonsterInfo MonsterInfo::createSlug()
{
	MonsterInfo info;
	info._minHealth = 10;
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Slug";
	info._texture = '0';
	info._color = FOREGROUND_GREEN + FOREGROUND_INTENSITY;
	return info;
}

MonsterInfo MonsterInfo::createScorpion()
{
	MonsterInfo info;
	_minHealth = 10;
	_maxHealth = 20;
	_minDamage = 10;
	_maxDamage = 20;
	_name = "Scorpion";
	_texture = 's';
	info._color = FOREGROUND_RED + FOREGROUND_BLUE + FOREGROUND_BLUE + FOREGROUND_INTENSITY;
	return info;
}

MonsterInfo MonsterInfo::createPython()
{
	MonsterInfo info;
	info._minHealth = 10;
	info._maxHealth = 20;
	info._minDamage = 10;
	info._maxDamage = 20;
	info._name = "Python";
	info._texture = 'p';
	info._color = FOREGROUND_RED + FOREGROUND_BLUE + FOREGROUND_BLUE + FOREGROUND_INTENSITY;
	return info;
}

std::vector<MonsterInfo> MonsterInfo::createAllMonsters() 
{
	MonsterInfo info; 
	std::vector<MonsterInfo> list;
	list.push_back(info.createGoblin());
	list.push_back(info.createGolem());
	list.push_back(info.createGremlin());
	list.push_back(info.createPython());
	list.push_back(info.createRat());
	list.push_back(info.createScorpion());
	list.push_back(info.createSlug());
	list.push_back(info.createSkeleton());
	list.push_back(info.createSpider());
	list.push_back(info.createZombie());
	return list;
}

void MonsterInfo::initialize(MonsterInfo info) 
{
	_minDamage = info._minDamage;
	_maxDamage = info._maxDamage;

	_texture = info._texture;
	_name = info._name;

	_minHealth = info._minHealth;
	_maxHealth = info._maxHealth;
}









