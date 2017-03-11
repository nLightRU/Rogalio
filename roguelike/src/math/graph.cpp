#include "graph.h"
#include <fstream>
#include <list>
#include <algorithm>

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
	std::ofstream blackListedPoints("Graph points out of graph.txt");
	blackListedPoints << "point " << point.x << " " << point.y << " don't exist in graph"
		<< std::endl;
	return false; 
}

int Graph::findIndexOfPoint(vec2 point) 
{
	for (unsigned int i = 0; i < _verticies.size(); i++)
		if (point == _verticies[i]) return i;
	return -1;
}

bool inList(vec2 point, std::vector<vec2> points) 
{
	for (unsigned int i = 0; i < points.size(); i++)
		if (points[i] == point) return true;
	return false;
}

int findIndexInList(vec2 point, std::vector<tile> list)
{
	for (unsigned int i = 0; i < list.size(); i++)
		if (list[i]._coords == point) return i;
	return -1;
}

std::vector<vec2> Graph::findPath(vec2 start, vec2 goal)
{
	//// g - distance from start in steps
	//// h - minimal distance to goal
	//// f = g + h

	//int g, f, h;

	std::ofstream closedListSizeLog("Graph closed list size.txt");
	std::ofstream openedListSizeLog("Graph opened list size.txt");
	std::vector<vec2> localityDirs;
	localityDirs.push_back(vec2(0, 1));
	localityDirs.push_back(vec2(0, -1));
	localityDirs.push_back(vec2(1, 0));
	localityDirs.push_back(vec2(-1, 0));

	//initialization of current tile
	tile currentTile;
	currentTile._coords = start;
	currentTile._g = 0; 
	currentTile._h = currentTile._coords.squareDistance(goal);
	currentTile._f = currentTile._g + currentTile._h;
	
	std::vector<vec2> path;

	
	if (!pointExistInGraph(start))
	{
		path.push_back(start);
		return path;
	}
		 
	std::vector<tile> openedList;
	std::vector<tile> closedList;
	std::vector<vec2> closedListCoords; // for making the path
	std::vector<vec2> blackList; // for locality points wich is not exist in graph

	closedList.push_back(currentTile);
	closedListCoords.push_back(currentTile._coords);

	tile localityTile;

	tile comparedTile;
	int comparedTileIndex;

	while (!openedList.empty()) 
	{
		// finding locality tile with the smallest value of f
		// in the opened list 
		comparedTile = openedList[0];
		comparedTileIndex = 0;
		for (int i = 1; i < openedList.size(); i++) 
			if (comparedTile._f > openedList[i]._f)
			{
				comparedTileIndex = i;
				comparedTile = openedList[i];
			}

		currentTile = openedList[comparedTileIndex];
		openedList.erase(openedList.begin() + comparedTileIndex);

		openedListSizeLog << "erasing" << std::endl; // logs

		closedList.push_back(currentTile);
		closedListCoords.push_back(currentTile._coords);

		closedListSizeLog << closedList.size() << std::endl; // logs

		for (int i = 0; i < 4; i++) 
		{
			localityTile._coords = currentTile._coords + localityDirs[i];
			localityTile._g = currentTile._g + 1;
			localityTile._h = localityTile._coords.squareDistance(goal);
			localityTile._f = localityTile._g + localityTile._h;

			if (localityTile._coords == goal)
			{
				closedList.push_back(localityTile);
				closedListSizeLog << closedList.size() << std::endl;
				break;
			}

			if (!pointExistInGraph(localityTile._coords))
				blackList.push_back(localityTile._coords);

			if (!inList(localityTile._coords, blackList))
				if (inList(currentTile._coords, closedListCoords))
				{
					for (unsigned int i = 0; i < closedList.size(); i++)
						if (currentTile._coords == closedList[i]._coords)
						{
							comparedTile = closedList[i];
							comparedTileIndex = i;
						}
					if (localityTile._g < comparedTile._g)
					{
						closedList[comparedTileIndex]._g = localityTile._g;
						closedList[comparedTileIndex]._parentCoords = localityTile._parentCoords;
					}
				}
				else
				{
					openedList.push_back(localityTile);
					openedListSizeLog << openedList.size() << std::endl;
				}
		}
	}

	currentTile = closedList[closedList.size() - 1];

	while (currentTile._coords != start)
	{
		path.push_back(currentTile._parentCoords);
		currentTile = closedList[findIndexInList(currentTile._parentCoords, closedList)];
	}

	return path;
}

vec2 Graph::findPathStep(vec2 start, vec2 goal) 
{
	std::vector<vec2> path = findPath(start, goal);
	return path[0];
}