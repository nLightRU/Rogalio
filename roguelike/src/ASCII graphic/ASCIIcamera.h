#pragma once
#include <vector> 

class ASCIICamera 
{
private: 
	const int _buffHeight = 21, _buffWidth = 21;
	std::vector<std::pair<char, unsigned char>> _monstersTextures;
	char _buff[21][21];
public: 
	ASCIICamera();

	void print();
	bool printMonster(char tile);

	void setBuff(char buff[21][21]);

	int getBuffHeight() { return _buffHeight; }
	int getBuffWidth() { return _buffWidth; }

	std::vector<char> showBuffLine(int index);
};