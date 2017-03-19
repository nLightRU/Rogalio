#pragma once
#include "item.h"
#include <vector>

class Chest 
{
	Rarity _rarity;
	std::vector<Item> _items;
};