#include "game.h"
#include "../math/vec2.h"
#include <iostream>

Game::Game()
{
	system("cls");
	_floorManager.initialize(_dungeon.getFloors()[0]);
	_player.setPosition(_floorManager.getPlayersPosition());
}

void Game::gameLoop()
{	
	std::cout << "Press any key to start game" << std::endl;
	bool playerDeath;
	while (_playerInputManager.getInputType() != Exit)
	{
		if (PlayersTurn()) 
		{
			_floorManager.initialize(_dungeon.getNextFloor());
			_player.setPosition(_floorManager.getPlayersPosition());
		}
		if (MonstersTurn())
		{
			system("cls");
			std::cout << "You died" << std::endl;
			break;
		}
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

bool Game::PlayersTurn() 
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

	if (findMonsterOnPosition(tile) != -1)
		_floorManager.hitMonster(_player.makeHit(), tile);
	else if (tile == _floorManager.getTrapPosition()) return true;
	else if (checkTile(tile)) 
		{
			_player.setPosition(_player.getPosition() + movingDirection);
			_floorManager.movePlayer(_player.getPosition());
		}
	return false;
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
	std::cout << "floor " << _dungeon.getCurrentFloorNumber() + 1 << "/";
	std::cout << _dungeon.getFloors().size() << std::endl;
	std::cout << "w - up" << std::endl; 
	std::cout << "a - left" << std::endl;
	std::cout << "s - down" << std::endl;
	std::cout << "d - right" << std::endl;
	std::cout << "p - exit" << std::endl;
}

bool Game::MonstersTurn() 
{
	_player.decreaseHealth(_floorManager.makeMonstersTurn());
	if (_player.getHealth() <= 0)
		return true;
	return false;
}

int Game::findMonsterOnPosition(vec2 position) 
{
	for (unsigned int i = 0; i < _floorManager.getMonsters().size(); i++)
		if (_floorManager.getMonsters()[i].getPosition() == position)
			return i;

	return -1;
}