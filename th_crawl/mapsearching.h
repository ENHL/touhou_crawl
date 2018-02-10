//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mapsearching.h
//
// ����: �� ��Ī �˰���
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <string>
#include <list>
#include <queue>
#include <map>

using namespace std;

class MapNode //���� �̾����� �� ��� Ž��
{
	list<MapNode*> state_map; //�̾����� �� ����
	int map_id;
	int max_level;
	int unique_id;
	string name;
	map<int, int> floor_map;

public:
	MapNode(const char* name, int map_id_, int max_level_);

	void addNode(MapNode* node, int floor);
	void addStair(MapNode* node, int floor);

	static void initMapNode();
	static MapNode* getFirstNode();
	static MapNode* getNode(int level_);
	static void testLoopAllNode();
	static bool searchRoad(int start_level, int goal_level, queue<list<coord_def>>* stairMap);

	int getMapId() { return map_id; };
	int getUniqueId() { return unique_id; };
	string getName() { return name; };
	bool isCurrentFloor(int level);
	int getFloorStair(int dungeon);
	bool getFloorStairToStack(queue<list<coord_def>> *stairMap, int dungeon);

	list<MapNode*>* getMap() { return &state_map; };
};


