#pragma once
#include <vector>
#include "vec2.h"

struct tile
{
	vec2 _coords;
	vec2 _parent;
	int _f, _g, _h;
	vec2 _parentCoords;

	tile::tile() 
	{

	}

	tile::tile(vec2 coords, int g, int h)
	{
		_coords = coords;
		_g = g;
		_h = h;
		_f = g + h;
	}
};

class Graph 
{
private: 
	std::vector<vec2> _verticies;
	std::vector<std::pair<vec2, vec2>> _edges;
	int findIndexOfPoint(vec2 point);
public: 
	Graph();
	void addVerticies(std::vector<vec2> verticies);
	std::vector<vec2> findPath(vec2 start, vec2 goal); // a star algorithm
	vec2 findPathStep(vec2 start, vec2 goal);
	std::vector<vec2> getVerticies() { return _verticies; }
	vec2 getRandomVertex() { return _verticies[rand() % _verticies.size()]; }
	bool existPoint(vec2 point);
};