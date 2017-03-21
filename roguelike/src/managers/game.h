#pragma once
#include "playerInputHandler.h"
#include "../ASCII graphic/ASCIIcamera.h"
#include "../ASCII graphic/ASCIIrenderer.h"
#include "../units/player.h"
#include "../structures/dungeon.h"
#include "floorManager.h"

enum GAME_STATES {MainMenu, PlayerTurn, MonstersTurn};

class Game
{
private: 

	std::vector<char> _forbiddenTextures;

	PlayerInputHandler _playerInputHandler;
	Player _player;

	ASCIICamera _ASCIIcamera;
	ASCIIRenderer _ASCIIrenderer;

	GAME_STATES _state;

	FloorManager _floorManager;
	Dungeon _dungeon;

	void SetCamera();
	bool MonstersTurn();
	bool PlayersTurn();
	void Render();

	int findMonsterOnPosition(vec2 position);

	bool inventoryOpened = false;
public: 
	Game();

	void gameLoop();

};