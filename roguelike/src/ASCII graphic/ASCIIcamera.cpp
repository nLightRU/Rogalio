#include "ASCIIcamera.h"
#include <iostream>
#include <Windows.h>

ASCIICamera::ASCIICamera()
{
	_monstersTextures.push_back('m'); // monster (for test)
	_monstersTextures.push_back('g'); // goblin or gremlin
	_monstersTextures.push_back('r'); // rat
	_monstersTextures.push_back('s'); // skeleton
}

void setTextColors(unsigned char attr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}

void ASCIICamera::print()
{
	for (int i = 0; i < 19; i++)
		std::cout << " ";
	for (int i = 0; i < 20; i++)
		std::cout << "-";
	for (int y = 0; y < _buffHeight; y++) 
	{
		for (int i = 0; i < 19; i++)
			std::cout << " ";
		for (int x = 0; x < _buffWidth; x++) 
			std::cout << _buff[y][x];
		std::cout << std::endl;
	}

	for (int i = 0; i < 19; i++)
		std::cout << " ";
	for (int i = 0; i < 20; i++)
		std::cout << "-";
}

void ASCIICamera::setBuff(char buff[21][21])
{
	for (int i = 0; i < _buffHeight; i++)
		for (int j = 0; j < _buffWidth; j++)
			_buff[i][j] = buff[i][j];
}

std::vector<char> ASCIICamera::showBuffLine(int index) 
{
	std::vector<char> line;
	for (int i = 0; i < _buffWidth; i++)
		line.push_back(_buff[index][i]);
	return line;
}
