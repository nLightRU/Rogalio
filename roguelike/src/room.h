#pragma once


class Room 
{
private: 
	// x, y - central coordinates
	int _x, _y, _height, _width;
	

public: 
	Room();
	Room(int x, int y, int width, int height);
	void setHeight(int height) { _height = height; }
	void setWidth(int width) { _width = width; }

	bool touching(Room b);
	

};