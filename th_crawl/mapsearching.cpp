//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mapsearching.cpp
//
// ����: �� ��Ī �˰���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "const.h"
#include "display.h"
#include "common.h"
#include "mapsearching.h"
#include "map.h"

int seqence = 0;



/*
���Ϲݴ���
�Ӥ��Ȱ���ȣ��
�ӤӤ�ȫ����
�ӤӤӤ�������
�ӤӤӤ����Ͻ�
�ӤӤ��䱫�ǻ�
�Ӥӡ���������
�Ӥ��̱����׸�
�ӡ���������
���±�
�����Ǽ���
������
������
�������̽Ż�
*/

MapNode mapNode_normal("�Ϲݴ���", 0, MAX_DUNGEUN_LEVEL);
MapNode mapNode_temple("����", TEMPLE_LEVEL, 1);
MapNode mapNode_misty("�Ȱ���ȣ��", MISTY_LAKE_LEVEL, MAX_MISTY_LAKE_LEVEL);
MapNode mapNode_scarlet("ȫ����", SCARLET_LEVEL, MAX_SCARLET_LEVEL);
MapNode mapNode_library("������", SCARLET_LIBRARY_LEVEL, MAX_SCARLET_LIBRARY_LEVEL);
MapNode mapNode_flan("���Ͻ�", SCARLET_UNDER_LEVEL, MAX_SCARLET_UNDER_LEVEL);
MapNode mapNode_moun("�䱫�ǻ�", YOUKAI_MOUNTAIN_LEVEL, MAX_YOUKAI_MOUNTAIN_LEVEL);
MapNode mapNode_yukku("������", YUKKURI_LEVEL, MAX_YUKKURI_LEVEL);
MapNode mapNode_bamboo("�̱����׸�", BAMBOO_LEVEL, MAX_BAMBOO_LEVEL);
MapNode mapNode_eien("������", EIENTEI_LEVEL, MAX_EIENTEI_LEVEL);
MapNode mapNode_depth("���±�", DEPTH_LEVEL, MAX_DEPTH_LEVEL);
MapNode mapNode_dream("���Ǽ���", DREAM_LEVEL, MAX_DREAM_LEVEL);
MapNode mapNode_moon("���Ǽ���", MOON_LEVEL, MAX_MOON_LEVEL);
MapNode mapNode_pande("����", PANDEMONIUM_LEVEL, MAX_PANDEMONIUM_LEVEL);
MapNode mapNode_hell("����", SUBTERRANEAN_LEVEL, MAX_SUBTERRANEAN_LEVEL);
MapNode mapNode_haku("�����̽Ż�", HAKUREI_LEVEL, MAX_HAKUREI_LEVEL);
MapNode mapNode_zigurrat("���Ǽ��� �糪ƽ", ZIGURRAT_LEVEL, 1);


MapNode::MapNode(const char* name_, int map_id_, int max_level_):
name(name_), map_id(map_id_), max_level(max_level_)
{
	unique_id = ++seqence;
}


void MapNode::addNode(MapNode* node, int floor)
{
	floor_map.insert(pair<int, int>(node->getMapId(), floor));
	state_map.push_back(node);
}

void MapNode::addStair(MapNode* node, int floor)
{
	floor_map.insert(pair<int, int>(node->getMapId(), floor));
	//state_map.push_back(node);
}



void MapNode::initMapNode()
{
	mapNode_normal.addNode(&mapNode_temple, TEMPLE);
	mapNode_normal.addNode(&mapNode_misty, MISTY_LAKE);
	mapNode_normal.addNode(&mapNode_bamboo, BAMBOO);
	mapNode_normal.addNode(&mapNode_depth, DEPTH);
	mapNode_normal.addStair(&mapNode_eien, BAMBOO); //�ǵ��ƿ��� ���

	mapNode_temple.addNode(&mapNode_normal, -1); //���ƿ�

	mapNode_misty.addNode(&mapNode_normal, -1); //���ƿ�
	mapNode_misty.addNode(&mapNode_scarlet, SCARLET_M);
	mapNode_misty.addNode(&mapNode_moun, YOUKAI_MOUNTAIN);

	mapNode_scarlet.addNode(&mapNode_misty, -1); //���ƿ�
	mapNode_scarlet.addNode(&mapNode_library, SCARLET_L);
	mapNode_scarlet.addNode(&mapNode_flan, SCARLET_U);

	mapNode_library.addNode(&mapNode_scarlet, -1); //���ƿ�

	mapNode_flan.addNode(&mapNode_scarlet, -1); //���ƿ�

	mapNode_moun.addNode(&mapNode_misty, -1); //���ƿ�
	mapNode_moun.addNode(&mapNode_yukku, YUKKURI_D);

	mapNode_yukku.addNode(&mapNode_moun, -1); //���ƿ�

	//mapNode_bamboo.addNode(&mapNode_normal);
	mapNode_bamboo.addStair(&mapNode_normal, -1);//�Ϲ浿��

	mapNode_eien.addNode(&mapNode_normal, -1); //���ƿ�

	mapNode_depth.addNode(&mapNode_normal, -1); //���ƿ�
	mapNode_depth.addNode(&mapNode_dream, DREAM_D);
	mapNode_depth.addNode(&mapNode_pande, PANDEMONIUM);
	mapNode_depth.addNode(&mapNode_hell, SUBTERRANEAN);
	mapNode_depth.addNode(&mapNode_haku, HAKUREI_D);
	mapNode_depth.addNode(&mapNode_zigurrat, ZIGURRAT);
	mapNode_normal.addStair(&mapNode_moon, DREAM_D); //�ǵ��ƿ��� ���

	//mapNode_dream.addNode(&mapNode_normal);
	mapNode_dream.addStair(&mapNode_depth, -1);//�Ϲ浿��

	mapNode_moon.addNode(&mapNode_depth, -1); //���ƿ�

	//mapNode_pande.addNode(&mapNode_depth);
	mapNode_pande.addStair(&mapNode_depth, -1);//�Ϲ浿��


	mapNode_hell.addNode(&mapNode_depth, -1); //���ƿ�

	mapNode_haku.addNode(&mapNode_depth, -1); //���ƿ�

	mapNode_zigurrat.addNode(&mapNode_depth, -1); //���ƿ�
	
}


MapNode* MapNode::getFirstNode()
{
	return &mapNode_normal;
}


MapNode* MapNode::getNode(int level_)
{
	if (level_ < TEMPLE_LEVEL)
		return &mapNode_normal;
	else if (level_ == TEMPLE_LEVEL)
		return &mapNode_temple;
	else if (level_ >= MISTY_LAKE_LEVEL && level_ <= MISTY_LAKE_LEVEL + MAX_MISTY_LAKE_LEVEL)
		return &mapNode_misty;
	else if (level_ >= YOUKAI_MOUNTAIN_LEVEL && level_ <= YOUKAI_MOUNTAIN_LEVEL + MAX_YOUKAI_MOUNTAIN_LEVEL)
		return &mapNode_moun;
	else if (level_ >= SCARLET_LEVEL && level_ <= SCARLET_LEVEL + MAX_SCARLET_LEVEL)
		return &mapNode_scarlet;
	else if (level_ >= SCARLET_LIBRARY_LEVEL && level_ <= SCARLET_LIBRARY_LEVEL + MAX_SCARLET_LIBRARY_LEVEL)
		return &mapNode_library;
	else if (level_ >= SCARLET_UNDER_LEVEL && level_ <= SCARLET_UNDER_LEVEL + MAX_SCARLET_UNDER_LEVEL)
		return &mapNode_flan;
	else if (level_ >= BAMBOO_LEVEL && level_ <= BAMBOO_LEVEL + MAX_BAMBOO_LEVEL)
		return &mapNode_bamboo;
	else if (level_ >= EIENTEI_LEVEL && level_ <= EIENTEI_LEVEL + MAX_EIENTEI_LEVEL)
		return &mapNode_eien;
	else if (level_ >= SUBTERRANEAN_LEVEL && level_ <= SUBTERRANEAN_LEVEL + MAX_SUBTERRANEAN_LEVEL)
		return &mapNode_hell;
	else if (level_ >= YUKKURI_LEVEL && level_ <= YUKKURI_LAST_LEVEL)
		return &mapNode_yukku;
	else if (level_ >= DEPTH_LEVEL && level_ <= DEPTH_LAST_LEVEL)
		return &mapNode_depth;
	else if (level_ >= DREAM_LEVEL && level_ <= DREAM_LAST_LEVEL)
		return &mapNode_dream;
	else if (level_ >= MOON_LEVEL && level_ <= MOON_LAST_LEVEL)
		return &mapNode_moon;
	else if (level_ >= PANDEMONIUM_LEVEL && level_ <= PANDEMONIUM_LEVEL + 3)
		return &mapNode_pande;
	else if (level_ >= HAKUREI_LEVEL && level_ <= HAKUREI_LAST_LEVEL)
		return &mapNode_haku;
	else if (level_ == ZIGURRAT_LEVEL)
		return &mapNode_zigurrat;
	else
		return NULL;
}

bool MapNode::isCurrentFloor(int level)
{
	return (level >= map_id) && (level <= map_id + max_level);
}



int MapNode::getFloorStair(int dungeon)
{
	map<int, int>::iterator floor_ = floor_map.find(dungeon);
	if (floor_ == floor_map.end()) {
		return -1;
	}

	if ((*floor_).second == -1)
	{
		return map_id;
	}
	return map_list.dungeon_enter[(*floor_).second].floor;
}

bool SetStairToStack(queue<list<coord_def>> *stairMap, int start_level, bool up) {
	list<coord_def> new_stair;
	if (up)
	{
		for (int i = 0; i < 3; i++)
		{
			if ((env[start_level].isExplore(env[start_level].stair_up[i].x, env[start_level].stair_up[i].y) ||
				env[start_level].isMapping(env[start_level].stair_up[i].x, env[start_level].stair_up[i].y))
				&& env[start_level].isStair(env[start_level].stair_up[i].x, env[start_level].stair_up[i].y))
			{
				new_stair.push_back(env[start_level].stair_up[i]);
			}
		}
	}
	else //down
	{
		if (!environment::isLastFloor(start_level))
		{
			for (int i = 0; i < 3; i++)
			{
				if ((env[start_level].isExplore(env[start_level].stair_down[i].x, env[start_level].stair_down[i].y) ||
					env[start_level].isMapping(env[start_level].stair_down[i].x, env[start_level].stair_down[i].y))
					&& env[start_level].isStair(env[start_level].stair_down[i].x, env[start_level].stair_down[i].y))
				{
					new_stair.push_back(env[start_level].stair_down[i]);
				}
			}
		}
	}
	if (new_stair.empty())
		return false;
	stairMap->push(new_stair);
	return true;
}


bool MapNode::getFloorStairToStack(queue<list<coord_def>> *stairMap, int dungeon)
{
	list<coord_def> new_stair;
	map<int, int>::iterator floor_ = floor_map.find(dungeon);
	if (floor_ == floor_map.end()) {
		return false;
	}

	if ((*floor_).second == -1)
	{
		return SetStairToStack(stairMap, map_id, true);
	}

	coord_def stair_ = map_list.dungeon_enter[(*floor_).second].pos;

	if ((env[map_list.dungeon_enter[(*floor_).second].floor].isExplore(stair_.x, stair_.y) ||
		env[map_list.dungeon_enter[(*floor_).second].floor].isMapping(stair_.x, stair_.y))
		&& env[map_list.dungeon_enter[(*floor_).second].floor].isStair(stair_.x, stair_.y))
	{
		new_stair.push_back(stair_);
		stairMap->push(new_stair);
		return true;
	}
	else
		return false;


}

void testLoopAndPrint(MapNode* node, int prev, int depth)
{
	//char temp[100];
	//sprintf_s(temp, 100, "�׽�Ʈ) %d��° - %s", node->getUniqueId(), node->getName().c_str());
	//for (int i = 0; i<depth; i++)
	//	printlog("��", false, false, false, CL_help);
	//printlog(temp, true, false, false, CL_help);


	auto *list = node->getMap();
	auto it = list->begin();
	for (; it != node->getMap()->end(); it++)
	{
		if (prev != (*it)->getUniqueId())
		{
			testLoopAndPrint((*it), node->getUniqueId(), depth + 1);
		}
	}

}
void MapNode::testLoopAllNode()
{
	enterlog();
	testLoopAndPrint(getFirstNode(), -1, 0);
}



bool getShortCut(stack<MapNode*>* stack_, MapNode* node, MapNode* goal, int prev, int depth)
{
	auto *list = node->getMap();
	auto it = list->begin();
	for (; it != node->getMap()->end(); it++)
	{
		if (prev != (*it)->getUniqueId())
		{
			if ((*it) == goal) {
				//char temp[100];
				//sprintf_s(temp, 100, "����) %s", (*it)->getName().c_str());
				//printlog(temp, true, false, false, CL_help);
				stack_->push((*it));
				return true;
			}


			if (getShortCut(stack_, (*it), goal, node->getUniqueId(), depth + 1))
			{
				//char temp[100];
				//sprintf_s(temp, 100, "������) %s" , (*it)->getName().c_str());
				//printlog(temp, true, false, false, CL_help);
				stack_->push((*it));
				return true;
			}
		}
	}
	return false;
}






bool MapNode::searchRoad(int start_level, int goal_level, queue<list<coord_def>>* stairMap)
{
	MapNode* start = getNode(start_level);
	MapNode* goal = getNode(goal_level);
	stack<MapNode*> stackMap;
	
	enterlog();
	if (start == NULL || goal == NULL)
	{
		printlog("�� �� ���� ��ġ.", false, false, false, CL_help);
		return false;
	}

	bool return_ = getShortCut(&stackMap, start, goal, -1, 0);
	stackMap.push(start);

	if(return_)
	{
		enterlog();
		while (!stackMap.empty()) {
			MapNode* current_dungeon = stackMap.top();
			stackMap.pop();
			if (stackMap.empty())
			{
				//char temp[100];
				//sprintf_s(temp, 100, "[����]%d", start_level);
				//printlog(temp, false, false, false, CL_magic);
				break;
			}
			MapNode* next_dungeon = stackMap.top();


			while (current_dungeon->isCurrentFloor(start_level))
			{
				//char temp[100];
				//sprintf_s(temp, 100, "%d-", start_level);
				//printlog(temp, false, false, false, CL_magic);

				int stair_level = current_dungeon->getFloorStair(next_dungeon->getMapId());
				if (stair_level == start_level) 
				{
					int next_floor = next_dungeon->getFloorStair(current_dungeon->getMapId());
					if (next_floor == -1) {
						printlog("���� ���� �� �� �����ϴ�.", true, false, false, CL_help);
						return false;
					}

					if (!current_dungeon->getFloorStairToStack(stairMap, next_dungeon->getMapId())) {
						printlog("���� ���� �� �� �����ϴ�.", false, false, false, CL_help);
						return false;
					}

					
					start_level = next_floor;
					break;
				}
				else if (stair_level > start_level)
				{
					if (!SetStairToStack(stairMap, start_level, false))
					{
						printlog("���� ���� �� �� �����ϴ�.", false, false, false, CL_help);
						return false;
					}
					start_level++;
				}
				else
				{
					if(!SetStairToStack(stairMap, start_level, true))
					{
						printlog("���� ���� �� �� �����ϴ�.", false, false, false, CL_help);
						return false;
					}
					start_level--;
				}
			}
			//char temp[100];
			//sprintf_s(temp, 100, "(>)");
			//printlog(temp, false, false, false, CL_magic);
		}
	}





	if(return_)
	{
		//printlog("��ġ�� ���������� ã�ҽ��ϴ�.", false, false, false, CL_help);
		return true;
	}
	else
	{
		printlog("�� ������ ���� ���� �� �� �����ϴ�.", false, false, false, CL_help);
		return false;
	}
}
