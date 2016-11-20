#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include "room.h"
#include "floor.h"

std::vector<int> getShiftings(Room a, Room b)
{
	int dx, dy, dxa, dya, dxb, dyb;

	dx = fmin(abs(a.getR() - b.getL()) + 1, abs(a.getL() - b.getR()) + 1);
	dy = fmin(abs(a.getB() - b.getT()) - 1, abs(a.getT() - b.getB()) - 1);

	if (abs(dx) < abs(dy)) dy = 0;
	else dx = 0;

	dxa = -dx / 2;
	dya = -dy / 2;

	dxb = dx / 2;
	dyb = dy / 2;

	std::vector<int> shiftings;

	shiftings.push_back(dxa);
	shiftings.push_back(dya);
	shiftings.push_back(dxb);
	shiftings.push_back(dyb);

	return shiftings;
}

int main()
{
	Room a(40, 20, 20, 15);
	Room b(55, 25, 30, 27);

	std::vector<int> shifting = getShiftings(a,b);

	Floor test_floor;
	Floor test_floor_new;

	test_floor.AddRoom(a);
	test_floor.AddRoom(b);

	a.shift(shifting[0], shifting[1]);
	b.shift(shifting[2], shifting[3]);

	test_floor_new.AddRoom(a);
	test_floor_new.AddRoom(b);

	test_floor.toFile("rooms.txt");
	test_floor_new.toFile("separated rooms.txt");

	system("PAUSE");
	return 0;
}