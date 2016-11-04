#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include "room.h"
#include "floor.h"

int main()
{
	int numberOfRooms = 7;
	Floor test_floor(1, numberOfRooms, "test");

	test_floor.toFile("rooms.txt");
	test_floor.SeparateRooms();
	test_floor.toFile("separated rooms.txt");

	//system("PAUSE");
	return 0;
}