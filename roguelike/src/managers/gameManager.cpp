#include "gameManager.h"
#include "../math/vec2.h"

GameManager::GameManager()
{
	system("cls");
	_player.setPosition(_floor.getPlayersPosition());
}

void GameManager::startGame()
{
	vec2 movingDirection;
	while (_playerInputManager.getInputType() != Exit)
	{
		Input();

		PrintCamera();
	}
}

void GameManager::PrintCamera() 
{
	char cameraBuff[21][21];

	for (int y = 0; y < 11; y++)
		for (int x = 0; x < 11; x++)
		{
			cameraBuff[y][x] = _floor.getFlatTile(_player.getPosition().y - 10 + y,
				_player.getPosition().x - 10 + x
			);
		}

	for (int y = 0; y < 11; y++)
		for (int x = 10; x < 21; x++)
		{
			cameraBuff[y][x] = _floor.getFlatTile(_player.getPosition().y - 10 + y,
				_player.getPosition().x - 10 + x
			);
		}

	for (int y = 10; y < 21; y++)
		for (int x = 0; x < 11; x++)
		{
			cameraBuff[y][x] = _floor.getFlatTile(_player.getPosition().y - 10 + y,
				_player.getPosition().x - 10 + x
			);
		}

	for (int y = 10; y < 21; y++)
		for (int x = 10; x < 21; x++)
		{
			cameraBuff[y][x] = _floor.getFlatTile(_player.getPosition().y - 10 + y,
				_player.getPosition().x - 10 + x
			);
		}

	_camera.setBuff(cameraBuff);
	system("cls");
	_camera.print();
}

void GameManager::Input() 
{
	_playerInputManager.input();
	vec2 movingDirection = _playerInputManager.getMovingDirection();

	if (_floor.getFlatTile(_player.getPosition().y + movingDirection.y,
		_player.getPosition().x + movingDirection.x)
		!= '#')
	{
		_player.setPosition(_player.getPosition().x + movingDirection.x,
			_player.getPosition().y + movingDirection.y);
		_floor.movePlayer(_player.getPosition());
	}
}