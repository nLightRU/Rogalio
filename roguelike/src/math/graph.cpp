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

bool Graph::existPoint(vec2 point)
{
	for (unsigned int i = 0; i < _verticies.size(); i++)
		if (_verticies[i] == point) return true;
	return false;
}

int Graph::findIndexOfPoint(vec2 point)
{
	for (unsigned int i = 0; i < _verticies.size(); i++)
		if (point == _verticies[i]) return i;
	return -1;
}

bool pointInList(vec2 point, std::vector<vec2> points)
{
	for (unsigned int i = 0; i < points.size(); i++)
		if (points[i] == point) return true;
	return false;
}

int findIndexOfPointInList(vec2 point, std::vector<tile> list)
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
	std::ofstream ways("Graph pathginding calls.txt");
	ways << start.x << " " << start.y << "->" << goal.x << " " << goal.y << std::endl;
	std::vector<vec2> localityDirs;
	localityDirs.push_back(vec2(0, 1));
	localityDirs.push_back(vec2(0, -1));
	localityDirs.push_back(vec2(1, 0));
	localityDirs.push_back(vec2(-1, 0));

	//initialization of current tile

	std::vector<vec2> path;


	if (!existPoint(start))
	{
		path.push_back(start);
		ways << "start out of graph" << std::endl;
		return path;
	}

	std::vector<tile> openedList;
	std::vector<tile> closedList;
	std::vector<vec2> closedListCoords; // for making the path

	tile startTile;
	startTile._coords = start;
	startTile._g = 0;
	startTile._h = startTile._coords.squareDistance(goal);
	startTile._f = startTile._g + startTile._h;

	closedListCoords.push_back(startTile._coords);
	closedList.push_back(startTile);

	// start locality 
	openedListSizeLog << "start " << start.x << " " << start.y << std::endl; //logs
	tile localityTile;
	for (int i = 0; i < 4; i++)
	{
		localityTile._coords = startTile._coords + localityDirs[i];
		localityTile._h = localityTile._coords.squareDistance(goal);
		localityTile._g = startTile._g + 1;
		localityTile._f = localityTile._g + localityTile._h;
		openedList.push_back(localityTile);
	}
	int count = 0;
	while (!openedList.empty())
	{
		// finding locality tile with the smallest value of f
		// in the opened list 
		openedListSizeLog << std::endl <<"iteration " << ++count << std::endl;
		openedListSizeLog << "size " << openedList.size() << std::endl; //logs
		tile currentTile = openedList[0];
		int indexOfCurrentTile;
		for (int i = 1; i < openedList.size(); i++)
			if (currentTile._f > openedList[i]._f)
			{
				currentTile = openedList[i];
				indexOfCurrentTile = i;
			}

		openedList.erase(openedList.begin() + indexOfCurrentTile);

		openedListSizeLog << "erasing "; // logs
		openedListSizeLog << indexOfCurrentTile << std::endl; // logs 

		closedList.push_back(currentTile);
		closedListCoords.push_back(currentTile._coords);

		closedListSizeLog << closedList.size() << std::endl; // logs

		for (int i = 0; i < 4; i++)
		{
			openedListSizeLog << "locality tile "; // logs
			localityTile._coords = currentTile._coords + localityDirs[i];
			localityTile._g = currentTile._g + 1;
			localityTile._h = localityTile._coords.squareDistance(goal);
			localityTile._f = localityTile._g + localityTile._h;
			openedListSizeLog << localityTile._coords.x << " " << localityTile._coords.y << " ";
			if (localityTile._coords == goal)
			{
				closedList.push_back(localityTile);
				closedListSizeLog << closedList.size() << std::endl;
				break;
			}

			// if point out of graph we skip it
			if (!existPoint(localityTile._coords))
			{
				openedListSizeLog << "in black list" << std::endl; // logs
				continue;
			}

			if (pointInList(currentTile._coords, closedListCoords))
			{
				openedListSizeLog << "in closed list already "; // logs

				tile tempTile; 
				int tempTileIndex;
				// find index of point in closed list
				for (unsigned int i = 0; i < closedList.size(); i++)
					if (currentTile._coords == closedList[i]._coords)
					{
						tempTile = closedList[i];
						tempTileIndex = i;
					}

				// rewriting points if we find shorter way
				if (localityTile._g < tempTile._g)
				{
					openedListSizeLog << "G less" << std::endl;
					closedList[tempTileIndex]._g = localityTile._g;
					closedList[tempTileIndex]._parentCoords = localityTile._parentCoords;
				}
				else openedListSizeLog << "G more" << std::endl; // logs
			}
			else
			{
				openedList.push_back(localityTile);
				openedListSizeLog << "pushing new " << localityTile._coords.x << " " <<
					localityTile._coords.y;
				openedListSizeLog << " size now ";
				openedListSizeLog << openedList.size() << std::endl;
			}
		}
	}

	tile currentTile;
	currentTile = closedList[closedList.size() - 1];

	std::ofstream pathLog("Path.txt");
	while (currentTile._coords != start)
	{
		path.push_back(currentTile._parentCoords);
		pathLog << currentTile._coords.x << " " << currentTile._coords.y << std::endl;
		currentTile = closedList[findIndexOfPointInList(currentTile._parentCoords, closedList)];
	}

	return path;
}

vec2 Graph::findPathStep(vec2 start, vec2 goal)
{
	std::vector<vec2> path = findPath(start, goal);
	return path[0];
}