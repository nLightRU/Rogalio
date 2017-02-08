#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "math\vec2.h"

const int height = 20, width = 20;
char room[height][width];

void printRoom() 
{
	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++)
			std::cout << room[y][x];
		std::cout << std::endl;
	}
}

void clearRoom() 
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			room[y][x] = '.';
		}
	}

	for (int i = 0; i < width; i++)
	{
		room[height - 1][i] = '#';
		room[0][i] = '#';
	}

	for (int i = 0; i < height; i++)
	{
		room[i][width -1] = '#';
		room[i][0] = '#';
	}
}

void placePoint(int x, int y, char symbol)
{
	room[y][x] = symbol;
}

void placePoint(vec2 point, char symbol) 
{
	room[point.y][point.x] = symbol;
}

int main()
{

	char move;
	char player = '@';

	vec2 playerCoords = vec2(5,5);

	clearRoom();
	placePoint(playerCoords.x, playerCoords.y, player);
	printRoom();

	do
	{
		move = _getch();
		if (move == 'a') playerCoords.x--;
		if (move == 'd') playerCoords.x++;
		if (move == 'w') playerCoords.y--;
		if (move == 's') playerCoords.y++;
		system("cls");
		clearRoom();
		placePoint(playerCoords, player);
		printRoom();
	} while (move != 'z');
	
	std::cout << std::endl;

	system("pause");
	return 0;
}