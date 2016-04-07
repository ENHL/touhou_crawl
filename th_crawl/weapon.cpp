//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: weapon.h
//
// ����: ���� ���� �Լ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "weapon.h"
#include "enum.h"
#include "common.h"


int GetNewBrand(int rare_weigth_)
{
	if(randA(99)>=rare_weigth_)
	{
		return randA(2)==0?WB_FIRE:(randA(1)==0?WB_COLD:WB_POISON);
	}
	else
	{
		return randA(2)==0?WB_CURSE:(randA(1)==0?WB_AUTUMN:WB_WEATHER);
	}
	return WB_NORMAL;

}

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
		case WB_CURSE:	
			att_type = ATT_CURSE;		
			break;
		case WB_WEATHER:
			att_type = ATT_WEATHER;
			break;
		case WB_AUTUMN:
			att_type = ATT_AUTUMN;
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
		case WB_CURSE:		
			return !artifact_?"������ ":"����";	
		case WB_WEATHER	:
			return !artifact_?"����� ":"���";	
		case WB_AUTUMN:
			return !artifact_?"��ǳ�� ":"��ǳ";	
		default:
			return !artifact_?"�˼����� ":"����";	
	}	

}