#pragma once
#include <string>

enum Rarity {COMMON, UNCOMMON, RARE, MYTHICAL, LEGENDARY};

class Item 
{
private: 
	int _damage, _durability; 

	Rarity _rarity;

	std::string _name;
	std::string _description;
};