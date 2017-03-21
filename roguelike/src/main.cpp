#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "math\vec2.h"
#include "managers\game.h"
#include <Windows.h>

void settTextColor(unsigned char attr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
	std::cout << "hello world" << std::endl;
}

/*
FOREGROUND_BLUE
FOREGROUND_GREEN
FOREGROUND_RED
FOREGROUND_INTENSITY

BACKGROUND_BLUE
BACKGROUND_GREEN
BACKGROUND_RED
BACKGROUND_INTENSITY
*/

int main()
{
	
	Game game;
	game.gameLoop();


	system("pause");
	return 0;
}