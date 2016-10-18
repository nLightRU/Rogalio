#pragma once


class Room 
{
private: 
	// x, y - left bottom corner coordinates
	int _x, _y, _height, _width;

public: 
	Room();
	Room(int x, int y, int width, int height);

	int getW() { return _width; }
	int getH() { return _height; }
	int getX() { return _x; }
	int getY() { return _y; }
	int getCenX() { return _x + _width / 2; }
	int getCenY() { return _y + _height / 2; }

	void setHeight(int height) { _height = height; }
	void setWidth(int width) { _width = width; }

	bool touching(Room b);
	

};