#include "game.h"
#include "../math/vec2.h"
#include <iostream>

Game::Game()
{
	system("cls");
	_dungeon = Dungeon(25);
	_floorManager.initialize(_dungeon.getFloors()[0]);
	_player.setPosition(_floorManager.getPlayersPosition());
}

void Game::gameLoop()
{	
	std::cout << "Press any key to start game" << std::endl;
	bool playerDeath;
	while (_playerInputHandler.getInputType() != Exit)
	{
		if (PlayersTurn()) 
		{
			if (_dungeon.getCurrentFloorNumber() == _dungeon.getFloors().size()) 
			{
				std::cout << "You end this game, ya vas pozdravlyau" << std::endl;
				break;
			}
			_floorManager.initialize(_dungeon.getNextFloor());
			_player.setPosition(_floorManager.getPlayersPosition());
		}
		if (MonstersTurn())
		{
			system("cls");
			std::cout << "You died" << std::endl;
			break;
		}
		Render();
	}
}  

void Game::SetCamera()
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
}

bool Game::PlayersTurn() 
{
	_playerInputHandler.input();

	if (_playerInputHandler.getInputType() == OpenInventory)
	{
		if (inventoryOpened)
			inventoryOpened = false;
		else inventoryOpened = true;
	}

	vec2 movingDirection = _playerInputHandler.getMovingDirection();
	vec2 tile = vec2(_player.getPosition() + movingDirection);

	if (findMonsterOnPosition(tile) != -1)
		_floorManager.hitMonster(_player.makeHit(), tile);
	else if (tile == _floorManager.getTrapPosition()) return true;
	else if(_floorManager.checkTile(tile))
		{
			_player.setPosition(_player.getPosition() + movingDirection);
			_floorManager.movePlayer(_player.getPosition());
		}
	return false;
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

void Game::Render() 
{
	SetCamera();
	_ASCIIrenderer.setCamera(_ASCIIcamera);
	_ASCIIrenderer.showGameplayScreen(_player, _dungeon);
}