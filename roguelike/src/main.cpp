#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "math\vec2.h"
#include "structures\floor.h"
#include "managers\gameManager.h"

int main() 
{
	//system("color 0F");

	GameManager manager;
	manager.startGame();

	system("pause");
	return 0;
}