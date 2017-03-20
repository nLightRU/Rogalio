#pragma once
#include "room.h"
#include "../units/monster.h"
#include "../math/graph.h"
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

	// vectors for content
	std::vector<Monster> _monsters;
	std::vector<char> _forbiddenTextures;
	vec2 _playerPosition;
	vec2 _trapPosition;

	int _number;
	int _hallsCount = 0;

	const int _height = 300, _width = 300;

	char _flat[300][300];

	// funtions for generating floor
	void GenerateRooms(int numberOfRooms);
	void GenerateRooms(int numberOfRooms, int maxWidth, int maxHeight, int maxX, int maxY);
	void SeparateRooms();
	bool MakeNeighborhoodGraph();
	void MakeConnections();
	void ChooseHallsAndCorridors();

	// functions for generating content
	void RespawnPlayerAndTrap();
	void RespawnMonsters(int monstersNumber);
	void InitializeForbiddenTextures();

	// funtions for placing floor in the flat
	void PlaceRooms();
	void PlaceConnections();
	void PlaceAll();

	// additional funtions for generating floor
	void includeRoomWithPoint(vec2 point);
	bool checkPointIsADoor(vec2 point);
	void placePoint(vec2 point, char symbol);
	void placePoint(int x, int y, char symbol);
public:
	Floor();
	Floor(int number, int numberOfRooms, int maxWidth, int maxHeight, int maxX, int maxY);

	char getFlatTile(int i, int j) { return _flat[i][j]; }
	char getFlatTile(vec2 position) { return _flat[position.y][position.x]; }

	int getNumber() { return _number; }

	int getNumberOfHalls() { return _halls.size(); }
	std::vector<Room> getHalls() { return _halls; }
	std::vector<Room> getRooms() { return _rooms; }
	int getNumberOfRooms() { return _rooms.size(); }

	vec2 createRandomPointInHall();
	bool isPointInAnyRoom(vec2 point);
	std::vector<vec2> collectPoints();
	
	std::vector<Monster> getMonsters() { return _monsters; }
	std::vector<char> getForbiddenTextures() { return _forbiddenTextures; }
	vec2 getPlayerPosition() { return _playerPosition; }
	vec2 getTrapPosition() { return _trapPosition; }

	void toFile(std::string FilePath);

	int getW() { return _width; }
	int getH() { return _height; }


};