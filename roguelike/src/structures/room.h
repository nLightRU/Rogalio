#pragma once
#include "../math/vec2.h"

class Room
{

private:
	// x, y - left top corner coordinates
	int _height, _width;
	int _left, _right, _top, _bottom;
	int _joiningLeft, _joiningRight;
	int _parent;
	vec2 _center;
	int _x, _y;
	bool _includesInFloor = false;
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

	int getRightJoin() { return _joiningRight; }
	int getLeftJoin() { return _joiningLeft; }
	int getParent() { return _parent; };

	vec2 getCenter() { return _center; }

	int getSquare() { return _height * _width; }

	bool isInclude() { return _includesInFloor; }

	void setX(int x);
	void setY(int y);

	void setJoinings(int right, int left);
	void setLeftJoining(int index);
	void setRightJoining(int index);
	void setParent(int index);

	bool touches(Room b);
	void shift(int dx, int dy);
	int countDistance(Room b);
	bool includePoint(vec2 point);
	void includeInFloor() { _includesInFloor = true; }
	vec2 createRandomPoint();
};