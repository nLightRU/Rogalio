#include "floor.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
Floor::Floor()
{
	_number = 0;
	GenerateRooms(50);
	SeparateRooms();
	bool flag = MakeNeighborhoodGraph();
	MakeConnections();
	PlaceAll();
	RespawnPlayerAndTrap();
	RespawnMonsters(5);
	InitializeForbiddenTextures();
}

Floor::Floor(int number, int numberOfRooms, int maxWidth, int maxHeight, int maxX, int maxY)
{
	_number = number;
	bool normallyGenerated = false;
	while (!normallyGenerated)
	{
		srand(time(NULL));
		GenerateRooms(numberOfRooms, maxWidth, maxHeight, maxX, maxY);
		SeparateRooms();
		normallyGenerated = MakeNeighborhoodGraph();
		MakeConnections();
	}

	PlaceAll();
	RespawnPlayerAndTrap();
	RespawnMonsters(numberOfRooms / 10);
	InitializeForbiddenTextures();
}

void Floor::GenerateRooms(int numberOfRooms)
{
	srand(time(NULL));

	int w, h, x, y;

	for (int i = 0; i < numberOfRooms; i++)
	{
		x = rand() % (150 - 120 + 1) + 120;
		y = rand() % (150 - 120 + 1) + 120;
		w = rand() % (15 - 3 + 1) + 3;
		h = rand() % (15 - 3 + 1) + 3;

		if (w / h < 1) continue;
		_rooms.push_back(Room(x, y, w, h));
	}
}

void Floor::GenerateRooms(int numberOfRooms, int maxWidth, int maxHeight, int maxX, int maxY)
{
	srand(time(NULL));

	int w, h, x, y;

	for (int i = 0; i < numberOfRooms; i++)
	{
		x = rand() % (maxX - 120 + 1) + 120;
		y = rand() % (maxY - 120 + 1) + 120;
		w = rand() % (maxWidth - 3 + 1) + 3;
		h = rand() % (maxHeight - 3 + 1) + 3;

		if (w / h < 1) continue;
		_rooms.push_back(Room(x, y, w, h));
	}
}

void Floor::SeparateRooms()
{
	int dx, dy, dxa, dxb, dya, dyb;
	bool touching = true;

	int steps = 0;

	while (touching)
	{
		steps++;
		touching = false;
		for (unsigned int a = 0; a < _rooms.size(); a++)
		{
			for (unsigned int b = a + 1; b < _rooms.size(); b++)
				if (_rooms[a].touches(_rooms[b]))
				{
					touching = true;

					dx = fmin(
						abs(_rooms[a].getR() - _rooms[b].getL()) + 2,
						abs(_rooms[a].getL() - _rooms[b].getR()) + 2
					);

					dy = fmin(
						abs(_rooms[a].getB() - _rooms[b].getT()) + 2,
						abs(_rooms[a].getT() - _rooms[b].getB()) + 2
					);

					if (dx < dy) dy = 0;
					else dx = 0;

					if (_rooms[a].getL() < _rooms[b].getL())
						dx *= -1;

					if (_rooms[a].getT() < _rooms[b].getT())
						dy *= -1;

					dxa = dx / 2 + 1;
					dya = dy / 2 + 1;

					dxb = -dx / 2;
					dyb = -dy / 2;

					_rooms[a].shift(dxa, dya);
					_rooms[b].shift(dxb, dyb);
				}
		}
	}
}

void Floor::ChooseHallsAndCorridors()
{
	Room tempRoom;
	for (unsigned int j = 0; j < _rooms.size(); j++)
		for (unsigned int k = 0; k < _rooms.size() - 1 - j; k++)
			if (_rooms[k].getSquare() < _rooms[k + 1].getSquare())
			{
				tempRoom = _rooms[k];
				_rooms[k] = _rooms[k + 1];
				_rooms[k + 1] = tempRoom;
			}
	for (int i = 0; _rooms[0].getSquare() - _rooms[i].getSquare() < 80; i++)
	{
		_halls.push_back(_rooms[i]);
		_halls[i].setParent(i);
		_halls[i].setJoinings(i, i);
		_hallsCount++;
	}

	for (int i = _rooms.size() - 1; i > _hallsCount; i--)
		_corridors.push_back(_rooms[i]);
}

bool Floor::MakeNeighborhoodGraph()
{
	ChooseHallsAndCorridors();

	int distance, tempDistance;
	int joining;

	bool findJoining = false;
	for (int i = 0; i < _hallsCount; i++)
	{
		distance = 99999;
		for (int j = 0; j < _hallsCount; j++)
		{
			tempDistance = _halls[i].getCenter().squareDistance(_halls[j].getCenter());
			if (tempDistance < distance && _halls[j].getParent() != i)
			{
				joining = j;
				findJoining = true;
				distance = tempDistance;
			}
		}

		if (findJoining)
		{
			_halls[i].setRightJoining(joining);
			_halls[joining].setParent(i);
		}
		else return false;

		findJoining = false;
		distance = 99999;
		for (int j = 0; j < _hallsCount; j++)
		{
			tempDistance = _halls[i].getCenter().squareDistance(_halls[j].getCenter());
			if (tempDistance < distance && _halls[j].getParent() != i)
			{
				findJoining = true;
				joining = j;
				distance = tempDistance;
			}
		}
		if (findJoining)
		{
			_halls[i].setLeftJoining(joining);
			_halls[joining].setParent(i);
		}
		else return false;
	}
	return true;
}

void Floor::includeRoomWithPoint(vec2 point)
{
	for (unsigned int i = 0; i < _rooms.size(); i++)
		if (_rooms[i].includePoint(point)) _rooms[i].includeInFloor();
}

bool Floor::isPointInAnyRoom(vec2 point)
{
	for (unsigned int i = 0; i < _rooms.size(); i++)
		if (_rooms[i].includePoint(point)) return true;
	return false;
}

bool Floor::checkPointIsADoor(vec2 point)
{
	for (unsigned int i = 0; i < _halls.size(); i++)
	{
		if (point.x > _rooms[i].getL() && point.x < _rooms[i].getR())
			if (point.y == _rooms[i].getB() || point.y == _rooms[i].getT())
				return true;
		if (point.y > _rooms[i].getT() && point.y < _rooms[i].getB())
			if (point.x == _rooms[i].getR() || point.x == _rooms[i].getL())
				return true;
	}

	for (unsigned int i = 0; i < _corridors.size(); i++)
	{
		if (point.x > _rooms[i].getL() && point.x < _rooms[i].getR())
			if (point.y == _rooms[i].getB() || point.y == _rooms[i].getT())
				return true;
		if (point.y > _rooms[i].getT() && point.y < _rooms[i].getB())
			if (point.x == _rooms[i].getR() || point.x == _rooms[i].getL())
				return true;
	}

	return false;
}

void Floor::toFile(std::string filePath)
{
	std::ofstream map_f(filePath);

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
			map_f << _flat[y][x];
		map_f << std::endl;
	}
}

void Floor::placePoint(vec2 point, char symbol)
{
	_flat[point.y][point.x] = symbol;
}

void Floor::placePoint(int x, int y, char symbol)
{
	_flat[y][x] = symbol;
}

void Floor::MakeConnections()
{
	vec2 point, end;
	vec2 start;
	int indexOfJoining;

	for (unsigned int i = 0; i < _halls.size(); i++)
	{
		start = _halls[i].getCenter();
		point = _halls[i].getCenter();
		indexOfJoining = _halls[i].getLeftJoin();
		end = _halls[indexOfJoining].getCenter();

		while (point.x != end.x)
		{
			if (isPointInAnyRoom(point))
			{
				point.x += point.x < end.x ? 1 : -1;
				includeRoomWithPoint(point);
				continue;
			}
			_ways.push_back(point);
			_connections.push_back(vec2(point.x, point.y + 1));
			_connections.push_back(vec2(point.x, point.y - 1));
			point.x += point.x < end.x ? 1 : -1;
		}

		if (!isPointInAnyRoom(point)) {
			if (start.x > end.x)
				if (start.y > end.y)
				{
					_connections.push_back(vec2(point.x, point.y + 1));
					_connections.push_back(vec2(point.x - 1, point.y + 1));
					_ways.push_back(vec2(point.x, point.y - 1));
				}
				else
				{
					_ways.push_back(vec2(point.x, point.y - 1));
					_ways.push_back(vec2(point.x - 1, point.y - 1));
					_ways.push_back(vec2(point.x, point.y + 1));
				}
			else
				if (start.y > end.y)
				{
					_connections.push_back(vec2(point.x, point.y + 1));
					_connections.push_back(vec2(point.x + 1, point.y + 1));
					_ways.push_back(vec2(point.x, point.y - 1));
				}
				else
				{
					_connections.push_back(vec2(point.x, point.y - 1));
					_connections.push_back(vec2(point.x + 1, point.y - 1));
					_ways.push_back(vec2(point.x, point.y + 1));
				}
		}

		while (point.y != end.y)
		{
			if (isPointInAnyRoom(point))
			{
				point.y += point.y < end.y ? 1 : -1;
				includeRoomWithPoint(point);
				continue;
			}
			_ways.push_back(point);
			_connections.push_back(vec2(point.x + 1, point.y));
			_connections.push_back(vec2(point.x - 1, point.y));
			point.y += point.y < end.y ? 1 : -1;
		}

		point = _halls[i].getCenter();
		indexOfJoining = _halls[i].getRightJoin();
		end = _halls[indexOfJoining].getCenter();

		while (point.x != end.x)
		{
			if (isPointInAnyRoom(point))
			{
				point.x += point.x < end.x ? 1 : -1;
				includeRoomWithPoint(point);
				continue;
			}
			_ways.push_back(point);
			_connections.push_back(vec2(point.x, point.y + 1));
			_connections.push_back(vec2(point.x, point.y - 1));
			point.x += point.x < end.x ? 1 : -1;
		}

		if (!isPointInAnyRoom(point)) {
			if (start.x > end.x)
				if (start.y > end.y)
				{
					_connections.push_back(vec2(point.x, point.y + 1));
					_connections.push_back(vec2(point.x - 1, point.y + 1));
					_ways.push_back(vec2(point.x, point.y - 1));
				}
				else
				{
					_ways.push_back(vec2(point.x, point.y - 1));
					_ways.push_back(vec2(point.x - 1, point.y - 1));
					_ways.push_back(vec2(point.x, point.y + 1));
				}
			else
				if (start.y > end.y)
				{
					_connections.push_back(vec2(point.x, point.y + 1));
					_connections.push_back(vec2(point.x + 1, point.y + 1));
					_ways.push_back(vec2(point.x, point.y - 1));
				}
				else
				{
					_connections.push_back(vec2(point.x, point.y - 1));
					_connections.push_back(vec2(point.x + 1, point.y - 1));
					_ways.push_back(vec2(point.x, point.y + 1));
				}
		}

		while (point.y != end.y)
		{
			if (isPointInAnyRoom(point))
			{
				point.y += point.y < end.y ? 1 : -1;
				includeRoomWithPoint(point);
				continue;
			}
			_ways.push_back(point);
			_connections.push_back(vec2(point.x + 1, point.y));
			_connections.push_back(vec2(point.x + 1, point.y));
			point.y += point.y < end.y ? 1 : -1;
		}
	}
	int count = 0;
	for (unsigned int i = 0; i < _rooms.size(); i++)
	{
		if (_rooms[i].isInclude())
			count++;
	}
}

void Floor::PlaceConnections()
{
	for (unsigned int i = 0; i < _connections.size(); i++)
		placePoint(_connections[i], '#');
	for (unsigned int i = 0; i < _ways.size(); i++)
		placePoint(_ways[i], ' ');
}

void Floor::PlaceRooms()
{
	for (unsigned int i = 0; i < _rooms.size(); i++)
	{
		if (_rooms[i].isInclude())
		{
			for (int x = 0; x <= _rooms[i].getW(); x++)
			{
				placePoint(_rooms[i].getX() + x, _rooms[i].getY(), '#');
				placePoint(_rooms[i].getX() + x, _rooms[i].getY() + _rooms[i].getH(), '#');
			}
			for (int y = 0; y <= _rooms[i].getH(); y++)
			{
				placePoint(_rooms[i].getX(), _rooms[i].getY() + y, '#');
				placePoint(_rooms[i].getX() + _rooms[i].getW(), _rooms[i].getY() + y, '#');
			}
		}
	}
}

void Floor::PlaceAll()
{
	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_flat[y][x] = ' ';

	PlaceRooms();
	PlaceConnections();
}

vec2 Floor::createRandomPointInHall()
{
	int hallNumber;
	hallNumber = rand() % _hallsCount;
	return _halls[hallNumber].createRandomPoint();
}

std::vector<vec2> Floor::collectPoints()
{
	std::vector<vec2> points;

	for (unsigned int i = 0; i < _rooms.size() - 1; i++)
		if (_rooms[i].isInclude())
			for (int y = _rooms[i].getT() + 1; y < _rooms[i].getB(); y++)
				for (int x = _rooms[i].getL() + 1; x < _rooms[i].getR(); x++)
					points.push_back(vec2(x, y));

	for (unsigned int i = 0; i < _ways.size(); i++)
		points.push_back(_ways[i]);

	return points;
}

void Floor::RespawnMonsters(int monstersNumber)
{
	srand(time(NULL));

	MonsterInfo info;
	std::vector<MonsterInfo> listOfMonsters = info.createAllMonsters();

	for (unsigned int i = 0; i < monstersNumber; i++)
	{
		int pointIndex = rand() % collectPoints().size();
		vec2 position = collectPoints()[pointIndex];
		int	infoIndex = rand() % listOfMonsters.size();
		_monsters.push_back(Monster(listOfMonsters[infoIndex], position));
	}
}

void Floor::RespawnPlayerAndTrap()
{
	_playerPosition = _halls[0].createRandomPoint();
	int index = rand() % _hallsCount;
	_trapPosition = _halls[index].createRandomPoint();
}

void Floor::InitializeForbiddenTextures()
{
	_forbiddenTextures.push_back('#');
	_forbiddenTextures.push_back('@');
	_forbiddenTextures.push_back('o');
	_forbiddenTextures.push_back('s');
	_forbiddenTextures.push_back('S');
	_forbiddenTextures.push_back('3');
	_forbiddenTextures.push_back('7');
	_forbiddenTextures.push_back('g');
	_forbiddenTextures.push_back('G');
	_forbiddenTextures.push_back('p');
	_forbiddenTextures.push_back('0');
	_forbiddenTextures.push_back('r');
	_forbiddenTextures.push_back('8');



	bool flag;
	int index;

	for (unsigned int i = 0; i < _monsters.size(); i++)
	{
		flag = false;
		for (unsigned int j = 0; j < _forbiddenTextures.size(); j++)
			if (_forbiddenTextures[j] == _monsters[i].getTexture())
				flag = true;

		if (!flag) _forbiddenTextures.push_back(_monsters[i].getTexture());
	}
}

