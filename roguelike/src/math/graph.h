#pragma once
#include <vector>
#include "vec2.h"

struct tile
{
	vec2 coords;
	vec2 parent;
	int f, g, h;
	int parentIndex;
};

class Graph 
{
private: 
	std::vector<vec2> _verticies;
	std::vector<std::pair<vec2, vec2>> _edges;
	bool pointExistInGraph(vec2 point);
public: 
	Graph();
	void addVerticies(std::vector<vec2> verticies);
	std::vector<vec2> findPath(vec2 start, vec2 goal); // a star algorithm
	vec2 findPathStep(vec2 start, vec2 goal);
};