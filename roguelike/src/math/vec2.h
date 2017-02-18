#pragma once

struct vec2 
{
	int x;
	int y;

	vec2(int x, int y);
	vec2();

	int squareDistance(vec2 point);
	void shift(int dx, int dy);

	vec2 operator+(vec2 summand);
	vec2 operator+=(vec2 summand);
	bool operator==(vec2 point);
	bool operator!=(vec2 point);
};