#include "gameManager.h"

GameManager::GameManager()
{
	system("cls");
	_player.setPosition(_dungeon.getCurrentFloor().getPlayersPosition());
}

void GameManager::startGame()
{
	char cameraBuff[20][20];
	while (_playerInputManager.getInputType() != Exit) 
	{
		_playerInputManager.input();
		if (_playerInputManager.getInputType() == Moving) 
		{
			_player.shift(_playerInputManager.getMovingDirection());
			_dungeon.setPlayerPosition(_player.getPosition());
		}
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				cameraBuff[9 + i][9 + j] = _dungeon.getCurrentFloor().getFlatTile(
					_player.getPosition().y + i, _player.getPosition().x + j);
		_camera.setBuff(cameraBuff);
		system("cls");
		_camera.print();
	}
}