#pragma once
#include "playerInputManager.h"
#include "../ASCII graphic/camera.h"
#include "../units/player.h"
#include "../structures/dungeon.h"
enum GAME_STATES {MainMenu, PlayerTurn, MonstersTurn};

class GameManager
{
private: 

	std::vector<char> _forbiddenTextures;

	PlayerInputManager _playerInputManager;
	Player _player;
	Camera _camera;
	GAME_STATES _state;
	Floor _floor; 

	void PrintCamera();
	void PrintUI();
	void Input();

	bool checkTile(vec2 position);
public: 
	GameManager();

	void startGame();

};