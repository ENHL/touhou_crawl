//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: weapon.h
//
// 내용: 무기 관련 함수들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "weapon.h"
#include "enum.h"
#include "common.h"


int GetNewBrand(int rare_weigth_)
{
	if(randA(99)>=rare_weigth_)
	{
		int arr_[] = {WB_FIRE,WB_COLD,WB_POISON,WB_PROTECT};
		return arr_[randA(3)];
	}
	else
	{
		int arr_[] = {WB_CURSE,WB_AUTUMN,WB_WEATHER,WB_MANA_REGEN,WB_FAST_CAST,WB_PROTECT};
		return arr_[randA(5)];
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
		case WB_MANA_REGEN:
		case WB_FAST_CAST:
		case WB_PROTECT:
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
			return !artifact_?"화염의 ":"화염";	
		case WB_COLD:
			return !artifact_?"냉기의 ":"냉기";
		case WB_POISON:
			return !artifact_?"맹독의 ":"맹독";	
		case WB_CURSE:		
			return !artifact_?"저주의 ":"저주";	
		case WB_WEATHER	:
			return !artifact_?"비상의 ":"비상";	
		case WB_AUTUMN:
			return !artifact_?"단풍의 ":"단풍";	
		case WB_MANA_REGEN:
			return !artifact_?"영력회복의 ":"영력회복";	
		case WB_FAST_CAST:
			return !artifact_?"고속영창의 ":"고속영창";	
		case WB_PROTECT:
			return !artifact_?"보호의 ":"보호";	
		default:
			return !artifact_?"알수없는 ":"버그";	
	}	

}