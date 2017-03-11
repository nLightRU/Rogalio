#include "game.h"
#include "../math/vec2.h"
#include <iostream>

Game::Game()
{
	system("cls");
	_player.setPosition(_floorManager.getPlayersPosition());
	_forbiddenTextures.push_back('#');
	_forbiddenTextures.push_back('m');
}

void Game::gameLoop()
{	
	std::cout << "Press any key to start game" << std::endl;
	while (_playerInputManager.getInputType() != Exit)
	{
		Input();
		MonstersTurn();
		PrintCamera();				
		PrintUI();
	}
}  

void Game::PrintCamera() 
{
	char cameraBuff[21][21];

	for (int y = 0; y < 11; y++)
		for (int x = 0; x < 11; x++)
		{
			cameraBuff[y][x] = _floorManager.getFlatTile(_player.getPosition().y - 10 + y,
				_player.getPosition().x - 10 + x
			);
		}

	for (int y = 0; y < 11; y++)
		for (int x = 10; x < 21; x++)
		{
			cameraBuff[y][x] = _floorManager.getFlatTile(_player.getPosition().y - 10 + y,
				_player.getPosition().x - 10 + x
			);
		}

	for (int y = 10; y < 21; y++)
		for (int x = 0; x < 11; x++)
		{
			cameraBuff[y][x] = _floorManager.getFlatTile(_player.getPosition().y - 10 + y,
				_player.getPosition().x - 10 + x
			);
		}

	for (int y = 10; y < 21; y++)
		for (int x = 10; x < 21; x++)
		{
			cameraBuff[y][x] = _floorManager.getFlatTile(_player.getPosition().y - 10 + y,
				_player.getPosition().x - 10 + x
			);
		}

	_ASCIIcamera.setBuff(cameraBuff);
	system("cls");
	_ASCIIcamera.print();
}

void Game::Input() 
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
		_floorManager.movePlayer(_player.getPosition());
	}
}

bool Game::checkTile(vec2 position) 
{
	for (unsigned int i = 0; i < _forbiddenTextures.size(); i++) 
		if (_floorManager.getFlatTile(position) == _forbiddenTextures[i])
			return false;
	return true;
}

void Game::PrintUI()
{
	std::cout << std::endl;
	std::cout << "Health " << _player.getHealth() << "/" << _player.getMaxHealth();
	std::cout << std::endl;
	std::cout << "Mana " << _player.getMana() << "/" << _player.getMaxMana();
	std::cout << std::endl;
	std::cout << "Inventory "; 
	if (inventoryOpened) std::cout << "opened" << std::endl;
	else std::cout << "closed" << std::endl;
	std::cout << "w - up" << std::endl; 
	std::cout << "a - left" << std::endl;
	std::cout << "s - down" << std::endl;
	std::cout << "d - right" << std::endl;
	std::cout << "p - exit" << std::endl;
}

void Game::MonstersTurn() 
{
	_floorManager.makeMonstersTurn();
}