#include "ASCIIcamera.h"
#include <iostream>
#include <Windows.h>

void checkTile(char tile) 
{
	if (tile == '#')
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED + FOREGROUND_RED + FOREGROUND_GREEN);
}

void normilize() 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED + FOREGROUND_BLUE + FOREGROUND_GREEN);
}

ASCIICamera::ASCIICamera()
{

}

void ASCIICamera::print()
{
	
	for (int y = 0; y < _buffHeight; y++) 
	{
		for (int x = 0; x < _buffWidth; x++) 
		{
			checkTile(_buff[y][x]);
			std::cout << _buff[y][x];
			normilize();
		}
		std::cout << std::endl;
	}
}

void ASCIICamera::setBuff(char buff[21][21])
{
	for (int i = 0; i < _buffHeight; i++)
		for (int j = 0; j < _buffWidth; j++)
			_buff[i][j] = buff[i][j];
}
