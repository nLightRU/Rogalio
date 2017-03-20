#pragma once
#include "ASCIIcamera.h"
#include "../units/player.h"
#include "../structures/dungeon.h"
class ASCIIRenderer 
{
private:
	ASCIICamera _camera;
public: 
	ASCIIRenderer();
	void setCamera(ASCIICamera cam);
	void showGameplayScreen(Player player, Dungeon dungeon);
	void showInventoryScreen();
};
