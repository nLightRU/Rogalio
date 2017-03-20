#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "math\vec2.h"
#include "structures\floor.h"
#include "math\graph.h"
#include "managers\game.h"
#include <Windows.h>
#include "ASCII graphic\renderer.h"

//void setTextColor(unsigned char attr)
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
//}

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
	//setTextColor(FOREGROUND_RED + FOREGROUND_BLUE + FOREGROUND_GREEN );
	/*Game game;
	game.gameLoop();*/

	Renderer r;
	Player player;
	r.showGameplayScreen(player);

	system("pause");
	return 0;
}