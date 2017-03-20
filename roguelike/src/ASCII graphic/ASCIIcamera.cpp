#include "ASCIIcamera.h"
#include <iostream>
#include <Windows.h>

ASCIICamera::ASCIICamera()
{

}

void ASCIICamera::print()
{
	
	for (int y = 0; y < _buffHeight; y++) 
	{
		for (int x = 0; x < _buffWidth; x++) 
			std::cout << _buff[y][x];
		std::cout << std::endl;
	}
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
