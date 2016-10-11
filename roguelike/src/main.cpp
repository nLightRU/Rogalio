#include <iostream>
#include <fstream>
#include <math.h>

#include "room.h"

void printRoom(int w, int h) 
{
	std::cout << "w:" << w << " " << "h:" << h << std::endl;
	for (int j = 0; j < w; j++)
		std::cout << "#";
	std::cout << std::endl;
	for (int j = 0; j < h - 2; j++)
	{
		std::cout << "#";
		for (int k = 0; k < w - 2; k++)
		{
			if (k == w / 2 - 1 && j == h / 2 - 1)
				std::cout << "x";
			else std::cout << ".";
		}
		std::cout << "#";
		std::cout << std::endl;
	}
	for (int j = 0; j < w; j++)
		std::cout << "#";
}

int main() 
{
	// генерация комнат
	
	
	int w, h;
	
	for (int i = 0; i < 10; i++) {
		w = rand() % (20 - 10 + 1) + 10;
		h = rand() % (20 - 10 + 1) + 10;
		printRoom(w, h);
		std::cout << std::endl;
		std::cout << std::endl;
	}
	


	std::ofstream map_file("map.txt");

	char map_char[100][100];
	//for()


	system("PAUSE");

	return 0;
}