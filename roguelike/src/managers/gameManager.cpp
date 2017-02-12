#include "gameManager.h"
#include "../math/vec2.h"
#include <iostream>

GameManager::GameManager()
{
	system("cls");
	_player.setPosition(_floor.getPlayersPosition());
	_forbiddenTextures.push_back('#');
	_forbiddenTextures.push_back('m');
}

void GameManager::startGame()
{
	vec2 movingDirection;
	while (_playerInputManager.getInputType() != Exit)
	{
		Input();
		PrintCamera();				
		PrintUI();
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

	if (_playerInputManager.getInputType() == OpenInventory)
	{
		if (inventoryOpened)
			inventoryOpened = false;
		else inventoryOpened = true;
	}

	vec2 movingDirection = _playerInputManager.getMovingDirection();
	vec2 tile = vec2(_player.getPosition() + movingDirection);

	if (checkTile(tile) && !inventoryOpened)
	{
		_player.setPosition(_player.getPosition() + movingDirection);
		_floor.movePlayer(_player.getPosition());
	}
}

bool GameManager::checkTile(vec2 position) 
{
	for (unsigned int i = 0; i < _forbiddenTextures.size(); i++) 
		if (_floor.getFlatTile(position) == _forbiddenTextures[i])
			return false;
	return true;
}

void GameManager::PrintUI()
{
	std::cout << std::endl;
	std::cout << "Health " << _player.getHealth() << "/" << _player.getMaxHealth();
	std::cout << std::endl;
	std::cout << "Mana " << _player.getMana() << "/" << _player.getMaxMana();
	std::cout << std::endl;
	std::cout << "Inventory "; 
	if (inventoryOpened) std::cout << "opened" << std::endl;
	else std::cout << "closed" << std::endl;
}