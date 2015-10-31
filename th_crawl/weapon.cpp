//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: weapon.h
//
// ����: ���� ���� �Լ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "weapon.h"
#include "enum.h"



int GetPulsDamage(weapon_brand brand, int damage)
{
	switch(brand)
	{
		case WB_FIRE:
		case WB_COLD:
			damage += damage/3;
			break;
		default:
			break;
	}
	return damage;
}
int GetAttType(weapon_brand brand)
{
	int att_type = ATT_NORMAL;
	switch(brand)
	{
		case WB_FIRE:
			att_type = ATT_FIRE;
			break;
		case WB_COLD:
			att_type = ATT_COLD;
			break;
		case WB_POISON:
			att_type = ATT_S_POISON;
			break;
		default:
			break;
	}
	return att_type;	
}
const char* GetBrandString(weapon_brand brand, bool artifact_)
{
	switch(brand)
	{
		case WB_FIRE:
			return !artifact_?"ȭ���� ":"ȭ��";	
		case WB_COLD:
			return !artifact_?"�ñ��� ":"�ñ�";
		case WB_POISON:
			return !artifact_?"�͵��� ":"�͵�";
		default:
			return !artifact_?"�˼����� ":"����";	
	}	

}