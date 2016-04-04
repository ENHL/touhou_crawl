//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: wiz.cpp
//
// ����: ���ڵ���!!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "smoke.h"
#include "key.h"
#include "mon_infor.h"

#include "spellcard.h"
#include "skill_use.h"

bool wizard_mode = false;


bool skill_summon_bug(int pow, bool short_, unit* order, coord_def target);

void wiz_mode()
{
	printlog("<���ڵ���> ��� ��ɾ�?",true,false,false,CL_help);
	wizard_mode = true;
	int key_ = waitkeyinput();
	switch(key_)
	{
	case 'D': //�ʹ�����
		for(int i = 0;i<DG_MAX_X;i++)
			for(int j = 0;j<DG_MAX_Y;j++)
				env[current_level].dgtile[i][j].flag = env[current_level].dgtile[i][j].flag | FLAG_MAPPING;
		break;
	case 'f': //����
		//for(int i = -1;i<2;i++)
		//	for(int j = -1;j<2;j++)
		//		env[current_level].MakeSmoke(coord_def(i+you.position.x,j+you.position.y),img_fog_fire,SMT_NORMAL,10,0,&you);
		MakeCloud(you.position, img_fog_fire, SMT_FIRE, rand_int(8,10), rand_int(8,12), 0,5, &you);
		break;
	case 'A':
		{
			item_infor t;
			makeitem(ITM_RING, 0, &t, RGT_GRAZE);
			makeitem(ITM_RING, 0, &t, RGT_GRAZE);	
			env[current_level].MakeItem(you.position,t);

			break;
		}
	case 'H':
		you.HpUpDown(you.max_hp,DR_EFFECT);
		you.MpUpDown(you.max_mp);
		you.PowUpDown(500,true);
		break;
	case 'X':
		you.GetExp(you.GetNeedExp(you.level-1) - you.exper);
		break;
	case '>': //������ �̵�
		if(!environment::isLastFloor(current_level))
		{
			deque<monster*> dq;
			env[current_level+1].EnterMap(0,dq);
			you.resetLOS(false);
		}
		break;
	case '<': //������ �̵�	
		if(!environment::isFirstFloor(current_level))
		{
			deque<monster*> dq;
			env[current_level-1].EnterMap(0,dq);
			you.resetLOS(false);
		}
		break;
	case 'G': //�����̵�	
		{
		deque<monster*> dq;
		dungeon_level next_ = TEMPLE_LEVEL;
		printlog("��� �������� �̵��غ���?",true,false,false,CL_help);
		printlog("T - ����      L - �Ȱ��� ȣ��     M - �䱫�� ��     S - ȫ����",true,false,false,CL_help);
		printlog("B - ȫ����������  U - ȫ��������   A - �̱����׸�  E - ������ ",true,false,false,CL_help);
		printlog("H - ������",true,false,false,CL_help);
		printlog("��� �������� �̵��غ���?",true,false,false,CL_help);
		wizard_mode = true;
		key_ = waitkeyinput();
		switch(key_)
		{
			case 't':
			case 'T':
				next_ = TEMPLE_LEVEL;
				break;
			case 'l':
			case 'L':
				next_ = MISTY_LAKE_LEVEL;
				break;
			case 'm':
				next_ = YOUKAI_MOUNTAIN_LEVEL;
				break;
			case 'M':
				next_ = YOUKAI_MOUNTAIN_LAST_LEVEL;
				break;
			case 's':
				next_ = SCARLET_LEVEL;
				break;
			case 'S':
				next_ = SCARLET_LEVEL_LAST_LEVEL;
				break;
			case 'b':					
			case 'B':
				next_ = SCARLET_LIBRARY_LEVEL;
				break;	
			case 'u':		
			case 'U':
				next_ = SCARLET_UNDER_LEVEL;
				break;
			case 'a':			
			case 'A':					
				next_ = BAMBOO_LEVEL;
				break;
			case 'e':			
			case 'E':					
				next_ = EIENTEI_LEVEL;
				break;
			case 'h':			
			case 'H':
				next_ = SUBTERRANEAN_LEVEL;
				break;
			default:
				return;
		}
		env[next_].EnterMap(0,dq);
		printlog("����� �����Դ�.",true,false,false,CL_normal);
		you.resetLOS(false);
		break;
		}
	case 'b':
		you.Blink(40);
		break;
	case 's':
		skill_summon_bug(10,false,&you,you.position);		
		//evoke_spellcard(SPC_V_NORMAL_INVISIBLE, 50+you.level*5);
		break;
	case 'w':
		//skill_summon_bug(100,&you,you.position);		
		you.SetBuff((stat_up)rand_int(BUFFSTAT_STR,BUFFSTAT_EV),BUFF_DUPLE,rand_int(-3,3),10);
		break;
	case 'p':
		env[current_level].dgtile[you.position.x][you.position.y].tile = (dungeon_tile_type) rand_int(DG_TEMPLE_FIRST,DG_TEMPLE_LAST);
		break;
	case 'M':
		if(monster* mon_=BaseSummon(MON_KOISHI, 100, true, false, 2, &you, you.position, SKD_OTHER, -1))
		{
			mon_->flag &= ~M_FLAG_SUMMON;
			mon_->ReturnEnemy();
		}
		break;
	case '^':
		you.PietyUpDown(10);
		you.GiftCount(10);
		break;
	default:
		printlog("���� ��ɾ�",true,false,false,CL_help);
		break;
	}

}