//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: skill.cpp
//
// ����: ��ų����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "player.h"
#include "skill_use.h"
#include "throw.h"
#include "key.h"
#include "environment.h"
#include "mon_infor.h"
#include "projectile.h"
extern HANDLE mutx;


bool SkillFlagCheck(skill_list skill, skill_flag flag)
{
	switch(skill)
	{
	case SKL_KANAKO_2:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUMMON) & flag);
	case SKL_KANAKO_1:
	case SKL_YUYUKO_3:
		return ((S_FLAG_SPEAK) & flag);
	case SKL_SWAKO_DIGGING:
		return ((S_FLAG_SPEAK | S_FLAG_UNSIGHT) & flag);
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
		return 0;
	case SKL_EIRIN_0:
		return ((S_FLAG_SPEAK | S_FLAG_CLOUD) & flag);
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_SATORI_2:
	case SKL_YUYUKO_1:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_STATUE:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE) & flag);
	case SKL_SWAKO_JUMP:
		return ((S_FLAG_SMITE | S_FLAG_RECT | S_FLAG_NO_TARGET) & flag);		
	case SKL_YUKARI_2:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUKIMA) & flag);
	case SKL_YUKARI_1:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUMMON | S_FLAG_SUKIMA) & flag);
	case SKL_SATORI_1:
		return ((S_FLAG_SPEAK | S_FLAG_DEBUF | S_FLAG_SMITE) & flag);
	case SKL_KANAKO_3:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_YUUGI_1:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_YUYUKO_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_SWAKO_SLEEP:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return ((S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag);	
	case SKL_SWAKO_TEMPLE:
		return ((S_FLAG_IMMEDIATELY) & flag);		
	case SKL_SHINKI_1:
	case SKL_SHINKI_2:
	case SKL_SHINKI_3:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_MISYAGUZI:
		return ((S_FLAG_SPEAK | S_FLAG_IMMEDIATELY | S_FLAG_SUMMON) & flag);
	case SKL_GRAZE:
	case SKL_LEVITATION:
	case SKL_INVISIBLE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
		return ((S_FLAG_IMMEDIATELY) & flag);
	case SKL_NONE:
	default:
		return false;
	}
}
int SkillLength(skill_list skill)
{
	switch(skill)
	{		
	case SKL_SWAKO_JUMP:
		 return 2;
	case SKL_KANAKO_2:
		return 3;
	case SKL_SWAKO_TOUGUE:
		return 5;
	case SKL_KANAKO_1:
	case SKL_EIRIN_0:
	case SKL_YUUGI_3_THROW:
		return 7;
	case SKL_SATORI_1:
	case SKL_SATORI_2:
	case SKL_YUYUKO_1:
	case SKL_YUYUKO_3:
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_STATUE:
		return 8;
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
		return 1;
	case SKL_KANAKO_3:
	case SKL_GRAZE:
	case SKL_LEVITATION:
	case SKL_INVISIBLE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_NONE:
	case SKL_YUUGI_1:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:		
	case SKL_SHINKI_1:
	case SKL_SHINKI_2:
	case SKL_SHINKI_3:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_YUYUKO_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:	
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:	
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	default:
		return 0;
	}
}
const char* SkillString(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
		return "�ǽ��ʷ���";
	case SKL_KANAKO_2:
		return "�ǽ��ʷ�����";
	case SKL_KANAKO_3:
		return "�ǽ��ʷ�ǳ";
	case SKL_GRAZE:
		return "�׷����� �ߵ�";
	case SKL_GRAZE_OFF:
		return "�׷����� ����";
	case SKL_LEVITATION:
		return "���� �ߵ�";
	case SKL_LEVITATION_OFF:
		return "���� ����";
	case SKL_INVISIBLE:
		return "���� �ߵ�";
	case SKL_INVISIBLE_OFF:
		return "���� ����";
	case SKL_EIRIN_0:
		return "���� ������";
	case SKL_EIRIN_1:
		return "��ü����";
	case SKL_EIRIN_2:
		return "��ü���";
	case SKL_BYAKUREN_1:
		return "���°�ȭ";
	case SKL_BYAKUREN_2:
		return "���°�ȭ";
	case SKL_SIZUHA_1:
		return "������ ����";
	case SKL_SIZUHA_2:
		return "��ǳ ��";
	case SKL_MINORIKO_1:
		return "�ɷ�ġ ȸ��";
	case SKL_MINORIKO_2:
		return "ü�� ȸ��";
	case SKL_YUUGI_1:
		return "�� ���ñ�";
	case SKL_YUUGI_2:
		return "���� ���÷���";
	case SKL_YUUGI_3:
	case SKL_YUUGI_3_THROW:
		return "���������";
	case SKL_YUUGI_4:
		return "������ ��ȿ";
	case SKL_YUUGI_5:
		return "�ﺸ�ʻ�";
	case SKL_SATORI_1:
		return "Ʈ��츶";
	case SKL_SATORI_2:
		return "���ɼ�";		
	case SKL_SHINKI_1:
		return "�ϱ� ���� ��ȯ";		
	case SKL_SHINKI_2:
		return "�߱� ���� ��ȯ";		
	case SKL_SHINKI_3:
		return "��� ���� ��ȯ";
	case SKL_YUYUKO_ON:
		return "���� ��ȯ �ߵ�";
	case SKL_YUYUKO_OFF:
		return "���� ��ȯ ����";
	case SKL_YUYUKO_1:	
		return "���� ����";	
	case SKL_YUYUKO_2:
		return "���� ��ȯ ����";	
	case SKL_YUYUKO_3:		
		return "���� ����";	
	case SKL_YUKARI_1:
		return "������ ���� ��";
	case SKL_YUKARI_2:
		return "ȯ�󱤻���";
	case SKL_YUKARI_3:
		return "���߰��";
	case SKL_YUKARI_4:
		return "��������";	
	case SKL_SWAKO_JUMP:
		return "������ ����";	
	case SKL_SWAKO_TEMPLE:
		return "���� �����";	
	case SKL_SWAKO_WATER_GUN:
		return "����";	
	case SKL_SWAKO_TOUGUE:
		return "������ ��";	
	case SKL_SWAKO_CURSE:
		return "�������� ���";	
	case SKL_SWAKO_DIGGING:
		return "����";	
	case SKL_SWAKO_SUMMON_FLOG:
		return "������ ��ȯ";	
	case SKL_SWAKO_STATUE:
		return "���� �����";	
	case SKL_SWAKO_RAIN:
		return "�� ������";
	case SKL_SWAKO_SLEEP:
		return "����";
	case SKL_SWAKO_MISYAGUZI:
		return "�̻������� ��ȯ";
	case SKL_HINA_1:
		return "�׶�";
	case SKL_HINA_2:
		return "���� ����(��ȭ)";
	case SKL_HINA_3:
		return "�� ����(�ݻ�)";
	case SKL_HINA_4:
		return "��ű� ����(ȸ��)";
	case SKL_NONE:
	default:
		return "�˼����� �ɷ�";
	}
}
int SkillCap(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
	case SKL_KANAKO_2:
	case SKL_KANAKO_3:
	case SKL_EIRIN_0:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_YUUGI_1:
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_SATORI_1:
	case SKL_SATORI_2:	
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	case SKL_YUYUKO_1:	
	case SKL_YUYUKO_2:	
	case SKL_YUYUKO_3:	
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return 200;
	case SKL_LEVITATION:
		return 75;
	case SKL_INVISIBLE:
		return 100;
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_OFF:
	case SKL_YUYUKO_ON:
	case SKL_NONE:
	default:
		return 0;
	}
}
int SkillNoise(skill_list skill)
{
	switch(skill)
	{
	case SKL_GRAZE:
	case SKL_LEVITATION:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_NONE:
	case SKL_INVISIBLE:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_YUUGI_1:
	case SKL_SATORI_2:
	case SKL_YUKARI_3:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_SLEEP:
		return 0;
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_SATORI_1:
	case SKL_YUYUKO_1:
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:	
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return 4;
	case SKL_KANAKO_1:
	case SKL_KANAKO_2:
	case SKL_KANAKO_3:
	case SKL_EIRIN_0:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:	
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	case SKL_YUYUKO_2:	
	case SKL_YUYUKO_3:
	case SKL_YUKARI_4:	
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_MISYAGUZI:
		return 8;
	case SKL_YUUGI_4:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_RAIN:
		return 12;
	case SKL_YUUGI_5:
		return 16;
	case SKL_YUYUKO_ON:	
	case SKL_YUYUKO_OFF:	
	default:
		return 0;
	}

}
int SkillPow(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
	case SKL_KANAKO_2:
	case SKL_KANAKO_3:
	case SKL_EIRIN_0:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
		return you.skill[SKT_INVOCATE].level*5;
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_YUUGI_1:
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_SATORI_2:
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	case SKL_YUYUKO_1:
	case SKL_YUYUKO_2:
	case SKL_YUYUKO_3:
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		//�žӽ����� �ٲٱ�
		return you.piety;
	case SKL_SIZUHA_1:
	case SKL_SATORI_1:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:
		return you.level*5;
		//return you.skill[SKT_SPELLCASTING].level*5;
	case SKL_SIZUHA_2:
		return you.piety;
	case SKL_LEVITATION:
	case SKL_INVISIBLE:
		return you.skill[SKT_EVOCATE].level*5;
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_NONE:
	default:
		return 0;
	}
}
int SkillDiffer(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
		return SkillDiffer_simple(-4,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_KANAKO_2:
		return SkillDiffer_simple(-2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_KANAKO_3:
		return SkillDiffer_simple(1,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_0:
		return SkillDiffer_simple(-6,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_1:
		return SkillDiffer_simple(-2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_2:
		return SkillDiffer_simple(2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_LEVITATION:
		return SkillDiffer_simple(-4,SKT_EVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_INVISIBLE:
		return SkillDiffer_simple(0,SKT_EVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_BYAKUREN_1:
		return 100;
		//return SkillDiffer_simple(-3,SKT_SPELLCASTING,SKT_ERROR,SKT_ERROR);
	case SKL_BYAKUREN_2:		
		return 100;
		//return SkillDiffer_simple(1,SKT_SPELLCASTING,SKT_ERROR,SKT_ERROR);
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_SIZUHA_1: //�žӽɺ�� �������� �ٲ�?
	case SKL_SIZUHA_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_YUUGI_1:
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_SATORI_1:
	case SKL_SATORI_2:
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	case SKL_YUYUKO_1:
	case SKL_YUYUKO_2:
	case SKL_YUYUKO_3:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return 100;
	case SKL_NONE:
	default:
		return 0;
	}
}
int SkillDiffer_simple(int differ, skill_type s1, skill_type s2, skill_type s3)
{
	int num = 0;
	float success_ = 0;
	if(s1 != -1)
	{
		success_ += you.skill[s1].level;
		num++;
	}	
	if(s2 != -1)
	{
		success_ += you.skill[s2].level;
		num++;
	}
	if(s3 != -1)
	{
		success_ += you.skill[s3].level;
		num++;
	}
	if(num)
		success_/=num;
	
	success_ = max(0,(success_-differ<=14)?(success_-differ)*(2*14+(success_-differ-1)*-1.07)/2:99);
	return success_;
}
int SkillMana(skill_list skill)
{
	switch(skill)
	{
	case SKL_BYAKUREN_1:
	case SKL_EIRIN_0:
	case SKL_GRAZE:
	case SKL_YUUGI_1:
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return 0;		
	case SKL_SWAKO_WATER_GUN:
		return 1;
	case SKL_KANAKO_1:
	case SKL_LEVITATION:
	case SKL_SATORI_1:
	case SKL_YUYUKO_1:
	case SKL_YUKARI_1:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TOUGUE:
		return 2;
	case SKL_KANAKO_2:
	case SKL_MINORIKO_1:
	case SKL_YUYUKO_2:
	case SKL_YUKARI_3:
		return 3;
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_YUKARI_2:
		return 4;
	case SKL_EIRIN_2:
	case SKL_MINORIKO_2:
	case SKL_SATORI_2:
	case SKL_YUYUKO_3:
		return 5;
	case SKL_KANAKO_3:
		return 4;
	case SKL_INVISIBLE:
	case SKL_YUKARI_4:
		return 6;
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_NONE:
	case SKL_EIRIN_1:
	case SKL_SIZUHA_2:
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	default:
		return 0;
	}
}
bool SkillPlusCost(skill_list skill,bool check_)
{ //return false�� �ڽ�Ʈ�� �����Ѱ��̴�.
	//check_�� �Ҹ� ���ϰ� üũ��
	switch(skill)
	{
	case SKL_EIRIN_0:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		return true;	
	case SKL_SATORI_1:
	case SKL_BYAKUREN_1:
	case SKL_SIZUHA_1:
		if(!check_)
			you.PietyUpDown(-2);
		return true;		
	case SKL_MINORIKO_1:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		if(!check_)
			you.PietyUpDown(-2);
		return true;
	case SKL_KANAKO_1:
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_KANAKO_2:
	case SKL_BYAKUREN_2:
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_KANAKO_3:
		if(!check_)
			you.PietyUpDown(-4);
		return true;	
	case SKL_YUYUKO_1:	
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(5)),true);
		return true;	
	case SKL_YUYUKO_2:	
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_YUYUKO_3:	
		if(!check_)
			you.PietyUpDown(-4);
		return true;		
	case SKL_YUKARI_1:
		if(!check_)
			you.PietyUpDown(-2);
		return true;
	case SKL_YUKARI_2:
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_YUKARI_3:
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_YUKARI_4:
		if(!check_)
			you.PietyUpDown(-6);
		return true;		
	case SKL_SWAKO_JUMP:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(5)),true);
		return true;
	case SKL_SWAKO_TEMPLE:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-100,true);
		return true;
	case SKL_SWAKO_WATER_GUN:
		return true;
	case SKL_SWAKO_TOUGUE:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		return true;
	case SKL_SWAKO_CURSE:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(30+randA(20)),true);
			you.PietyUpDown(-3);
		}
		return true;
	case SKL_SWAKO_DIGGING:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(30+randA(20)),true);
			you.PietyUpDown(-3);
		}
		return true;
	case SKL_SWAKO_SUMMON_FLOG:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(30+randA(20)),true);
			you.PietyUpDown(-4);
		}
		return true;
	case SKL_SWAKO_STATUE:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(40+randA(20)),true);
			you.PietyUpDown(-3);
		}
		return true;
	case SKL_SWAKO_RAIN:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-6);
		}
		return true;
	case SKL_SWAKO_SLEEP:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-8);
		}
		return true;
	case SKL_SWAKO_MISYAGUZI:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-6);
		}
		return true;
	case SKL_SHINKI_1:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		if(!check_)
			you.PietyUpDown(-1);
		return true;
	case SKL_SHINKI_2:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(30+randA(20)),true);
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_SHINKI_3:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-5);
		}
		return true;
	case SKL_SIZUHA_2:
		if(check_ && !you.equipment[ET_ARMOR])
		{
			printlog("������ ���� ����Ͽ��� �Ѵ�.",true,false,false,CL_small_danger);	
			return false;
		}
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_SATORI_2:
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_EIRIN_1:
		if(check_ && you.hp <  you.max_hp * 0.1f)
		{
			printlog("�� �Ǵ��� ����ϱ⿣ ü���� �ʹ� ����.",true,false,false,CL_small_danger);	
			return false;
		}
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_EIRIN_2:
		if(check_ && you.hp ==  you.max_hp)
		{
			printlog("�̹� ü���� ���� �� �ִ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PietyUpDown(-15);
		return true;		
	case SKL_YUUGI_1:
		if(!check_)
			you.PietyUpDown(-1);
		return true;
	case SKL_MINORIKO_2:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-6);
		}
		return true;	
	case SKL_YUUGI_2:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(10+randA(5)),true);
			//you.PietyUpDown(-3);
		}
		return true;	
	case SKL_YUUGI_3:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(12+randA(8)),true);
			//you.PietyUpDown(-4);
		}
		return true;	
	case SKL_YUUGI_4:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(20+randA(10)),true);
			you.PietyUpDown(-5);
		}
		return true;	
	case SKL_YUUGI_5:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-10);
		}
		return true;			
	case SKL_HINA_1:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(5)),true);
		return true;
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return true;	
	case SKL_LEVITATION:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(3+randA(5)),true);
		return true;		
	case SKL_INVISIBLE:
		if(check_ && you.power<100)
		{
			printlog("�Ŀ� 1ĭ �̻󿡼� ����Ѵ�.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(8+randA(10)),true);
		return true;
	case SKL_NONE:
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	default:
		return true;
	}
}
void SkillUseTraning(skill_list skill)
{
	//switch(skill)
	//{
	//case SKL_KANAKO_1:
	//case SKL_KANAKO_2:
	//case SKL_KANAKO_3:
	//case SKL_EIRIN_1:
	//case SKL_EIRIN_2:
	//	you.SkillTraining(SKT_INVOCATE,1);
	//	return;		
	//case SKL_BYAKUREN_1:
	//case SKL_BYAKUREN_2:
	//	you.SkillTraining(SKT_ENCHARM,1);
	//	return;		
	//case SKL_GRAZE:
	//case SKL_LEVITATION:
	//case SKL_INVISIBLE:
	//	you.SkillTraining(SKT_EVOCATE,1);
	//	return;		
	//case SKL_NONE:
	//case SKL_GRAZE_OFF:
	//case SKL_LEVITATION_OFF:
	//case SKL_INVISIBLE_OFF:
	//default:
	//	return;
	//}
}
const char* SkillCostString(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
		return "(���� 2, �ž�)";		
	case SKL_MINORIKO_1:
		return "(���� 3, P �ణ, �ž�)";
	case SKL_BYAKUREN_1:
		return "(�ž�)";
	case SKL_YUUGI_1:
		return "(����, �ž�)";
	case SKL_YUUGI_2:
		return "(�ž�, P �ҷ�)";
	case SKL_YUUGI_3:
		return "(�ž�, P �ҷ�)";
	case SKL_YUUGI_4:
		return "(�ž�, P �ణ)";
	case SKL_YUUGI_5:
		return "(�ž�, P �뷮)";
	case SKL_KANAKO_2:
		return "(���� 3, �ž�)";
	case SKL_BYAKUREN_2:
		return "(���� 4, �ž�)";
	case SKL_KANAKO_3:
		return "(���� 4, �ž�)";
	case SKL_EIRIN_0:
		return "(����, P �ణ)";
	case SKL_EIRIN_1:
		return "(����, �ž�)";
	case SKL_EIRIN_2:
		return "(����, ���� 5, �ž�)";	
	case SKL_MINORIKO_2:
		return "(����, ���� 5, P �뷮, �ž�)";	
	case SKL_SIZUHA_1:
		return "(���� 4, �ž�)";
	case SKL_SIZUHA_2:
		return "(�ž�)";
	case SKL_LEVITATION:
		return "(���� 2, P �ҷ�)";
	case SKL_INVISIBLE:
		return "(���� 2, P �ణ)";
	case SKL_SATORI_1:
		return "(���� 2, �ž�)";	
	case SKL_SATORI_2:
		return "(���� 5, �ð�, �ž�)";	
	case SKL_SHINKI_1:
		return "(�ž�, P �ҷ�)";
	case SKL_SHINKI_2:
		return "(�ž�, P �ణ)";
	case SKL_SHINKI_3:
		return "(�ž�, P �뷮)";
	case SKL_YUYUKO_1:
		return "(���� 2, P �ҷ�)";
	case SKL_YUYUKO_2:
		return "(���� 3, �ž�)";
	case SKL_YUYUKO_3:
		return "(���� 5, �ž�)";
	case SKL_YUKARI_1:
		return "(���� 2, �ž�)";
	case SKL_YUKARI_2:
		return "(���� 4, �ž�)";
	case SKL_YUKARI_3:
		return "(���� 3, �ž�)";
	case SKL_YUKARI_4:
		return "(���� 6, �ž�)";
	case SKL_SWAKO_JUMP:
		return "(���� 2, P �ҷ�)";
	case SKL_SWAKO_TEMPLE:
		return "(P �뷮)";
	case SKL_SWAKO_WATER_GUN:
		return "(���� 1)";
	case SKL_SWAKO_TOUGUE:
		return "(���� 2, P �ҷ�)";
	case SKL_SWAKO_CURSE:
		return "(�ž�, P �ణ)";
	case SKL_SWAKO_DIGGING:
		return "(�ž�, P �ణ)";
	case SKL_SWAKO_SUMMON_FLOG:
		return "(�ž�, P �ణ)";
	case SKL_SWAKO_STATUE:
		return "(�ž�, P �ణ)";
	case SKL_SWAKO_RAIN:
		return "(�ž�, P �뷮)";
	case SKL_SWAKO_SLEEP:
		return "(�ž�, P �뷮)";
	case SKL_SWAKO_MISYAGUZI:
		return "(�ž�, P �뷮)";
	case SKL_HINA_1:
		return "(P �ҷ�)";
	case SKL_HINA_2:
		return "(����)";
	case SKL_HINA_3:
		return "(����)";
	case SKL_HINA_4:
		return "(����)";
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_NONE:
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	default:
		return "(����)";
	}
}
int GetSpellBombRange(skill_list skill)
{	
	switch(skill)
	{		
	case SKL_YUUGI_3_THROW:
	case SKL_EIRIN_0:
		return 1;
	default:
		break;
	}
	return 0;
}
int GetSpellBombRange(spell_list spell)
{
	switch(spell)
	{
	case SPL_FIRE_BALL:
	case SPL_CONFUSE_CLOUD:
	case SPL_STONE_TRAP:
	case SPL_STONE_UPLIFT:
		return 1;
	default:
		break;
	}
	return 0;
}



void SkillUse()
{
	if(you.currentSkillNum)
	{	
		int i=0;
		changedisplay(DT_SKILL_USE);
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z'))
			{
				int num = (key_-'a');
				if(skill_list skill_ = (skill_list)you.MemorizeSkill[num])
				{
					if(!GetDisplayMove()) //��ų���
					{
						if(SkillMana(skill_)>you.mp)
						{
							printlog("����� ������ ���ڶ���.",true,false,false,CL_normal);	
							break;
						}
						if(!SkillFlagCheck(skill_, S_FLAG_IMMEDIATELY))
						{
							SetSpellSight(SkillLength(skill_),SkillFlagCheck(skill_, S_FLAG_RECT)?2:1);
							changedisplay(DT_GAME);
							beam_iterator beam(you.position,you.position);
							projectile_infor infor(SkillLength(skill_),false,SkillFlagCheck(skill_, S_FLAG_SMITE),skill_,true);
							if(int short_ = Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor))
							{
								unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
								if(unit_)
									you.youAttack(unit_);
								if(UseSkill(skill_, short_==2, you.search_pos))
								{
									SkillPlusCost(skill_,false);
									if(SkillMana(skill_))
										you.mp -= SkillMana(skill_);
									SkillUseTraning(skill_);
									Noise(you.position , SkillNoise(skill_));
									you.time_delay += you.GetNormalDelay();
									you.TurnEnd();
								}
							}
							SetSpellSight(0,0);
							break;
						}			
						if(SkillFlagCheck(skill_, S_FLAG_IMMEDIATELY))
						{
							changedisplay(DT_GAME);
							if(int succece_ =  UseSkill(skill_, false, you.position))
							{
								if(succece_ != 2)
								{ //2�� ��뿡 �����Ѱ��̴�. ������ �ƴϸ� ��뿡 �����ϸ� �ϸ� �Ҹ�
									SkillPlusCost(skill_,false);
									if(SkillMana(skill_))
										you.mp -= SkillMana(skill_);
								}
								SkillUseTraning(skill_);
								Noise(you.position , SkillNoise(skill_));
								you.time_delay += you.GetNormalDelay();
								you.TurnEnd();
							}		
							break;
						}
					}
					else //������
					{
						WaitForSingleObject(mutx, INFINITE);
						SetText() = GetSkillInfor(skill_);
						changedisplay(DT_TEXT);
						ReleaseMutex(mutx);
						waitkeyinput();
						changedisplay(DT_SKILL_USE);
						changemove(0);
					}
				}
			}
			else if(key_ == '!' || key_ == '?')
			{
				changemove(0);
			}
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
		printlog("���� �˰��ִ� �ɷ��� ����.",true,false,false,CL_normal);	
}