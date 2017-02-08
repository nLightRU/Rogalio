#pragma once
#include "playerInputManager.h"
#include "../graphic/camera.h"
#include "../units/player.h"
enum GAME_STATES {MainMenu, PlayerTurn, MonstersTurn};

class GameManager
{
private: 
	PlayerInputManager _playerInputManager;
	Player _player;
	Camera _camera;
	GAME_STATES _state;
public: 
	GameManager();
	void startGame();

};