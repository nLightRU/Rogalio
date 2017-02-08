#include "playerInputManager.h"
#include <conio.h>

void PlayerInputManager::input() 
{
	char key; 

	key = getch();

	if (key == 'a' || key == 'w' || key == 's' || key == 'd')
	{
		_inputType = Moving;
		switch (key)
		{
		case 'w':
			_movingDirection = vec2(0, -1);
			break;
		case 'a':
			_movingDirection = vec2(-1, 0);
			break;
		case 's':
			_movingDirection = vec2(0, 1);
			break;
		case 'd':
			_movingDirection = vec2(1, 0);
			break;
		}
	}
	if (key == 'p')
		_inputType = Exit;
	if (key == 'i')
		_inputType = OpenInventory;
}