//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: evoke.cpp
//
// ����: �ߵ��۵�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "evoke.h"
#include "skill_use.h"
#include "projectile.h"
#include "environment.h"
#include "throw.h"


const char *evoke_string[EVK_MAX]=
{
	"��ž",
	"����η縶��",
	"��ȥ"
};
const bool evoke_string_is[EVK_MAX]=
{
	true,
	false,
	true
};


void MakeEvokeItem(item_infor* t, int kind_)
{	
	if(kind_ == -1 || (kind_<0 && kind_>=EVK_MAX))
		kind_= randA(EVK_MAX-1);

	t->value1 = kind_;
	t->value2 = 0;
	t->value3 = 0;
	t->value4 = 0;
	t->value5 = 0;
	t->value6 = 0;
	t->is_pile = false;
	t->can_throw = false;
	t->image = &img_mons_default;
	t->name.name = evoke_string[kind_];
	t->name.name_type = evoke_string_is[kind_];
	t->weight = 1.0f;
	t->value = 300;
}






bool EvokeFlagCheck(evoke_kind skill, skill_flag flag);
int EvokeLength(evoke_kind skill);
float EvokeSector(evoke_kind skill);
bool EvokeEvokable(evoke_kind kind, bool short_, coord_def &target);



bool evoke_evokable(evoke_kind kind)
{
	if(you.s_confuse)
	{
		printlog("����� ȥ��������.",true,false,false,CL_normal);
		return false;
	}

	if(you.power < Evokeusepower(kind,true))
	{
		printlog("�ߵ��ϱ⿣ ����� P�� ���ڶ���.",true,false,false,CL_small_danger);	
		return false;
	}



	int i=0;
	if(EvokeFlagCheck(kind, S_FLAG_DIREC))
	{
		SetSpellSight(EvokeLength(kind),EvokeFlagCheck(kind, S_FLAG_RECT)?2:1);
		coord_def target_;
		if(Direc_Throw(&target_))
		{
			if(EvokeEvokable(kind, false, target_))
			{
				you.PowUpDown(-1* Evokeusepower(kind,false),true);
				return true;
			}
		}
		else
		{
			return false;
		}

	}
	else if(!EvokeFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		SetSpellSight(EvokeLength(kind),EvokeFlagCheck(kind, S_FLAG_RECT)?2:1);
		beam_iterator beam(you.position,you.position);
		projectile_infor infor(EvokeLength(kind),false,EvokeFlagCheck(kind, S_FLAG_SMITE),-2,false);
		if(int short_ = Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor, EvokeLength(kind), EvokeSector(kind)))
		{
			unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
			you.SetBattleCount(30);
			if(unit_)
				you.youAttack(unit_);
			if(EvokeEvokable(kind, short_ == 2, you.search_pos))
			{
				you.PowUpDown(-1* Evokeusepower(kind,false),true);
				SetSpellSight(0,0);
				return true;
			}
		}
		else
		{
			SetSpellSight(0,0);
			return false;
		}
	}			
	else if(EvokeFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		if(EvokeEvokable(kind, false, you.position))
		{
			you.PowUpDown(-1* Evokeusepower(kind,false),true);
			return true;
		}
	}
	return false;
}

int Evokeusepower(evoke_kind skill, bool max_)
{
	switch(skill)
	{
	case EVK_PAGODA:
		return 10;
	case EVK_AIR_SCROLL:
		return 50;
	case EVK_DREAM_SOUL:
		return 50;
	default:
		return false;
	}
}


bool EvokeFlagCheck(evoke_kind skill, skill_flag flag)
{
	switch(skill)
	{
	case EVK_PAGODA:
		return (S_FLAG_PENETRATE) & flag;
	case EVK_AIR_SCROLL:
	case EVK_DREAM_SOUL:
		return (S_FLAG_IMMEDIATELY) & flag;
	default:
		return false;
	}
}

int EvokeLength(evoke_kind skill)
{
	switch(skill)
	{
	case EVK_PAGODA:
		return 8;
	case EVK_AIR_SCROLL:
	case EVK_DREAM_SOUL:
		return 0;
	default:
		return false;
	}
}
float EvokeSector(evoke_kind skill)
{
	switch(skill)
	{
	case 0:
	default:
		return 0;
	}
}
string DreamSoulMonster(vector<int>& list_, int level_);



bool EvokeEvokable(evoke_kind kind, bool short_, coord_def &target)
{
	if(target == you.position && !EvokeFlagCheck(kind,S_FLAG_SEIF) && !EvokeFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		printlog("�ڻ��Ұž�?",true,false,false,CL_small_danger);	
		return false;
	}
	int level_ = you.skill[SKT_EVOCATE].level;

	
	switch(kind)
	{
	case EVK_PAGODA:
		{
			beam_iterator beam(you.position,target);
			if(CheckThrowPath(you.position,target,beam)){
				beam_infor temp_infor(randC(3,4+level_*2/3),3*(4+level_*2/3),16,&you,you.GetParentType(),EvokeLength(kind),8,BMT_PENETRATE,ATT_THROW_NORMAL,name_infor("������",false));
				if(short_)
					temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));
				
				for(int i=0;i<(you.GetParadox()?2:1);i++)
					throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
				you.SetParadox(0); 
				return true;
			}
			return false;	
		}	
	case EVK_AIR_SCROLL:
		{
			printlog("����η縶���κ��� ������ �����!",false,false,false,CL_normal);
			you.MpUpDown(8+level_/3+randA(3+level_/3));
			//�ߵ�0 8~11���� �ߵ����� 17~29
			return true;
		}
	case EVK_DREAM_SOUL:
		{
			vector<int> mon_list;
			string s_ =	DreamSoulMonster(mon_list,level_);
			for(auto it = mon_list.begin(); it != mon_list.end(); it++)
			{
				if(BaseSummon((*it), rand_int(50,60), true, false, 2, &you, you.position, SKD_OTHER, -1))
				{

				}
			}
			printarray(true,false,false,CL_normal,3,"����� ",s_.c_str(),"�� ���� �ҷ��´�!");
			return true;
		}
	}
	return false;
}






string DreamSoulMonster(vector<int>& list_, int level_)
{
	random_extraction<int> branch_list_;
	string msg_;
	if(level_>=0)
		branch_list_.push(0);//����
	if(level_>=0)
		branch_list_.push(1);//�䱫�ǻ�
	if(level_>=6)
		branch_list_.push(2);//ȫ����
	if(level_>=0)
		branch_list_.push(3);//����
	if(level_>=0)
		branch_list_.push(4);//�̱����׸�
	if(level_>=0)
		branch_list_.push(5);//����
	if(level_>=6)
		branch_list_.push(6);//����

	int branch_ = branch_list_.pop();


	random_extraction<int> mon_list_;

	int num_ = rand_int(1,3)+randA(level_/13);

	if(num_ == 1)
		level_ = min(27,level_ + 5);


	switch(branch_)
	{
	case 0: //����
		if(level_<=3)
			mon_list_.push(MON_FAIRY_GREEN,4);
		if(level_<=5)
			mon_list_.push(MON_FAIRY_BLUE,9);
		if(level_<=7)
			mon_list_.push(MON_FAIRY_RED,15);
		if(level_>5 && level_<=15)
			mon_list_.push(MON_FAIRY_GREEN_WARRIOR,15);
		if(level_>7 && level_<=18)
			mon_list_.push(MON_FAIRY_BLUE_MAGICIAN,10);
		if(level_>9 && level_<=21)
			mon_list_.push(MON_FAIRY_RED_COMMANDER,5);
		if(level_>15)
			mon_list_.push(MON_FAIRY_HERO,15);
		if(level_>18)
			mon_list_.push(MON_FAIRY_SOCERER,15);
		if(level_>21)
			mon_list_.push(MON_FAIRY_SUN_FLOWER,5);
		msg_ = "�Ȱ��� ȣ��";
		break;
	case 1: //�䱫��
		if(level_<=6)
			mon_list_.push(MON_CROW,6);
		if(level_<=13)
			mon_list_.push(MON_KATPA,18);
		if(level_>6 && level_<=15)
			mon_list_.push(MON_FROG,6);
		if(level_>9 && level_<=25)
			mon_list_.push(MON_KATPA_SPEAR,10);
		if(level_>11)
			mon_list_.push(MON_CROW_TENGU,15);
		if(level_>13)
			mon_list_.push(MON_KATPA_WATER_WIZARD,7);
		if(level_>15)
			mon_list_.push(MON_YAMABUSH_TENGU,10);
		if(level_>18)
			mon_list_.push(MON_HANATACA_TENGU,10);
		if(level_>21)
			mon_list_.push(MON_SANPEI_FIGHTER,3);
		msg_ = "�䱫�� ��";
		break;
	case 2: //ȫ����
		if(level_<=13)
			mon_list_.push(MON_HOBGOBRIN,15);
		if(level_<=16)
			mon_list_.push(MON_MAID_FAIRY,8);
		if(level_>9 && level_<=19)
			mon_list_.push(MON_HOBGOBRIN_MAID,10);
		if(level_>13 && level_<=24)
			mon_list_.push(MON_MAGIC_BOOK,8);
		if(level_>16)
			mon_list_.push(MON_HOBGOBRIN_LIBRARIAN,6);
		if(level_>18)
			mon_list_.push(MON_VAMPIER_BAT,10);			
		if(level_>21)
			mon_list_.push(MON_CHUPARCABRA,3);
		msg_ = "ȫ����";
		break;
	case 3: //����
		if(level_<=9)
			mon_list_.push(MON_REIMUYUKKURI,15);
		if(level_<=16)
			mon_list_.push(MON_MARISAYUKKURI,10);
		if(level_>9 && level_<=24)
			mon_list_.push(MON_AYAYUKKURI,8);
		if(level_>16)
			mon_list_.push(MON_REMILIAYUKKURI,6);
		if(level_>19)
			mon_list_.push(MON_YOUMUYUKKURI,2);
		if(level_>21)
			mon_list_.push(MON_ALICEYUKKURI,2);
		msg_ = "���� ����";
		break;
	case 4: //�׸�
		if(level_<=12)
			mon_list_.push(MON_RABBIT,10);
		if(level_>6)
			mon_list_.push(MON_RABIT_SPEAR,5);
		if(level_>9)
			mon_list_.push(MON_RABIT_SPEAR,15);
		if(level_>12)
			mon_list_.push(MON_RABIT_SUPPORT,3);
		if(level_>15)
			mon_list_.push(MON_RABIT_MAGIC,10);
		msg_ = "�̱��� �׸�";
		break;
	case 5: //����
		if(level_<=8)
			mon_list_.push(MON_CROW,6);
		if(level_<=13)
			mon_list_.push(MON_HAUNT,10);
		if(level_>8 && level_<=15)
			mon_list_.push(randA(2)?(randA(1)?MON_WHITE_CAT:MON_BLACK_CAT):MON_ORANGE_CAT,10);
		if(level_>11 && level_<=18)
			mon_list_.push(MON_HELL_CROW,10);
		if(level_>14)
			mon_list_.push(MON_BLOOD_HAUNT,5);
		if(level_>15)
			mon_list_.push(MON_HELL_SPIDER, 10);
		if(level_>18)
			mon_list_.push(randA(1)?MON_ONI:MON_BLUE_ONI,8);
		if(level_>24)
			mon_list_.push(MON_FIRE_CAR,3);				
		msg_ = "����";
		break;
	case 6: //����
		if(level_<=12)
			mon_list_.push(MON_EVIL_EYE,10);
		if(level_<=10)
			mon_list_.push(MON_LITTLE_IMP,10);
		if(level_>8)				
			mon_list_.push(MON_SARA,15);
		if(level_>12)		
			mon_list_.push(MON_LUIZE,15);
		if(level_>13)		
			mon_list_.push(MON_ELIS,15);
		if(level_>21)		
			mon_list_.push(MON_YUKI,1);
		if(level_>21)
			mon_list_.push(MON_MAI,1);	
		if(level_>23)		
			mon_list_.push(MON_YUKI,3);
		if(level_>23)
			mon_list_.push(MON_MAI,3);		
		msg_ = "����";
		break;
	}


	
	for(int i = num_; i > 0; i--)
		list_.push_back(mon_list_.choice());
	return msg_;
}