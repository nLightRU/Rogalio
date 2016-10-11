#include "room.h"
#include <math.h>
Room::Room() 
{
	_height = 0;
	_width = 0;
	_x = 0;
	_y = 0;
}

Room::Room(int x, int y, int width, int height) 
{
	_height = height;
	_width = width;
	_x = x;
	_y = y;
}

bool Room::touching(Room b) 
{
	// a_l_t - distane from coords origin to Room a - left top corner
	int a_l_b, a_r_b, a_l_t, a_r_t;

	// b_l_t - distane from coords origin to Room b - left top corner
	int b_l_b, b_r_b, b_l_t, b_r_t;

	if (this->_x % 2 == 0)
	{
		if (this->_y % 2 == 0)
		{
			a_l_b = sqrt( pow(_x - _x / 2 + 1, 2) + pow(_y - _y / 2 + 1, 2) );
			a_l_t = sqrt( pow(_x - _x/2 +1, 2) + pow(_y + _y / 2 + 1, 2) );
			a_r_b = sqrt(pow(_x - _x / 2 + 1, 2) + pow(_y + _y / 2 + 1, 2));
		}
	}

}