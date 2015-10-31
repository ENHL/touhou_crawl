//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: weapon.h
//
// ����: ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __WEAPON_H__
#define  __WEAPON_H__



enum weapon_brand
{
	WB_NORMAL =0,
	WB_FIRE,
	WB_COLD,
	WB_POISON,
	WB_MAX
};

int GetPulsDamage(weapon_brand brand, int damage);
int GetAttType(weapon_brand brand);
const char* GetBrandString(weapon_brand brand, bool artifact_);

#endif // __WEAPON_H__