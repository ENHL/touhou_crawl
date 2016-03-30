//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: create_mon.cpp
//
// ����: �ʿ� �´� ���ͱ׷��� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_infor.h"
#include "environment.h"
#include "event.h"


void create_id_to_mon(int id, int level);
int get_unique_to_id(int m_id);
void create_id_to_unique(int id, int level);
vector<unique_infor> unique_list;

struct mon_group
{
	int id; //������ȣ <- ������ȣ
	int min_level; //�ּҷ��� <- ������ ���� ��
	int max_level; //�ִ뷹�� <- ������ ���� ��
	int percent; //Ȯ��  <- ���� �󵵸� �����Ѵ�.
	int strong; //������ ���̵�  (10�� �⺻) <- ���� ���̳� ���� ���� �ʹ� ���� �������� ����

};
mon_group normal_group[] = //�Ϲݸ� �׷�
{
	{  0,  0,  4,  30,  1}, //��� 1
	{  1,  0,  4,  30,  1}, //�� 1
	{  2,  0,  3,  15,  2}, //���̹����� 1
	{  3,  0,  2,  30,  1}, //�ʷϿ��� 1
	//{  4,  0,  4,  20,  3}, //��� 3
	{  5,  0,  2,  2,  3}, //�������� 1
	{  6,  0,  1,  10,  3}, //�Ķ����� 1
	{  7,  0,  2,  10,  2}, //�ʷϿ��� 2~3
	{ 23,  0,  5,  5,  3}, //�ݵ�����

	{  8,  1,  4,  20,  3}, //�Ź� 1
	{  9,  1,  5,  15,  5}, //�� 1
	{ 11,  1,  4,  10,  3}, //�ʷϿ���1 �Ķ�����1
	{ 12,  1,  5,  10,  3}, //�ʷϿ���1 ��������1
	//{ 13,  1,  5,  40,  3}, //���2 ���4
	{ 14,  1,  3,  8,  5}, //ı��2~3
	{ 24,  1,  4,  5,  5}, //�ΰ��δ�(����)
	{ 27,  1,  14,  8,  5}, //���䱫
	{ 28,  1,  5,  5,  5}, //�ʷϸ��
	
	{ 10,  2,  14,  3,  6}, //�η�� 1
	{ 15,  2,  9,  20,  5}, //�ʷϿ���2 �Ķ�����1 ��������1
	{ 18,  2,  6,  25,  6}, //ı��4~5
	{ 4,   2,  7,  10 , 3}, //���3
	{ 20,  2,  9,  10,  7}, //�Ź�1 ��1
	{ 10,  2,  11,  10,  6}, //�η�� 1
	{ 24,  2,  4,  5,  5}, //�ΰ��δ�(����)
	{ 29,  2,  7,  5,  5}, //��Ȳ���
	{ 28,  2,  5,  10,  5}, //�ʷϸ��


	{ 16,  3,  9,  10,  6}, //�Ķ�����2 ��������2
	{ 25,  3,  6,  7, 10}, //�ΰ��δ�(�߰�)
	{ 30,  3,  9,  5,  5}, //ȸ�����

	
	{ 21,  4,  11,  10,  8}, //���� ������ ȣ���δ�
	{ 25,  4,  6,  20, 10}, //�ΰ��δ�(�߰�)
	{ 29,  4,  7,  10,  5}, //��Ȳ���


	{ 22,  5,  12,  10, 13}, //��� ���� ȣ���δ�
	{ 35,  5,  14,  5, 10}, //����������
	{ 30,  5,  9,  10,  5}, //ȸ�����

	
	{ 32,  6,  14,  15, 10}, //�����
	
	{ 31,  7,  14,  20, 10}, //������
	{ 26,  7,  14,  30, 20}, //�ΰ��δ�(����)
	{ 33,  7,  14,  15, 15}, //����ٱ�
	{ 38,  7,  14,  8, 10}, //�߸�����


	{ 34,  9,  14,  5, 30}, //����
	{ 39,  9,  14,  5, 15}, //ı��â���δ�
	{ 36,  9,  14,  5, 10}, //Ű���̸���

	{ 37,  10,  14,  5, 30}, //���и��� ����
	{ 43,  10,  14,  5, 30}, //�ƿ�����

	{ 34,  11,  14,  10, 30}, //����
	{ 42,  11,  14,  10, 30}, //�ٱ��δ�
	
	//YOUKAI_MOUNTAIN_LEVEL

	
	
	{ 15,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  10,  5}, //�ʷϿ���2 �Ķ�����1 ��������1
	{ 21,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  10,  8}, //���� ������ ȣ���δ�
	{ 22,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  10, 13}, //��� ���� ȣ���δ�
	{  3,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+1,  1,  1}, //�ʷϿ��� 1
	{  5,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+1,  1,  3}, //�������� 1
	{  6,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  3}, //�Ķ����� 1
	{  7,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  2}, //�ʷϿ��� 2~3
	{  0,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  1}, //��� 1
	{ 29,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  2,  5}, //��Ȳ���
	{ 28,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  2,  5}, //�ʷϸ��
	{ 30,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  2,  5}, //ȸ�����
	
	{ 21,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  5,  8}, //���� ������ ȣ���δ�
	{ 22,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  8, 13}, //��� ���� ȣ���δ�
	{ 14,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  2,  5}, //ı��2~3
	{ 17,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4, 1,  5}, //ı��â��
	{ 31,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  5, 10}, //������
		
	{ 22,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4, 5, 13}, //��� ���� ȣ���δ�
	
	{ 63,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4, 5, 13}, //ū�β���

	//YOUKAI_MOUNTAIN_LEVEL

	{ 18,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+2, 15,  6}, //ı��4~5
	{ 17,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+1, 10,  5}, //ı��â��
	{ 19,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+1,  7, 10}, //ı��1~3 ı�ļ�����
	{ 33,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 15}, //����ٱ�
	{ 39,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+2,  2, 15}, //ı��â���δ�
	{ 36,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+3,  1, 10}, //Ű���̸���

	{ 17,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+2,  5, 10}, //ı��â�� 
	{ 33,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 15}, //����ٱ�
	{ 39,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //ı��â���δ�
	{ 44,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //ı�� â ���� ����Ʈ�δ�
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  1, 25}, //�߸��ͷ� �δ�


	{ 33,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //����ٱ�
	{ 39,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //ı��â���δ�
	{ 44,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //ı�� â ���� ����Ʈ�δ�
	{ 40,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //�߸��ν��ٱ�
	{ 41,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //�ϳ�Ÿī�ٱ�
	{ 36,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 10}, //Ű���̸���
	{ 42,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  10, 30}, //�ٱ��δ�
	//{ 45,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+4,  10, 30}, //����ٱ�
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3, 2, 25}, //�߸��ͷ� �δ�

	 
	{ 40,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //�߸��ν��ٱ�
	{ 41,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //�ϳ�Ÿī�ٱ�
	{ 61,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  2, 30}, //������������
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 25}, //�߸��ͷ� �δ�


	
	//SCARLET_LEVEL
	{ 51,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 15,  6}, //���̵����3~4
	{ 48,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 15,  16}, //ȩ��� �Һδ� 
	{ 49,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� ���̵�2��
	{ 50,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 1,  16}, //ȩ��� ����
	
	{ 48,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� �Һδ� 
	{ 50,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 3,  16}, //ȩ��� ����
	{ 47,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 3,  20}, //����å
	{ 52,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 1,  10}, //����ī���
	{ 60,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 1,  20}, //��������
	
	{ 48,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� �Һδ� 
	{ 49,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� ���̵�2��
	{ 50,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� ����
	{ 47,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  20}, //����å
	{ 37,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 3,  30}, //���и��� ����
	
	{ 52,  SCARLET_LEVEL+3,  SCARLET_LEVEL+3, 5,  30}, //����ī���
	
	{ 47,  SCARLET_LIBRARY_LEVEL,  SCARLET_LIBRARY_LEVEL, 5,  20}, //�������� ����å
	

	{ -1,  0,  0,  0,  0} //�迭�� ��
};


mon_group unigue_group[] = //���ӵ�� �׷� Ȯ���� 100�� �ְ�
{
	{  0,  1,  3,  40,  1}, //��̾�
	{  1,  2,  4,  40,  1}, //����
	{  2,  4,  6,  40,  2}, //�̽�Ƽ��
	{  3,  7,  10,  40,  3}, //ġ����
	{  4,  8,  12,  10,  3}, //�޵�
	{  5,  5,  8,  40,  2}, //�����
	{  6,  1,  3,  40,  1}, //Ű����
	{  7,  6,  9,  40,  3}, //þ
	{  8,  3,  5,  40,  2}, //�ڰ���
	{  9,  2,  4,  40,  2}, //�����
	{  10, 2,  4,  40,  2}, //����
	{  11,  1,  6,  5,  2}, //���׹�Ʈ
	{  12,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  60,  4}, //�����
	{  22,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3, 20,  3}, //�����
	{  16,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  20,  3}, //���
	//{  13,  YOUKAI_MOUNTAIN_LEVEL+4,  YOUKAI_MOUNTAIN_LEVEL+4,  100,  5}, //�ƾ�(����������� ��Ʈ�� ����. ��Ʈ ������ �ٽ� �߰�)
	{  21,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  10,  3}, //�ĸ���
	{  19,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+2,  30,  3}, //���丮
	
	{  15,  9,  13,  10,  3}, //�߸���
	{  16,  7,  10,  10,  3}, //���
	{  17,  9,  13,  10,  3}, //���ī
	{  18,  9,  13,  20,  3}, //��Ű��Ű
	{  20,  9,  13,  10,  3}, //ī�Է�
	{  21,  9,  13,  10,  3}, //�ĸ���
	{  22,  9,  13,  20,  3}, //�����
	{  23,  9,  13,  10,  3}, //����
	{  24,  9,  13,  30,  3}, //��ġ��
	{  31,  9,  13,  30,  3}, //���̽�
	{  32,  9,  13,  30,  3}, //����

	//�Ȱ�ȣ��
	{  3, MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  40,  3}, //ġ����
	{  5, MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  40,  2}, //�����
	{  9, MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  40,  2}, //�����
	{  14,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  40,  2}, //����
	{  18,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4,  20,  2}, //��Ű��Ű
	{  21,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  10,  3}, //�ĸ���
	
	
	{  21,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3,  10,  3}, //�ĸ���
	//{  25,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3,  40,  4}, //����(�Ƹ� ��Ʈ����)
	{  26,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3,  60,  3}, //�ҾǸ�
	//{  27,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4,  60,  4}, //���̸�(�Ƹ� ��Ʈ����)
	{  28,  SCARLET_LEVEL+3,  SCARLET_LEVEL+4,  60,  4}, //�����
	//{  29,  SCARLET_LEVEL+4,  SCARLET_LEVEL+4,  60,  5}, //���и��� �Ƹ� ��Ʈ ����


	{ -1,  0,  0,  0,  0} //�迭�� ��
};


void init_monster()
{
	int i=0;
	while(unigue_group[i].id != -1)
	{
		if(randA_1(100)<=unigue_group[i].percent)
		{
			int f_id_ = unigue_group[i].id;
			auto it = find_if(unique_list.begin(),unique_list.end(),
				[f_id_](unique_infor &v)->bool{
					return v.id == f_id_;
				}
				);

			if(it != unique_list.end())
			{
				if(randA(1))
				{
					unique_list.erase(it);
					unique_list.push_back(unique_infor(unigue_group[i].id,rand_int(unigue_group[i].min_level,unigue_group[i].max_level)));
				}
			}
			else	
				unique_list.push_back(unique_infor(unigue_group[i].id,rand_int(unigue_group[i].min_level,unigue_group[i].max_level)));

		}
		i++;
	}

}



bool is_exist_named(monster_index m_id_) //�ش� ���ӵ尡 ����Ȯ���Ǿ��ִ���
{		
	int id_ = get_unique_to_id(m_id_);

	auto it = find_if(unique_list.begin(),unique_list.end(),
		[id_](unique_infor &v)->bool{
			return v.id == id_;
		}
	);
	return it != unique_list.end();
}
void set_exist_named(monster_index m_id_) //���ӵ带 ����Ȯ��(��Ʈ������)
{
	for(auto it = unique_list.begin();  it !=  unique_list.end(); it++)
	{ //������ ������ ����������.
		if(it->id == get_unique_to_id(m_id_))
		{
			unique_list.erase(it);
			break;
		}
	}
	int id_ = get_unique_to_id(m_id_);
	unique_list.push_back(unique_infor(id_,-1));
}


void create_mon(int floor, int num_)
{
	if(num_ == 0)
		return;

	int i = 0, total=0, num = num_?num_:10;
	vector<mon_group*> group;
	group.reserve(128);
	while(normal_group[i].id != -1)
	{
		if(normal_group[i].min_level<=floor && normal_group[i].max_level>=floor)
		{
			group.push_back(&normal_group[i]);
			total+=normal_group[i].percent;
		}
		else if(normal_group[i].min_level > floor)
			break;
		i++;
	}

	for(int i = 0; i<num; i++)
	{
		int rand_ = randA_1(total);
		vector<mon_group*>::iterator it;
		for(it = group.begin(); it != group.end(); it++)
		{
			if(rand_<=(*it)->percent)
			{
				create_id_to_mon((*it)->id, floor);
				break;
			}
			else
				rand_ -= (*it)->percent;	
	
		}
	}

	for(vector<unique_infor>::iterator it = unique_list.begin();it!=unique_list.end();it++)
	{
		if(it->level == floor)
		{
			create_id_to_unique(it->id, floor);

		}
	}
}


void Set_X_Y(int &x_, int x, int rand_x, int &y_, int y, int rand_y)
{
	x_= x+rand_x;
	y_= y+rand_y;
	if(x_<0)
		x_=0;
	else if(x_>=DG_MAX_X)
		x = DG_MAX_X-1;
	if(y_<0)
		y_=0;
	else if(y_>=DG_MAX_Y)
		y_ = DG_MAX_Y-1;
}




void create_id_to_mon(int id, int level)
{
	vector<monster_index> index;

	switch(id)
	{
	case 0:
		index.push_back(MON_MOOK);
		break;
	case 1:
		index.push_back(MON_RAT);
		break;
	case 2:
		index.push_back(MON_REIMUYUKKURI);
		break;
	case 3:
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 4:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_CROW);
		break;
	case 5:
		index.push_back(MON_FAIRY_RED);
		break;
	case 6:
		index.push_back(MON_FAIRY_BLUE);
		break;
	case 7:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_FAIRY_GREEN);
		break;
	case 8:
		index.push_back(MON_SPIDER);
		break;
	case 9:
		index.push_back(MON_SNAKE);
		break;
	case 10:
		index.push_back(MON_CRANE);
		break;
	case 11:
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 12:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 13:
		//index.push_back(MON_MOOK);
		//index.push_back(MON_MOOK);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		break;
	case 14:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		break;
	case 15:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_GREEN);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 16:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_BLUE);
		break;
	case 17:
		//����־�
		/*index.push_back(MON_KATPA);
		index.push_back(MON_KATPA);*/
		index.push_back(MON_KATPA_SPEAR);
		break;
	case 18:
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		break;
	case 19:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		index.push_back(MON_KATPA_WATER_WIZARD);
		/*for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back((monster_index)rand_int(MON_FAIRY_GREEN_WARRIOR,MON_FAIRY_RED_COMMANDER));*/
		
		break;
	case 20:
		index.push_back(MON_SPIDER);
		index.push_back(MON_SNAKE);
		break;
	case 21:
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(randA(2)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ = randA(2)?1:2, i=0;i<rand_;i++)
		index.push_back(randA(1)?MON_FAIRY_GREEN_WARRIOR:MON_FAIRY_BLUE_MAGICIAN);
		break;
	case 22:
		for(int rand_ =rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(randA(2)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN_WARRIOR:MON_FAIRY_BLUE_MAGICIAN);
		index.push_back(MON_FAIRY_RED_COMMANDER);
		break;
	case 23:
		index.push_back(MON_FIREFLY);
		break;
	case 24:
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		if(randA(4)<1)
			index.push_back(randA(1)?MON_HUMAM_PRIEST:MON_HUMAM_YINYANG);
		break;
	case 25:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_HUMAM_PRIEST:MON_HUMAM_YINYANG);
		if(randA(4)<1)
			index.push_back(MON_HUMAM_SAMURI);
		break;
	case 26:
		for(int rand_ = rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		index.push_back(MON_HUMAM_PRIEST);
		index.push_back(MON_HUMAM_YINYANG);
		index.push_back(randA(1)?MON_HUMAM_PRIEST:MON_HUMAM_YINYANG);
		index.push_back(MON_HUMAM_SAMURI);
		break;
	case 27:
		index.push_back(MON_BAKEKASA);
		break;
	case 28:
		index.push_back(MON_GREEN_MOOK);
		break;
	case 29:
		index.push_back(MON_ORANGE_MOOK);
		break;
	case 30:
		index.push_back(MON_GRAY_MOOK);
		break;
	case 31:
		index.push_back(MON_FROG);
		break;
	case 32:
		index.push_back(randA(2)?(randA(1)?MON_ORANGE_CAT:MON_WHITE_CAT):MON_BLACK_CAT);
		break;
	case 33:
		index.push_back(MON_CROW_TENGU);
		break;
	case 34:
		index.push_back(MON_ONI);
		break;
	case 35:
		index.push_back(MON_MARISAYUKKURI);
		break;
	case 36:
		index.push_back(MON_AYAYUKKURI);
		break;
	case 37:
		index.push_back(MON_REMILIAYUKKURI);
		break;
	case 38:
		index.push_back(MON_YAMABIKO);
		break;
	case 39:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		index.push_back(MON_KATPA_WATER_WIZARD);
		index.push_back(MON_KATPA_SPEAR);
		break;
	case 40:
		index.push_back(MON_YAMABUSH_TENGU);
		break;
	case 41:
		index.push_back(MON_HANATACA_TENGU);
		break;
	case 42:
		for(int rand_ =rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(MON_CROW);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_CROW_TENGU);
		index.push_back(MON_YAMABUSH_TENGU);
		break;
	case 43:
		index.push_back(MON_BLUE_ONI);
		break;
	case 44:
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_KATPA_SPEAR);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_KATPA_WATER_WIZARD);
		break;
	case 45:
		index.push_back(MON_WOLF_TENGU);
		break;
		
	case 46:	
		for(int rand_ =rand_int(1,4), i=0;i<rand_;i++)
			index.push_back(MON_ZOMBIE_FAIRY);
		break;			
	case 47:
		//����å�� ������ �����־���ϹǷ� ����
		index.push_back(MON_MAGIC_BOOK);
		break;		
	case 48:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_HOBGOBRIN);
		if(randA(2)<1)
			index.push_back(MON_HOBGOBRIN_MAID);
		if(randA(4)<1)
			index.push_back(MON_HOBGOBRIN_LIBRARIAN);
		break;		
	case 49:
		index.push_back(MON_HOBGOBRIN_MAID);
		index.push_back(MON_HOBGOBRIN_MAID);
		break;	
	case 50:
		index.push_back(MON_HOBGOBRIN_LIBRARIAN);
		break;
	case 51:	
		for(int rand_ =rand_int(3,5), i=0;i<rand_;i++)
			index.push_back(MON_MAID_FAIRY);
		break;
	case 52:
		index.push_back(MON_CHUPARCABRA);
		break;
	case 53:
		index.push_back(MON_EAGLE);
		break;
	case 54:
		index.push_back(MON_TIGER);
		break;
	case 55:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_RAIJUU);
		break;
	case 56:
		index.push_back(MON_DRAGON_BABY);
		break;
	case 57:
		for(int rand_ =rand_int(1,5), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_YAMAWARO_NINJA:MON_YAMAWARO_WAWRRIOR);
		if(randA(3)<1)
			index.push_back(MON_YAMAWARO_FLAG);
		break;
	case 58:
		index.push_back(MON_RED_UFO);
		break;
	case 59:
		for(int rand_ =rand_int(3,5), i=0;i<rand_;i++)
		index.push_back(randA(2)?(randA(1)?MON_RED_UFO:MON_BLUE_UFO):MON_GREEN_UFO);
		break;
	case 60:
		index.push_back(MON_HOBGOBRIN_TEMP);
		break;
	case 61:
		index.push_back(MON_SANPEI_FIGHTER);
		break;
	case 62:
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_VAMPIER_BAT);
		break;
	case 63:
		index.push_back(MON_DEAGAMA);
		break;	
	}

	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1),rand_x=0,rand_y=0, r=2+index.size()/3,k=0;
	for(vector<monster_index>::iterator it=index.begin();it!=index.end();it++)
	{ 
		int x_ = 0, y_ = 0;
		Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y_))
		{
			if(it==index.begin())
			{
				x = randA(DG_MAX_X-1),y = randA(DG_MAX_Y-1);
			}
			else
			{
				rand_x=rand_int(-r,r);
				rand_y=rand_int(-r,r);
				if(++k%5 == 0)
				{
					r++;
				}
			}
			Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		}
		if(env[level].AddMonster((*it),0,coord_def(x_,y_)))
		{
			continue;
		}
		k = 0;
		r=2+index.size()/3;
		rand_x=rand_int(-r,r);
		rand_y=rand_int(-r,r);
	}
}	


int get_unique_to_id(int m_id)
{
	switch(m_id)
	{
	default: return -1;
	case MON_RUMIA:return 0;
	case MON_MISTIA: return 1;
	case MON_WRIGGLE: return 2;
	case MON_CIRNO: return 3;
	case MON_MEDICINE: return 4;
	case MON_DIEFAIRY: return 5;
	case MON_KISUME: return 6;
	case MON_CHEN: return 7;
	case MON_KOGASA: return 8;
	case MON_SUNNY:case MON_LUNAR:case MON_STAR: return 9;
	case MON_KYOUKO: return 10;
	case MON_SIGMUND: return 11;
	case MON_MOMIZI: return 12;
	case MON_AYA: return 13;
	case MON_WAKASAGI: return 14;
	case MON_YAMAME: return 15;
	case MON_NAZRIN:case MON_DAUZING: return 16;
	case MON_YOSIKA: return 17;
	case MON_SEKIBANKI:
	case MON_SEKIBANKI_BODY:
	case MON_SEKIBANKI_HEAD: return 18;
	case MON_NITORI: return 19;
	case MON_KEGERO: return 20;
	case MON_PARSI: return 21;
	case MON_BENBEN:
	case MON_YATHASI: return 22;
	case MON_ORIN:
	case MON_ORIN_CAT: return 23;
	case MON_ICHIRIN:
	case MON_UNZAN:
	case MON_UNZAN_PUNCH: return 24;
	case MON_PACHU: return 25;
	case MON_KOAKUMA: return 26;
	case MON_MEIRIN: return 27;
	case MON_SAKUYA: return 28;
	case MON_REMILIA: return 29;
	case MON_KASEN: return 30;
	case MON_KOISHI: return 31;
	case MON_NUE: return 32;
	case MON_FLAN: 
	case MON_FLAN_BUNSIN: return 33;
	case MON_TEWI:  return 34;
	case MON_CLOWNPIECE:  return 35;
	case MON_DOREMI:  return 36;
	}
}




void create_id_to_unique(int id, int level)
{
	vector<monster_index> index;

	switch(id)
	{
	case 0:
		index.push_back(MON_RUMIA);
		break;
	case 1:
		index.push_back(MON_WRIGGLE);
		break;
	case 2:
		index.push_back(MON_MISTIA);
		break;
	case 3:
		index.push_back(MON_CIRNO);
		break;
	case 4:
		index.push_back(MON_MEDICINE);
		break;
	case 5:
		index.push_back(MON_DIEFAIRY);
		break;
	case 6:
		{
			int x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y_))
			{
				x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			}			
			env[level].MakeEvent(EVL_KISME,coord_def(x_,y_),EVT_APPROACH_SMALL);
		}
		break;
	case 7:
		index.push_back(MON_CHEN);
		for(int i=0;i<4;i++)
			index.push_back(randA(2)?(randA(1)?MON_ORANGE_CAT:MON_WHITE_CAT):MON_BLACK_CAT);
		break;
	case 8:
		index.push_back(MON_KOGASA);
		break;
	case 9:
		index.push_back(MON_SUNNY);
		index.push_back(MON_LUNAR);
		index.push_back(MON_STAR);
		break;
	case 10:
		index.push_back(MON_KYOUKO);
		break;
	case 11:
		index.push_back(MON_SIGMUND);
		break;
	case 12:
		index.push_back(MON_MOMIZI);
		break;
	case 13:
		index.push_back(MON_AYA);
		break;
			
	case 14:	
		index.push_back(MON_WAKASAGI);
		break;
	case 15:
		index.push_back(MON_YAMAME);
		break;
	case 16:
		index.push_back(MON_NAZRIN);
		if(randA(2)<1)
		{			
			for(int rand_ =rand_int(2,5), i=0;i<rand_;i++)
				index.push_back(MON_RAT);
		}
		break;
	case 17:
		index.push_back(MON_YOSIKA);
		break;
	case 18:
		index.push_back(MON_SEKIBANKI);
		break;
	case 19:
		index.push_back(MON_NITORI);
		if(randA(2)<1)
		{			
			index.push_back(MON_KATPA);
			index.push_back(MON_KATPA_SPEAR);
			index.push_back(MON_KATPA_WATER_WIZARD);
		}
		break;
	case 20:
		index.push_back(MON_KEGERO);
		break;		
	case 21:
		index.push_back(MON_PARSI);
		break;	
	case 22:
		index.push_back(MON_BENBEN);
		index.push_back(MON_YATHASI);
		break;
	case 23:
		index.push_back(MON_ORIN);
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_ZOMBIE_FAIRY);
		break;
	case 24:
		index.push_back(MON_ICHIRIN);
		break;	
	case 25:
		//ȫ���� ������ ���� ����
		index.push_back(MON_PACHU);
		break;	
	case 26:
		index.push_back(MON_KOAKUMA);
		break;	
	case 27:
		//�Ƹ� �� ��ȣ�� �Ⱦ�����? ���̸��� ȫ���� �Ա� ���� ����
		index.push_back(MON_MEIRIN);
		break;	
	case 28:
		index.push_back(MON_SAKUYA);
		break;	
	case 29:
		//���� ȫ���� �ֽ��� ��������(�����������)
		index.push_back(MON_REMILIA);
		break;		
	case 30:
		index.push_back(MON_KASEN);
		index.push_back(MON_EAGLE);
		index.push_back(MON_TIGER);
		index.push_back(MON_RAIJUU);
		index.push_back(MON_DRAGON_BABY);
		break;	
	case 31:
		index.push_back(MON_KOISHI);
		break;
	case 32:
		index.push_back(MON_NUE);
		break;
	}

	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1),rand_x=0,rand_y=0, r=2+index.size()/3,k=0;
	for(vector<monster_index>::iterator it=index.begin();it!=index.end();it++)
	{ 
		int x_ = 0, y_ = 0, limit_ = 10000;
		Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		bool only_water = (mondata[(*it)].flag & M_FLAG_CANT_GROUND) && (mondata[(*it)].flag & M_FLAG_SWIM);
		while(!env[level].isMove(x_,y_,false, only_water, only_water) || 
			(env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || 
			env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y))
		{
			if(limit_--<0)
				break;
			if(it==index.begin())
			{
				x = randA(DG_MAX_X-1),y = randA(DG_MAX_Y-1);
			}
			else
			{
				rand_x=rand_int(-r,r);
				rand_y=rand_int(-r,r);
				if(++k%5 == 0)
				{
					r++;
				}
			}
			Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		}
		if(limit_<=0)
			continue;

			
		if(env[level].AddMonster((*it),0,coord_def(x_,y_)))
		{
			continue;
		}
		k = 0;
		r=2+index.size()/3;
		rand_x=rand_int(-r,r);
		rand_y=rand_int(-r,r);
	}
}


void SetResistMonster(monster* mon)
{
	mon->ice_resist = 0;
	mon->fire_resist = 0;
	mon->poison_resist=0;
	mon->elec_resist=0;
	switch(mon->id)
	{
	case MON_CIRNO:
		mon->ice_resist=3;
		mon->fire_resist=-1;
		break;
	case MON_MISTIA:
		mon->poison_resist=-1;
		break;
	case MON_MEDICINE:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_DIEFAIRY:
		mon->ice_resist=1;
		break;
	case MON_GHOST:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_BAKEKASA:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_KOGASA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_ONI:
		mon->fire_resist=1;
		break;
	case MON_REMILIAYUKKURI:
		mon->poison_resist=1;
		break;
	case MON_KATPA_WATER_WIZARD:
		mon->ice_resist=1;
		break;
	case MON_HANATACA_TENGU:
		mon->poison_resist=1;
		break;
	case MON_BLUE_ONI:
		mon->ice_resist=1;
		break;
	case MON_MUSHROOM:
		mon->poison_resist=1;
		break;
	case MON_WAKASAGI:
		mon->ice_resist=1;
		break;
	case MON_YAMAME:		
		mon->poison_resist=1;
		break;
	case MON_YOSIKA:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SEKIBANKI:
	case MON_SEKIBANKI_BODY:
		mon->fire_resist=1;
		break;
	case MON_NITORI:
		mon->elec_resist=2;
		mon->ice_resist=2;
		break;
	case MON_BENBEN:
	case MON_YATHASI:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_ORIN:		
	case MON_ORIN_CAT:
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_ZOMBIE_FAIRY:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_ICHIRIN:
		mon->fire_resist=1;
		mon->elec_resist=1;
		break;
	case MON_UNZAN:
	case MON_UNZAN_PUNCH:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_PACHU:
		mon->elec_resist=2;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_HOBGOBRIN_LIBRARIAN:
		mon->ice_resist=1;
		mon->fire_resist=1;
		break;
	case MON_CHUPARCABRA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_KOAKUMA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_REMILIA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_RAIJUU:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_TIGER:
		mon->ice_resist=1;
		break;
	case MON_DRAGON_BABY:
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_YAMAWARO_NINJA:
	case MON_YAMAWARO_WAWRRIOR:
	case MON_YAMAWARO_FLAG:
		mon->fire_resist=1;
		break;
	case MON_ONBASIRA:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_RED_UFO:
		mon->fire_resist=2;
		break;
	case MON_GREEN_UFO:
		mon->elec_resist=2;
		mon->poison_resist=1;
		break;
	case MON_BLUE_UFO:
		mon->ice_resist=2;
		break;
	case MON_NUE:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_SANPEI_FIGHTER:
		mon->ice_resist=2;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_DEAGAMA:
		mon->poison_resist=1;
		break;
	case MON_NAMAZ:
		mon->fire_resist=1;
		mon->elec_resist=1;
		break;
	case MON_HELL_CROW:
		mon->fire_resist=3;
		break;
	case MON_LANTERN_YOUKAI:
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_YINYAN:
		mon->elec_resist=2;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_YUUGENMAGAN:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_ELIS:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SARIEL:
		mon->elec_resist=1;
		mon->ice_resist=2;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SARA:
		mon->poison_resist=1;
		break;
	case MON_LUIZE:
		mon->ice_resist=1;
		break;
	case MON_YUKI:
		mon->fire_resist=3;
		break;
	case MON_MAI:
		mon->ice_resist=3;
		break;
	case MON_YUMEKO:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_MAGICAL_STAR:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_GOLEM:
		mon->elec_resist=3;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
	case MON_EVIL_EYE:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_SCHEMA_EYE:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_FLAN:
	case MON_FLAN_BUNSIN:
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_TEWI:
		break;
	case MON_CLOWNPIECE:
		mon->fire_resist=2;
		break;
	case MON_DOREMI:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	}
}