#pragma once
#include "room.h"
#include <vector>
#include <string>

class Floor 
{
private:
	std::vector<Room> _rooms;

	std::vector<Room> _corridors;
	std::vector<Room> _halls;

	std::vector<vec2> _connections;
	std::vector<vec2> _ways;
	std::vector<vec2> _corners;

	int _number;
	int _hallsCount = 0;

	const int _height = 100, _width = 175;

	char _flat[100][175];
	
	void GenerateRooms(int numberOfRooms);
	void SeparateRooms();
	void MakeGraph();
	void MakeConnections();
	void ChooseHallsAndCorridors();
	void AddLoot();
	void AddEnemies();

	void PlaceRooms();
	void PlaceConnections();
	void PlaceAll();
	void toFile(std::string FilePath);

	void includeRoomWithPoint(vec2 point);
	bool checkPointIsADoor(vec2 point);
	bool isPointInAnyRoom(vec2 point);
	void placePoint(vec2 point, char symbol);
	void placePoint(int x, int y, char symbol);

	char getFlatTile(int i, int j) { return _flat[i][j]; }
	Room getRoom(int i) { return _rooms[i]; }
	int getW() { return _width; }
	int getH() { return _height; }
public: 
	Floor();
	Floor(int number, int numberOfRooms);
	Floor(int numberOfRooms, std::string filePath);

	int getNumber() { return _number; }
	int getNumberOfHalls() { return _hallsCount; }
};