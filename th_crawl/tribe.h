//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: tribe.h
//
// 내용: 종족 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __TRIBE_H__
#define  __TRIBE_H__

#include <string>

using namespace std;

extern enum tribe_type;

enum tribe_proper_type
{
	TPT_FIRE_RESIST,
	TPT_COLD_RESIST,
	TPT_ELEC_RESIST,
	TPT_POISON_RESIST,
	TPT_STEALTH,
	TPT_FLY,	
	TPT_SWIM,
	TPT_SIZE,
	TPT_HORN,
	TPT_GHOST_FOOT,
	TPT_CHEUKUMOGAMI,
	TPT_HP,
	TPT_MAX
};



class tribe_property
{
public:
	tribe_proper_type id;
	int value;
	tribe_property():id(TPT_FIRE_RESIST),value(0){}
	tribe_property(tribe_proper_type id_, int value_):id(id_),value(value_){}
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);

	string GetName();
	string GetInfor();
	string GetDetail();
	void gain(bool gain_);
};




void SetTribe(tribe_type select_);
void PropertyView();
void LevelUpTribe(int level_);





#endif // __TRIBE_H__