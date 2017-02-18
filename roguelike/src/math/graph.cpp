#include "graph.h"

Graph::Graph() 
{
}

void Graph::addVerticies(std::vector<vec2> verticies) 
{
	for (unsigned int i = 0; i < verticies.size(); i++)
		_verticies.push_back(verticies[i]);
}

bool Graph::pointExistInGraph(vec2 point) 
{
	for (unsigned int i = 0; i < _verticies.size(); i++)
		if (_verticies[i] == point) return true; 
	return false; 
}

std::vector<tile> makeLocality(tile position, vec2 goal, int parentIndex) 
{
	std::vector<tile> locality;
	tile tempTile;

	tempTile.coords += vec2(0, 1);
	tempTile.parent = position.coords;
	tempTile.h = tempTile.coords.squareDistance(goal);
	tempTile.g = position.g + 1;
	tempTile.f = tempTile.g + tempTile.h;
	tempTile.parentIndex = parentIndex;
	locality.push_back(tempTile);

	tempTile.coords += vec2(1, 0);
	tempTile.parent = position.coords;
	tempTile.h = tempTile.coords.squareDistance(goal);
	tempTile.g = position.g + 1;
	tempTile.f = tempTile.g + tempTile.h;
	tempTile.parentIndex = parentIndex;
	locality.push_back(tempTile);

	tempTile.coords += vec2(0, -1);
	tempTile.parent = position.coords;
	tempTile.h = tempTile.coords.squareDistance(goal);
	tempTile.g = position.g + 1;
	tempTile.f = tempTile.g + tempTile.h;
	tempTile.parentIndex = parentIndex;
	locality.push_back(tempTile);

	tempTile.coords += vec2(-1, 0);
	tempTile.parent = position.coords;
	tempTile.h = tempTile.coords.squareDistance(goal);
	tempTile.g = position.g + 1;
	tempTile.f = tempTile.g + tempTile.h;
	tempTile.parentIndex = parentIndex;
	locality.push_back(tempTile);

	return locality;
}

std::vector<tile> makeStartLocality(vec2 position, vec2 goal) 
{
	std::vector<tile> locality; 
	tile tempTile; 

	tempTile.coords += vec2(0, 1);
	tempTile.parent = position;
	tempTile.h = tempTile.coords.squareDistance(goal);
	tempTile.g = 1;
	tempTile.f = tempTile.g + tempTile.h;
	tempTile.parentIndex = 0;
	locality.push_back(tempTile);

	tempTile.coords += vec2(1, 0);
	tempTile.parent = position;
	tempTile.h = tempTile.coords.squareDistance(goal);
	tempTile.g = 1;
	tempTile.f = tempTile.g + tempTile.h;
	tempTile.parentIndex = 0;
	locality.push_back(tempTile);

	tempTile.coords += vec2(0, -1);
	tempTile.parent = position;
	tempTile.h = tempTile.coords.squareDistance(goal);
	tempTile.g = 1;
	tempTile.f = tempTile.g + tempTile.h;
	tempTile.parentIndex = 0;
	locality.push_back(tempTile);

	tempTile.coords += vec2(-1, 0);
	tempTile.parent = position;
	tempTile.h = tempTile.coords.squareDistance(goal);
	tempTile.g = 1;
	tempTile.f = tempTile.g + tempTile.h;
	tempTile.parentIndex = 0;
	locality.push_back(tempTile);

	return locality;
}
 
int findPointInOpenList(std::vector<tile> list, vec2 point) 
{
	for (unsigned int i = 0; i < list.size(); i++) 
		if (list[i].coords == point) return i; 
	return -1; 
}

std::vector<vec2> Graph::findPath(vec2 start, vec2 goal) 
{
	tile tempTile; 
	tile currTile;
	std::vector<vec2> path;
	// g - distance from start in steps
	// h - minimal distance to goal
	// f = g + h
	

	std::vector<tile> openList; 
	std::vector<tile> closedList;

	tempTile.coords = start;

	closedList.push_back(tempTile);

	// make first locality 
	openList.push_back(makeStartLocality(start, goal)[0]);
	openList.push_back(makeStartLocality(start, goal)[1]);
	openList.push_back(makeStartLocality(start, goal)[2]);
	openList.push_back(makeStartLocality(start, goal)[3]);

	int currTileIndex;
	int foundIndex;

	while (!openList.empty()) 
	{
		// erase points which graph doesn't include
		for (unsigned int i = 0; i < openList.size(); i++)
			if (!(pointExistInGraph(openList[i].coords)))
				openList.erase(openList.begin() + i);

		tempTile = openList[0]; // initialize var for tile with minimal "f"
		currTileIndex = 0; // initialize index of tile with minimal "f"

		// find a tile with minimal "f"
		for(unsigned int i = 1; i < openList.size(); i ++)
			if (tempTile.f > openList[i].f) 
			{
				currTileIndex = i; 
				currTile = openList[i];
			}

		for (int i = 0; i < 4; i++)
		{
			tempTile = makeLocality(openList[currTileIndex], goal, currTileIndex)[i];
			if (tempTile.coords == goal)
			{
				closedList.push_back(tempTile);
				openList.clear();
			}
			foundIndex = findPointInOpenList(openList, tempTile.coords) == -1;
			if (foundIndex == -1)
				openList.push_back(tempTile);
			else 
			{
				if (openList[foundIndex].g < tempTile.g)
					tempTile.parent = openList[foundIndex].parent;
				closedList.push_back(tempTile);
			}
		}
	}

	path.push_back(closedList[closedList.size() - 1].coords);
	tempTile = closedList[closedList.size() - 1];
	while (tempTile.coords != start)
	{
		tempTile = closedList[tempTile.parentIndex];
		path.push_back(tempTile.coords);
	}

	return path;
}

vec2 Graph::findPathStep(vec2 start, vec2 goal) 
{
	std::vector<vec2> path = findPath(start, goal);
	return path[path.size() - 1];
}