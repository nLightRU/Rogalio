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

int findInClosedList(tile _tile, std::vector<tile> closedlist)
{
	for (unsigned int i = 0; i < closedlist.size(); i++)
		if (_tile.coords == closedlist[i].coords) return i;
	return -1;
}

int findInClosedList(vec2 point, std::vector<tile> closedlist)
{
	for (unsigned int i = 0; i < closedlist.size(); i++)
		if (point == closedlist[i].coords) return i;
	return -1;
}

bool Graph::inGraph(vec2 point)
{
	for (unsigned int i = 0; i < _verticies.size(); i++)
		if (_verticies[i] == point) return true;
	return false;
}

std::vector<vec2> Graph::findPath(vec2 _start, vec2 _goal)
{
	vec2 goal;
	vec2 start;

	goal.x = _start.y;
	goal.y = _start.x;
	start.x = _goal.y;
	start.y = _goal.x;

	std::vector<tile> openedList;
	std::vector<tile> closedList;
	std::vector<vec2> localityDirs;
	localityDirs.push_back(vec2(-1, 0));
	localityDirs.push_back(vec2(1, 0));
	localityDirs.push_back(vec2(0, 1));
	localityDirs.push_back(vec2(0, -1));

	tile startTile;
	startTile.g = 0;
	startTile.h = start.squareDistance(goal);
	startTile.coords = start;

	tile startLocalityTile;
	startLocalityTile.g = 1;
	startLocalityTile.parent = start;
	for (int i = 0; i < 4; i++)
	{
		startLocalityTile.coords = start + localityDirs[i];
		if (!inGraph(startLocalityTile.coords)) {
			continue;
		}
		startLocalityTile.countDistance(goal);
		startLocalityTile.countFunction();
		openedList.push_back(startLocalityTile);
	}

	closedList.push_back(startTile);

	while (!openedList.empty())
	{
		tile currentTile = openedList[0];
		int currentTileIndex = 0;
		for (unsigned int i = 1; i < openedList.size(); i++)
			if (openedList[i].f < currentTile.f)
			{
				currentTile = openedList[i];
				currentTileIndex = i;
			}

		openedList.erase(openedList.begin() + currentTileIndex);
		closedList.push_back(currentTile);

		tile localityTile;
		for (int i = 0; i < 4; i++)
		{
			localityTile.coords = currentTile.coords + localityDirs[i];
			localityTile.parent = currentTile.coords;
			localityTile.countDistance(goal);
			localityTile.g = currentTile.g + 1;
			localityTile.countFunction();

			if (!inGraph(localityTile.coords))
				continue;

			if (localityTile.coords == goal)
			{
				closedList.push_back(localityTile);
				openedList.clear();
				break;
			}

			int indexOfTile = findInClosedList(localityTile, closedList);
			if (indexOfTile == -1)
				openedList.push_back(localityTile);
			else
				if (localityTile.g < closedList[indexOfTile].g)
					closedList[indexOfTile] = localityTile;
		}
	}

	std::vector<vec2> path;
	tile pathTile = closedList[closedList.size() - 1];
	vec2 point;
	int indexOfPoint;
	while (point != start)
	{
		point = pathTile.parent;
		indexOfPoint = findInClosedList(point, closedList);
		pathTile = closedList[indexOfPoint];
		path.push_back(point);
	}
	return path;
}

vec2 Graph::findPathStep(vec2 start, vec2 goal)
{
	std::vector<vec2> path = findPath(start, goal);
	return path[0];
}