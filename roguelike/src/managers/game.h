#pragma once
#include "playerInputManager.h"
#include "../ASCII graphic/ASCIIcamera.h"
#include "../units/player.h"
#include "../structures/dungeon.h"
#include "floorManager.h"
enum GAME_STATES {MainMenu, PlayerTurn, MonstersTurn};

class Game
{
private: 

	std::vector<char> _forbiddenTextures;

	PlayerInputManager _playerInputManager;
	Player _player;
	ASCIICamera _ASCIIcamera;
	GAME_STATES _state;
	FloorManager _floorManager; 
	Graph _graph;

	void PrintCamera();
	void PrintUI();
	void Input();
	void MonstersTurn();
	
	bool checkTile(vec2 position);

	bool inventoryOpened = false;
public: 
	Game();

	void gameLoop();

};