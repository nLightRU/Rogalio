#include "vec2.h"
#include <math.h>
vec2::vec2() 
{
	x = 0;
	y = 0;
}

vec2::vec2(int x, int y)
{
	this->x = x;
	this->y = y;
}

int vec2::squareDistance(vec2 point) 
{
	return pow(point.x - x, 2) + pow(point.y - y, 2);
}

void vec2::shift(int dx, int dy)
{
	this->x += dx;
	this->y += dy;
}

vec2 vec2::operator+(vec2 summand)
{
	return vec2(this->x + summand.x, this->y + summand.y);
}

bool vec2::operator==(vec2 point) 
{
	return (this->x == point.x && this->y == point.y);
}

bool vec2::operator!=(vec2 point)
{
	return (this->x != point.x || this->y != point.y);
}

vec2 vec2::operator+=(vec2 summand) 
{
	return vec2(this->x + summand.x, this->y + summand.y);
}