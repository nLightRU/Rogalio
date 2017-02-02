#pragma once

struct vec2 
{
	int x;
	int y;

	vec2(int x, int y);
	vec2();
	int squareDistance(vec2 point);
	void shift(int dx, int dy);
};

