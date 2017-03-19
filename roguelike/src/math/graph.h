#pragma once
#include <vector>
#include "vec2.h"

struct tile
{
	vec2 coords;
	vec2 parent;
	int f, g, h;
	void countDistance(vec2 goal) { this->h = this->coords.squareDistance(goal); }
	void countFunction() { this->f = this->g + this->h; }
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
	std::vector<vec2> findPath(vec2 _start, vec2 _goal); // a star algorithm
	vec2 findPathStep(vec2 start, vec2 goal);
	std::vector<vec2> getVerticies() { return _verticies; }
	vec2 getRandomVertex() { return _verticies[rand() % _verticies.size()]; }
	bool inGraph(vec2 point);
};