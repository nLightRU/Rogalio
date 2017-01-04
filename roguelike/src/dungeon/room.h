#pragma once
#include "../math/vec2.h"

class Room 
{

private: 
	// x, y - left bottom corner coordinates
	int _height, _width;
	int _left, _right, _top, _bottom;
	int _x, _y;
public: 
	Room();
	Room(int x, int y, int width, int height);
	
	int getW() { return _width; }
	int getH() { return _height; }
	int getX() { return _x; }
	int getY() { return _y; }

	int getL() { return _left; }
	int getR() { return _right; }
	int getT() { return _top; }
	int getB() { return _bottom; }

	void setX(int x);
	void setY(int y);

	bool touches(Room b);
	void shift(int dx, int dy);

};