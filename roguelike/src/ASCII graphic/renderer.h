#pragma once
#include "ASCIIcamera.h"
#include "../units/player.h"

class Renderer 
{
private:
	ASCIICamera _camera;
public: 
	Renderer();
	void showGameplayScreen(Player player);
	void showInventoryScreen();
};
