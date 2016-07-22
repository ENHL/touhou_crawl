//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: item.h
//
// ����: ������ Ŭ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ITEM_H__
#define  __ITEM_H__

#include "enum.h"
#include "unit.h"
#include "texture.h"
#include "atifact.h"
#include "scroll.h"

class item;

struct item_infor
{
	name_infor name;
	name_infor name2;
	textures *image;
	item_type type;
	float weight;
	int value;
	bool is_pile;
	int num;
	bool can_throw;

	int value0;
	int value1;
	int value2;
	int value3;
	int value4;
	int value5;
	int value6;
	int value7;
	int value8;

	bool curse;

	bool artifact;
	item_infor():name("����",true), name2("",true) ,image(NULL),type(ITM_WEAPON_FIRST),weight(0),value(0),is_pile(false),
		num(1),value0(0),value1(0),value2(0),value3(0),value4(0),value5(0),value6(0), value7(0), value8(0)
		, curse(false), artifact(false)
	{};
	item_infor(item* item_);
	item_infor(item* item_, int num_);

	
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);

};


struct potion_iden
{
	bool iden;
	int color;
	potion_iden():
	iden(false), color(0)
	{};
};
struct scroll_iden
{
	char iden; //1�� �����, 2�� ���û����, 3�� �ĺ�
	int type;
	scroll_iden():
	iden(false), type(0)
	{};
};
struct ring_iden
{
	char iden; //1�� �����, 2�� �ĺ�
	int type;
	ring_iden():
	iden(false), type(0)
	{};
};
struct amulet_iden
{
	char iden; //1�� �����, 2�� �ĺ�
	int type;
	amulet_iden():
	iden(false), type(0)
	{};
};
struct spellcard_iden
{
	char iden; //1�� �����, 2�� �ĺ�
	int type;
	spellcard_iden():
	iden(false), type(0)
	{};
};



class Iden_collect
{
public:
	potion_iden potion_list[PT_MAX];
	scroll_iden scroll_list[SCT_MAX];
	ring_iden ring_list[RGT_MAX];
	amulet_iden amulet_list[AMT_MAX];
	spellcard_iden spellcard_list[SPC_V_MAX];
	bool books_list[BOOK_LAST];
};


class item
{
public:
	name_infor name;
	name_infor second_name;
	textures *image;
	coord_def position;
	coord_def prev_position;
	item_type type;
	float weight;
	int value;
	bool is_pile;
	int num;
	char id;
	bool prev_sight;
	bool not_find;
	bool now_find;
	bool curse;
	bool identify;
	bool identify_curse;
	bool can_throw; 
	bool drop;
	bool throw_item;

	int value0; //���� - å-����(�� ���� �ʿ��� �����۾ƴϸ� ������� �ʴ� ������.)

	
	int value1; //value1 - ����,ź��-���߷� ��-AC ����-SH ����,����,��ũ��,��-���� å-���� ����ī��-Ƚ�� �ߵ���-����
	
	int value2; //value2 - ����,ź��-���ݷ� ��,����-EV  ����-������ ��-��ġ ����ī��-����

	int value3;	//value3 - ��-�ּ� EV�г�Ƽ ź��-��æƮ ����-�ż��� ����ī��-��뿹��Ƚ��
	
	int value4; //value4 - ����-��æƮ ��-AC+ ����-SH+ ź��-���� ����(p��)-����id 

	int value5;	//value5 - ����-�Ӽ� ��-���� ����-pow���ġ
	
	int value6; //value6 - �Ӽ���æƮ �ð�. 0�̸� ��Ȯ��.-1�̸� �ĺ�+����, ����� �ĺ�+����

	int value7; //value7 - ���� - �ִ����
	
	int value8; //value8 - ���� - �ּҰ���

	
	vector<atifact_infor> atifact_vector;

	item();
	item(const coord_def &c, const item_infor &t);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	
	string GetName(int num_ = -1);
	name_infor GetNameInfor();
	const D3DCOLOR item_color();
	bool draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_);

	bool isSimpleType(item_type_simple type_); //�ش� Ÿ���� �³� Ȯ���Ѵ�.
	bool isRightType(equip_type type_); //�ش� ������ ������ �� �ִ��� Ȯ���Ѵ�.
	equip_type GetArmorType();//�� Ÿ������ �����Ѵ�.
	bool SameItem(const item &item_);
	float GetStabPercent();
	int GetValue(int i);


	bool isweapon();
	bool isarmor();
	bool isjewerly();
	bool isring();
	bool isiden();
	bool isautopick();
	bool isArtifact();
	bool isChargable();

	bool Curse(bool equip_,equip_type kind_);
	bool isEnhantable();
	bool Enchant(equip_type kind_, int acc_);
	void pick();

	void Identify();//���ĺ�
	void autoIdentify();//��ű��迭�� �ڵ��ĺ�
	void income_view(); //�þ߿� ������.

	int action(int delay_);
	bool offsetmove(const coord_def &c);

};


item_infor& makeCustomBook(item_infor* t);
item_infor& makeitem(item_type type, int good_bad, item_infor* t, int select_ = -1);
item_infor& makePitem(monster_index mon_id, int num, item_infor* t);
item_infor& CustomItem(item_infor* t, item_type type, textures* graphic, int num, bool pile_, bool curse, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, bool throw_, name_infor name_, name_infor name2_, float weight, int value);
item_infor& CustomSimpleItem(item_infor* t, item_type type, int num, bool curse, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8);
int baditem(const item_infor *item_);
item_type RandomItemType();

const char* GetItemTypeSting(item_type_simple type);


bool GetItemofKey(list<item>::iterator it,list<item>::iterator it2);
int GetItemofNum(list<item>::iterator it,list<item>::iterator it2);
 
list<item>::iterator GetKeytoItem(char key_);

void init_identify();
item_infor& CreateFloorItem(int floor, item_infor* item_);
void create_item(int floor, int num_);


extern Iden_collect iden_list;

#endif // __PLAYER_H__