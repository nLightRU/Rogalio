#pragma once
#include "room.h"
#include "../units/monster.h"
#include <vector>
#include <string>
class Floor 
{
private:
	std::vector<Room> _rooms;
	std::vector<vec2> _greatWall;

	// chosen rooms for spawn anything
	// and others
	std::vector<Room> _corridors;
	std::vector<Room> _halls;

	// different points for corridors between rooms
	std::vector<vec2> _connections;
	std::vector<vec2> _ways;
	std::vector<vec2> _corners;

	// different mobs 
	std::vector<Monster> _monsters;
	vec2 _playersPosition;

	int _number;
	int _hallsCount = 0;

	const int _height = 300, _width = 300;

	char _flat[300][300];
	
	// methods for generating floor
	void GenerateRooms(int numberOfRooms);
	void SeparateRooms();
	void MakeGraph();
	void MakeConnections();
	void ChooseHallsAndCorridors();
	void AddLoot();
	void AddEnemies();

	// methods for placing floor in the flat
	void PlaceRooms();
	void PlaceConnections();
	void RespawnPlayer();
	void PlaceMonsters();
	void PlaceAll();
	void toFile(std::string FilePath);
	
	// ad hoc for broken corridors 
	void MakeGreatWall();

	// additional methods for generating floor
	void includeRoomWithPoint(vec2 point);
	bool checkPointIsADoor(vec2 point);
	bool isPointInAnyRoom(vec2 point);
	void placePoint(vec2 point, char symbol);
	void placePoint(int x, int y, char symbol);
public:
	Floor();
	Floor(int number, int numberOfRooms);
	Floor(int numberOfRooms, std::string filePath);

	char getFlatTile(int i, int j) { return _flat[i][j]; }
	std::vector<Room> getRooms() { return _rooms; }
	Room getRoom(int i) { return _rooms[i]; }

	int getNumber() { return _number; }
	int getNumberOfHalls() { return _hallsCount; }
	int getNumberOfRooms() { return _rooms.size(); }

	int getW() { return _width; }
	int getH() { return _height; }

	std::vector<Monster> getMonsters() { return _monsters; }
	vec2 getPlayersPosition() { return _playersPosition; }

	void movePlayer(vec2 position);
};