#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "math\vec2.h"
#include "structures\floor.h"
#include "managers\game.h"

int main() 
{
	Game game;
	game.gameLoop();

	system("pause");
	return 0;
}