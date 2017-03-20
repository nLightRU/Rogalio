#pragma once
#include "monsterInfo.h"

class MonstersDataBase
{
private:
	MonsterInfo _rat;
	MonsterInfo _skeleton;
	MonsterInfo _gremlin;
	MonsterInfo _goblin;
	MonsterInfo _spider;
	MonsterInfo _zombie;
	MonsterInfo _golem;
	MonsterInfo _slug;
	MonsterInfo _scorpion;
	MonsterInfo _python;
public:
	MonsterInfo getRat() { return _rat; }
	MonsterInfo getSkeleton() { return _skeleton; }
	MonsterInfo getGremlin() { return _gremlin; }
	MonsterInfo getSpider() { return _spider; }
	MonsterInfo getZombie() { return _zombie; }
	MonsterInfo getGolem() { return _golem; }
	MonsterInfo getSlug() { return _slug; }
	MonsterInfo getScorpion() { return _scorpion; }
	MonsterInfo getPython() { return _python; }
};