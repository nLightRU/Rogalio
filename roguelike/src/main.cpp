#include <iostream>
#include <fstream>
#include <math.h>

#include "floor.h"

int main() 
{
	std::ofstream map_file("map.txt");
	Floor floor(1);
	for (int i = 0; i < floor.getH(); i++) 
	{
		for (int j = 0; j < floor.getW(); j++)
			map_file << floor.getFlat(i,j);
		map_file << std::endl;
	}

	map_file.close();
	return 0;
}