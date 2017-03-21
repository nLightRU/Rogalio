#include "ASCIIcamera.h"
#include "../data/monsterInfo.h"
#include <iostream>
#include <Windows.h>

ASCIICamera::ASCIICamera()
{
	MonsterInfo info;

	std::pair<char, unsigned char> _pair;

	std::vector<MonsterInfo> allMonsters = info.createAllMonsters();

	for (unsigned int i = 0; i < allMonsters.size(); i++)
	{
		_pair.first = allMonsters[i].getTexture();
		_pair.second = allMonsters[i].getColor();
		_monstersTextures.push_back(_pair);
	}
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
		{
			bool monsterPrinted = printMonster(_buff[y][x]);
			if (!monsterPrinted) std::cout << _buff[y][x];
		}
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

bool ASCIICamera::printMonster(char tile) 
{
	for (unsigned int i = 0; i < _monstersTextures.size(); i++) 
	{
		if (tile == _monstersTextures[i].first)
		{
			setTextColors(_monstersTextures[i].second);
			std::cout << _monstersTextures[i].first;
			setTextColors(FOREGROUND_BLUE + FOREGROUND_GREEN + FOREGROUND_RED);
			return true;
		}
	}
	return false;
}
