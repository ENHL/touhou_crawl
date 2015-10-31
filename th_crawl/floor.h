//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: floor.h
//
// ����: �ٴ� Ŭ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __FLOOR_H__
#define  __FLOOR_H__

#include "enum.h"
#include "common.h"
#include "unit.h"

enum floor_type //�Ʒ� �ִ� ���� �켱������ ����.
{
	FLOORT_NORMAL = 0,
	FLOORT_AUTUMN,
	FLOORT_STONE,
	FLOORT_SCHEMA,
	FLOORT_MAX
};

class textures;
class unit;

class floor_effect
{
public:
	coord_def position;
	textures *image;
	textures *image2;
	int time;	
	floor_type type;
	parent_type parent;
	
	floor_effect();
	floor_effect(const coord_def &c, textures *t, textures *t2, floor_type type_, int time_, parent_type parent_ = PRT_NEUTRAL);
	
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	bool draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_);
	void prev_check();
	bool action(int delay_);
	void onWalk(unit* unit_);
	int danger(unit* unit_, bool first_ = true);

	bool Update(textures *t, textures *t2, floor_type type_, int time_, parent_type parent_ = PRT_NEUTRAL);

	static bool isFly(floor_type type_); //�ϴû� ��ġ(��,����� ����)
	static bool isSwim(floor_type type_); //���� ��ġ����(���� ����)
	static bool isNoGround(floor_type type_); //���� ��ġ�Ұ�?

	char* GetName();
};



#endif // __FLOOR_H__