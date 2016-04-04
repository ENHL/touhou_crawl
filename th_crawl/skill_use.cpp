//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: skill_use.cpp
//
// ����: ����ϴ� ��ų��
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "unit.h"
#include "skill_use.h"
#include "throw.h"
#include "beam.h"
#include "monster.h"
#include "smoke.h"
#include "mon_infor.h"
#include "rect.h"
#include "player.h"
#include "monster_texture.h"
#include "weapon.h"
#include "environment.h"
#include "key.h"
#include "floor.h"
#include "debuf.h"
#include "potion.h"
#include "throw.h"
#include "projectile.h"
#include "event.h"


extern HANDLE mutx;

bool skill_kanako_might(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		monster* unit_ = (monster*)env[current_level].isMonsterPos(target.x,target.y, &you);
		if(!unit_ || unit_->isUserAlly())
		{
			printlog("�� ���͸� ������� ����Ѵ�.",true,false,false,CL_normal);	
			return false; //�ش� ��ġ�� ���Ͱ� ����.
		}

		beam_iterator beam(order->position,order->position);
		if(CheckThrowPath(order->position,target,beam))
		{
			beam.init();
			
			if(beam.GetMaxLength() == 1 || env[current_level].isMonsterPos(beam->x,beam->y, &you))
			{				
				printlog("�� ���� ��뿡�� ������ �� ����.",true,false,false,CL_normal);	
				return false;
			}
			while(!beam.end())
			{
				beam_iterator temp = beam;
				temp++;
				unit *unit_ = env[current_level].isMonsterPos(temp->x,temp->y, &you);
				if(temp.end() || unit_)
				{
					if(!env[current_level].dgtile[beam->x][beam->y].isMove(you.isFly(),you.isSwim(),false))
					{
						printlog("�ش� ��ġ�� ������ �� ����.",true,false,false,CL_normal);	
						return false;
					}
					you.SetXY(beam->x,beam->y);

					float multy_ = 1.0f; //�⵵��, �Ÿ� ����ؼ� �������� ����.
					multy_*=(9.0f+temp.GetCurLength())/9; //�Ÿ��� 6�������� 1.66�� �������� �ش�.
					//multy_*=(13.0f+pow/5)/13;

					attack_infor temp_att(you.GetAttack(false)*multy_,you.GetAttack(true),you.GetHit()+10,&you,you.GetParentType(),ATT_RUSH,name_infor("����",true));
					unit_->damage(temp_att,false);
					printlog("������ �����ߴ�!",true,false,false,CL_normal);	
					return true;
				}
				beam++;
			}
			printlog("������ �� ����.",true,false,false,CL_normal);
			return false;
		}
		//���̻� ����Ʈ�� �ƴϴ�! ���� �������� �����Ѵ�.
		//you.SetMight(20+randA_1(pow*5));
		printlog("���̿� ��ֹ��� �ִ�.",true,false,false,CL_normal);	
		return false;
	}
	return false;
}


bool skill_kanako_2(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(BaseSummon(MON_ONBASIRA, 20+randA_1(pow), true, false, 0, order, target, SKD_SUMMON_ONBASIRA, -1))
			return true;
		else
			printlog("������ �� ���� ��ġ�Դϴ�.",true,false,false,CL_normal);	

	}
	return false;
}

bool skill_kanako_haste(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		you.SetWind(50+randA_1(pow));
	}
	return true;
}
bool skill_turn_graze(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer() && !you.s_graze)
	{
		you.SetGraze(-1/*rand_int(15,25)+pow/2*/);
		int temp = you.Ability(SKL_GRAZE,false,true,1);
		you.Ability(SKL_GRAZE_OFF,false,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_graze)
		printlog("�̹� �׷�����߿� ����� �� ����.",true,false,false,CL_normal);	

	return false;
}
bool skill_off_graze(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("�׷���� �����.",true,false,false,CL_normal);
		you.s_graze = 0;
		int temp = you.Ability(SKL_GRAZE_OFF,false,true,1);
		you.Ability(SKL_GRAZE,false,false,temp);
		return true;
	}
	return false;
}
bool skill_turn_levitation(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer() && !you.s_levitation)
	{
		you.SetLevitation(rand_int(15,25)+pow/2);
		int temp = you.Ability(SKL_LEVITATION,false,true,1);
		you.Ability(SKL_LEVITATION_OFF,false,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_levitation)
		printlog("�̹� �������߿� ����� �� ����.",true,false,false,CL_normal);	

	return false;
}
bool skill_off_levitation(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("������ �����.",true,false,false,CL_normal);
		you.s_levitation = 0;
		int temp = you.Ability(SKL_LEVITATION_OFF,false,true,1);
		you.Ability(SKL_LEVITATION,false,false,temp);
		return true;
	}
	return false;
}
bool skill_turn_invisible(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer() && !you.s_invisible)
	{
		you.SetInvisible(rand_int(15,25)+pow/2);
		int temp = you.Ability(SKL_INVISIBLE,false,true,1);
		you.Ability(SKL_INVISIBLE_OFF,false,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_invisible)
		printlog("�̹� ������ ���߿� ����� �� ����.",true,false,false,CL_normal);	

	return false;
}
bool skill_off_invisible(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("�ٽ� ���̱� �����ߴ�.",true,false,false,CL_normal);
		you.s_invisible = 0;
		int temp = you.Ability(SKL_INVISIBLE_OFF,false,true,1);
		you.Ability(SKL_INVISIBLE,false,false,temp);
		return true;
	}
	return false;
}

bool skill_soul_shot(int power, unit* order, coord_def target)
{
	for(int i=-2;i<=2;i++)
		for(int j=-2;j<=2;j++)
			if(abs(i)+abs(j)<4 && env[current_level].isMove(order->position.x+i,order->position.y+j,true))
				env[current_level].MakeEffect(coord_def(order->position.x+i,order->position.y+j),&img_fog_slow[0],false);
	for(int i=-2;i<=2;i++)
	{
		for(int j=-2;j<=2;j++)
		{				
			if(abs(i)+abs(j)<4 && (env[current_level].isInSight(order->position+i)) && env[current_level].isMove(order->position.x+i,order->position.y+j,true))
			{
				if(unit* hit_ = env[current_level].isMonsterPos(order->position.x+i,order->position.y+j))
				{
					if(hit_ != order)
						hit_->SetParalyse(rand_int(5,10));
				}
			}
		}
	}
	Sleep(300);
	env[current_level].ClearEffect();

	return false;
}
bool skill_eirin_throw_potion(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SpellLength(SPL_FIRE_BALL));
	if(CheckThrowPath(order->position,target,beam))
	{
		view_item(IVT_POTION,"������ �����ڽ��ϱ�?");
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				changedisplay(DT_GAME);
				list<item>::iterator it;
				for(it = you.item_list.begin(); it != you.item_list.end();it++)
				{
					if((*it).id == key_)
					{
						if((*it).type == ITM_POTION)
						{				
							textures *t_ = img_fog_normal;
							smoke_type smoke_ = SMT_FOG;

							switch((*it).value1)
							{
							case PT_POISON:
								t_ = img_fog_poison;
								smoke_ = SMT_POISON;
								break;
							case PT_CONFUSE:
								t_ = img_fog_poison;
								smoke_ = SMT_CONFUSE;
								break;
							case PT_SLOW:
								t_ = img_fog_slow;
								smoke_ = SMT_SLOW;
								break;
							case PT_DOWN_STAT:
								t_ = img_fog_cold;
								smoke_ = SMT_COLD;
								break;
							case PT_PARALYSIS:
								t_ = img_fog_fire;
								smoke_ = SMT_FIRE;
								break;
							}
							beam_infor temp_infor(randA(power/10),randA(power/10),10,order,order->GetParentType(),length_,1,BMT_PENETRATE,ATT_THROW_NONE_MASSAGE,name_infor("����",true));
							coord_def pos = throwtanmac(27,beam,temp_infor,NULL, false);
							{
								for(int i=-1;i<=1;i++)
									for(int j=-1;j<=1;j++)
										if(env[current_level].isMove(pos.x+i,pos.y+j,true))
											env[current_level].MakeEffect(coord_def(pos.x+i,pos.y+j),t_,false);
								for(int i=-1;i<=1;i++)
									for(int j=-1;j<=1;j++)
											env[current_level].MakeSmoke(coord_def(pos.x+i,pos.y+j),t_,smoke_,rand_int(7+power/8,20+power/8),0,&you);
								Sleep(300);
								env[current_level].ClearEffect();

							}
							you.DeleteItem(it,1);
							return true;	

						}
						else
						{
							printlog("�װ��� ������ �ƴϴ�.",true,false,false,CL_normal);
							return false;	
						}
					}
				}
				printlog("�������� �ʴ� ������.",true,false,false,CL_normal);
				return false;	
			}
			else if(key_ == VK_DOWN)//-----�̵�Ű-------
			{
				changemove(32);  //��
			}
			else if(key_ == VK_UP)
			{
				changemove(-32); //�Ʒ�
			}
			else if(key_ == VK_PRIOR)
			{
				changemove(-WindowHeight);
			}
			else if(key_ == VK_NEXT)
			{
				changemove(WindowHeight);
			}						//-----�̵�Ű��-------
			else if(key_ == '*')
				view_item(IVT_SELECT,"������ �����ڽ��ϱ�?");
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
		return false;
	}
	return false;
}

bool skill_eirin_move_stat(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		bool end_ = false;
		stat_type prev = STAT_STR, next = STAT_STR;
		//��𼭺���
		printlog("���̰� ���� ������ ������. (S)tr - ��  (D)ex - ��ø  (I)nt - ���� ",false,false,false,CL_help);
		while(!end_)
		{
			switch(waitkeyinput())
			{
			case 'S':
				prev= STAT_STR;
				printlog("==> ��",true,false,false,CL_help);
				end_ = true;
				break;
			case 'D':
				prev= STAT_DEX;
				printlog("==> ��ø",true,false,false,CL_help);
				end_ = true;
				break;
			case 'I':
				prev= STAT_INT;
				printlog("==> ����",true,false,false,CL_help);
				end_ = true;
				break;
			case VK_ESCAPE:
				enterlog();
				printlog("����Ͽ���. �����ϰ� �����ϵ���!",true,false,false,CL_help);
				return false;
			}
		}
		end_ = false;
		//�״��� ����?
		printlog("��� �������� �ű�ϱ�?",false,false,false,CL_help);
		if(prev != STAT_STR)
			printlog(" (S)tr - �� ",false,false,false,CL_help);
		if(prev != STAT_DEX)
			printlog(" (D)ex - ��ø ",false,false,false,CL_help);
		if(prev != STAT_INT)
			printlog(" (I)nt - ���� ",false,false,false,CL_help);
		while(!end_)
		{
			switch(waitkeyinput())
			{
			case 'S':
				if(prev != STAT_STR)
				{
					next = STAT_STR;
					end_ = true;
					printlog("==> ��",true,false,false,CL_help);
				}
				break;
			case 'D':
				if(prev != STAT_DEX)
				{
					next = STAT_DEX;
					end_ = true;
					printlog("==> ��ø",true,false,false,CL_help);
				}
				break;
			case 'I':
				if(prev != STAT_INT)
				{
					next = STAT_INT;
					end_ = true;
					printlog("==> ����",true,false,false,CL_help);
				}
				break;
			case VK_ESCAPE:
				enterlog();
				printlog("����Ͽ���. �����ϰ� �����ϵ���!",true,false,false,CL_help);
				return false;
			}
		}
		you.StatUpDown(-1,prev);
		you.StatUpDown(1,next);
		printarray(false,false,false,CL_good,4,prev==STAT_STR?"��":(prev==STAT_DEX?"��ø":"����"),"���� ",next==STAT_STR?"��":(next==STAT_DEX?"��ø":"����"),"���� ������ ��������. ");
		printlog("���ۿ��� ������.",true,false,false,CL_small_danger);
		int damage = rand_int(10,40);
		if(damage >= you.hp)
			damage = you.hp-1;
		you.HpUpDown(-damage,DR_EFFECT);
		randA(2)?(randA(1)?you.StatUpDown(-1,STAT_STR,true):you.StatUpDown(-1,STAT_DEX,true)):you.StatUpDown(-1,STAT_INT,true);
		for(int i=0;i<3;i++)				
			if(!randA(2))
				randA(2)?(randA(1)?you.StatUpDown(-1,STAT_STR,true):you.StatUpDown(-1,STAT_DEX,true)):you.StatUpDown(-1,STAT_INT,true);
	}
	return true;
}

bool skill_eirin_heal(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("����� �Ϻ��ϰ� ����Ǿ���! �� ���ۿ����� �ִ�ü�°� �ִ븶���� �پ�����.",false,false,false,CL_help);
		you.max_hp -= you.max_hp * rand_int(2,11-pow/15)/100;
		you.max_mp -= rand_int(1,3-pow/50);
		you.HpUpDown(you.max_hp,DR_EFFECT);
		you.MpUpDown(you.max_mp);
	}
	return true;
}


bool skill_byakuren_smart(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		int time_ = rand_int(10+randA_1(pow/10),20+randA_1(pow/10));
		you.SetClever(time_);
		you.SetManaRegen(time_);
	}
	return true;
}


bool skill_byakuren_leg(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		int time_ = rand_int(15,15+pow/5);
		you.SetSuperMan(time_);
	}
	return true;
}
bool skill_sizuha_confuse(int pow, bool short_, unit* order, coord_def target)
{
	int number_ = 0;
	for(auto it = env[current_level].floor_list.begin(); it!= env[current_level].floor_list.end(); it++)
	{
		if(it->type == FLOORT_AUTUMN && it->parent == PRT_PLAYER)
		{
			unit* unit_ = env[current_level].isMonsterPos(it->position.x,it->position.y,&you);
			
			if(unit_ && !unit_->isUserAlly())
			{
				if(unit_->CalcuateMR(GetDebufPower(SKL_SIZUHA_1, pow)))
				{
					unit_->SetConfuse(rand_int(5,15)+randA(pow/20));
				}
				else if(unit_->isYourShight())
				{					
					printarray(true,false,false,CL_normal,3,unit_->GetName()->name.c_str(),unit_->GetName()->name_is(true),"�����ߴ�.");
				}
				number_++;
			}
		}
	}
	if(!number_)
	{
		printlog("�þ߾� ��ǳ���� �ִ� ���� ����.",true,false,false,CL_normal);
		return false;
	}
	return true;

}
bool skill_sizuha_autumn_armour(int pow, bool short_, unit* order, coord_def target)
{
	if(you.equipment[ET_ARMOR])
	{
		if(you.equipment[ET_ARMOR]->isArtifact())
		{
			printlog("��Ƽ��Ʈ�� ��ȭ�� �� ����.",true,false,false,CL_normal);
			return false;
		}
		if(!strncmp(you.equipment[ET_ARMOR]->name.name.c_str(),"��ǳ",4))
		{
			printlog("����� �̹� ��ǳ ���� ���� �ִ�.",true,false,false,CL_normal);
			return false;
		}
		switch(you.equipment[ET_ARMOR]->type)
		{
		case ITM_ARMOR_BODY_ROBE:
			printarray(true,false,true,CL_help,3,you.equipment[ET_ARMOR]->name.name.c_str(),you.equipment[ET_ARMOR]->name.name_to(true),"��ǳ���� ��ȭ�Ͻðڽ��ϱ�? ȭ���� �������ϴ�! (y/n)");
			printlog("(��ǳ���� ��ȭ�� ��� +2, ���к��ʽ� ���� ����)",true,false,true,CL_help);
			break;
		case ITM_ARMOR_BODY_ARMOUR_0:
			printarray(true,false,true,CL_help,3,you.equipment[ET_ARMOR]->name.name.c_str(),you.equipment[ET_ARMOR]->name.name_to(true),"��ǳ���� ��ȭ�Ͻðڽ��ϱ�? ȭ���� �������ϴ�! (y/n)");
			printlog("(��ǳ���� ��ȭ�� ��� +2, �����г�Ƽ -1, ���к��ʽ� ����)",true,false,true,CL_help);
			break; 
		case ITM_ARMOR_BODY_ARMOUR_1:
			printarray(true,false,true,CL_help,3,you.equipment[ET_ARMOR]->name.name.c_str(),you.equipment[ET_ARMOR]->name.name_to(true),"��ǳ���� ��ȭ�Ͻðڽ��ϱ�? ȭ���� �������ϴ�! (y/n)");
			printlog("(��ǳ���� ��ȭ�� ��� +2, �����г�Ƽ -1, �ּҰ����г�Ƽ -1, ���к��ʽ� �߰�)",true,false,true,CL_help);
			break;
		case ITM_ARMOR_BODY_ARMOUR_2:
			printarray(true,false,true,CL_help,3,you.equipment[ET_ARMOR]->name.name.c_str(),you.equipment[ET_ARMOR]->name.name_to(true),"��ǳ���� ��ȭ�Ͻðڽ��ϱ�? ȭ���� �������ϴ�! (y/n)");
			printlog("(��ǳ���� ��ȭ�� ��� +3, �����г�Ƽ -2, �ּҰ����г�Ƽ -2, ���к��ʽ� ����)",true,false,true,CL_help);
			break;
		case ITM_ARMOR_BODY_ARMOUR_3:
			printarray(true,false,true,CL_help,3,you.equipment[ET_ARMOR]->name.name.c_str(),you.equipment[ET_ARMOR]->name.name_to(true),"��ǳ���� ��ȭ�Ͻðڽ��ϱ�? ȭ���� �������ϴ�! (y/n)");
			printlog("(��ǳ���� ��ȭ�� ��� +3, �����г�Ƽ -4, �ּҰ����г�Ƽ -2. ���к��ʽ� �̷�)",true,false,true,CL_help);
			break;
		}
		
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			break;
		default:
			printlog("����Ͽ���. �����ϰ� �����ϵ���!",true,false,false,CL_help);
			return false;
		}

		you.equipment[ET_ARMOR]->name.name = "��ǳ "+you.equipment[ET_ARMOR]->name.name;

		
		


		switch(you.equipment[ET_ARMOR]->type)
		{
		case ITM_ARMOR_BODY_ROBE:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[0];			
			you.equipment[ET_ARMOR]->value1+=2;		
			you.equipment[ET_ARMOR]->value2-=0;	
			you.equipment[ET_ARMOR]->value3-=0;//3,0,0
			break;
		case ITM_ARMOR_BODY_ARMOUR_0:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[1];			
			you.equipment[ET_ARMOR]->value1+=2;	
			you.equipment[ET_ARMOR]->value2+=1;	
			you.equipment[ET_ARMOR]->value3+=0;//5,-1,0
			break; 
		case ITM_ARMOR_BODY_ARMOUR_1:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[2];			
			you.equipment[ET_ARMOR]->value1+=2;
			you.equipment[ET_ARMOR]->value2+=1;	
			you.equipment[ET_ARMOR]->value3+=1;//8,-3,0
			break;
		case ITM_ARMOR_BODY_ARMOUR_2:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[3];			
			you.equipment[ET_ARMOR]->value1+=3;
			you.equipment[ET_ARMOR]->value2+=2;	
			you.equipment[ET_ARMOR]->value3+=2;//12,-5,-1
			break;
		case ITM_ARMOR_BODY_ARMOUR_3:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[4];			
			you.equipment[ET_ARMOR]->value1+=3;
			you.equipment[ET_ARMOR]->value2+=4;	
			you.equipment[ET_ARMOR]->value3+=2;//15,-7,-2
			break;
		}
		you.ReSetASPanlty();
		you.ResistUpDown(-1,RST_FIRE);
		printlog("����� ���� Ŀ�ٶ� ��ǳ������ ���ߴ�!",true,false,false,CL_normal);
	}
	else
	{
		printlog("����� ���� ���� ���� �ʴ�.",true,false,false,CL_normal);
		return false;
	}
	return true;
}
	
bool skill_minoriko_restore(int pow, bool short_, unit* order, coord_def target)
{
	{
		bool up_ = false;
		
		if(you.s_confuse)
		{
			you.s_confuse = 0;
			up_ = true;
		}
		if(you.s_poison)
		{
			you.s_poison = 0;
			up_ = true;
		}
		if(you.s_sick)
		{
			you.s_sick = 0;
			up_ = true;
		}
		if(you.s_frozen)
		{
			you.s_frozen = 0;
			up_ = true;
		}
		if(you.s_glow)
		{
			you.s_glow = 0;
			up_ = true;
		}
		if(you.s_slow)
		{
			you.s_slow = 0;
			up_ = true;
		}


		if(you.s_str != you.m_str)
		{
			you.StatUpDown(you.m_str-you.s_str,STAT_STR,true);
			up_ = true;
		}
		if(you.s_dex != you.m_dex)
		{
			you.StatUpDown(you.m_dex-you.s_dex,STAT_DEX,true);
			up_ = true;
		}
		if(you.s_int != you.m_int)
		{
			you.StatUpDown(you.m_int-you.s_int,STAT_INT,true);
			up_ = true;
		}
		if(up_)
		{
			printlog("����� ���¸� ȸ���Ͽ���.",true,false,false,CL_white_blue);
			return true;
		}
		else{
			printlog("����� ȸ���� ���°� ����.",true,false,false,CL_normal);
			return false;	
		}

	}
	return false;

}
	
bool skill_minoriko_heal(int pow, bool short_, unit* order, coord_def target)
{		
	view_item(IVT_FOOD,"������ ����ϰڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			list<item>::iterator it;
			for(it = you.item_list.begin(); it != you.item_list.end();it++)
			{
				if((*it).id == key_)
				{
					if((*it).type == ITM_FOOD)
					{						
						int bonus_ = (*it).value5 / 10;
						order->HpUpDown(rand_int(10+bonus_,15+bonus_)+order->GetMaxHp()*rand_float(0.15f,0.25f),DR_NONE);
						you.DeleteItem(it,1);
						printlog("������ ���� ü���� ȸ���Ͽ���.",true,false,false,CL_white_blue);
						return true;	
					}
					else
					{
						printlog("�װ��� ������ �ƴϴ�.",true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog("�������� �ʴ� ������.",true,false,false,CL_normal);
			return false;	
		}
		else if(key_ == VK_DOWN)//-----�̵�Ű-------
		{
			changemove(32);  //��
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //�Ʒ�
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----�̵�Ű��-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"������ ����Ͻðڽ��ϱ�?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}

bool skill_yuugi_drink(int pow, bool short_, unit* order, coord_def target)
{
	{
		view_item(IVT_POTION,"������ ����ϰڽ��ϱ�?");
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				changedisplay(DT_GAME);
				list<item>::iterator it;
				for(it = you.item_list.begin(); it != you.item_list.end();it++)
				{
					if((*it).id == key_)
					{
						if((*it).type == ITM_POTION)
						{	
							drinkpotion(PT_ALCOHOL);	
							you.DeleteItem(it,1);
							return true;	

						}
						else
						{
							printlog("�װ��� ������ �ƴϴ�.",true,false,false,CL_normal);
							return false;	
						}
					}
				}
				printlog("�������� �ʴ� ������.",true,false,false,CL_normal);
				return false;	
			}
			else if(key_ == VK_DOWN)//-----�̵�Ű-------
			{
				changemove(32);  //��
			}
			else if(key_ == VK_UP)
			{
				changemove(-32); //�Ʒ�
			}
			else if(key_ == VK_PRIOR)
			{
				changemove(-WindowHeight);
			}
			else if(key_ == VK_NEXT)
			{
				changemove(WindowHeight);
			}						//-----�̵�Ű��-------
			else if(key_ == '*')
				view_item(IVT_SELECT,"������ ����ϰڽ��ϱ�?");
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
		return false;
	}
	return false;
}
bool skill_yuugi_german(int pow, bool short_, unit* order, coord_def target)
{
	unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
	if(unit_&& order->isplayer() && !unit_->isplayer())
	{
		monster* mon_ = (monster*)unit_;
		bool no_cost_ = (you.s_catch && mon_->s_catch);
		if(you.isEnemyMonster(mon_))
		{
			coord_def offset_ = you.position+you.position - mon_->position;
			if(!env[current_level].isMove(offset_))
			{
				printlog("������ ���� ���÷����� �� ������ �����ϴ�.",true,false,false,CL_normal);
				return false;	
			}
			if(!env[current_level].isMonsterPos(target.x,target.y,order))
			{
				printlog("���� ���÷����� ���µ� ���صǴ� �������� �ִ�.",true,false,false,CL_normal);
				return false;	
			}
			mon_->SetXY(offset_);
			int damage_ = you.GetAttack(false)*10/you.GetAtkDelay()*(1+pow/100.0f)+randC(2,2+pow/20);
			int max_damage_ = you.GetAttack(true)*10/you.GetAtkDelay()*(1+pow/100.0f)+2*(2+pow/20);				
			
			printlog("���� ���÷���! ",false,false,false,CL_yuigi);
			attack_infor temp_att(damage_,max_damage_,99,&you,you.GetParentType(),ATT_NORMAL_HIT,name_infor("���� ���÷���",false));
			unit_->damage(temp_att,true);

			if(!no_cost_)
				you.PietyUpDown(-4);
			return true;
		}
	}
	return false;
}
bool skill_yuugi_throw(int power, bool short_, unit* order, coord_def target)
{
	unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
	if(unit_ && order->isplayer() && !unit_->isplayer())
	{
		monster* mon_ = (monster*)unit_;
		bool no_cost_ = (you.s_catch && mon_->s_catch);
		if(you.isEnemyMonster(mon_))
		{
			int throw_length_ = 7;
			SetSpellSight(throw_length_, 1);
			beam_iterator beam(you.position,you.position);
			projectile_infor infor(throw_length_,false,false,SKL_YUUGI_3_THROW,true);
			int temp_flag = mon_->flag;
			mon_->flag |= M_FLAG_PASSED_ENEMY;
			if(Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor, throw_length_, 0.0f))
			{		
				int length_ = ceil(sqrt(pow((float)abs(order->position.x-you.search_pos.x),2)+pow((float)abs(order->position.y-you.search_pos.y),2)));
				printlog("���󰡶�! ",false,false,false,CL_yuigi);
				int damage_ = 5+mon_->level+power/10;
				beam_infor temp_infor(randC(1,damage_),damage_,15,order,order->GetParentType(),length_,1,BMT_PENETRATE,ATT_THROW_NORMAL,mon_->name);
				coord_def final_ = throwtanmac(mon_->image,beam,temp_infor,NULL);

				
				dif_rect_iterator rit(final_,3);

				for(;!rit.end();rit++)
				{
					if(!env[current_level].isMove(rit->x, rit->y))
						continue; //�����ϼ����� ��ġ	
					if(env[current_level].isMonsterPos(rit->x,rit->y)) 
						continue; //�̹� ���Ͱ� �ִ� ��ġ

					mon_->SetXY(*rit);
					break;
				}
				attack_infor temp_att(randC(3,3+power/15),3*(3+power/15),99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor("�����",false));
				BaseBomb(final_, &img_fog_normal[0],temp_att);

				
				mon_->flag = temp_flag;
				if(!no_cost_)
					you.PietyUpDown(-5);
				return true;
			}
			mon_->flag = temp_flag;
		}
	}
	return false;
}
bool skill_yuugi_shout(int pow, bool short_, unit* order, coord_def target)
{
	bool ok_ = false;
	int enter_ = 0;
	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(it->isLive() && env[current_level].isInSight(it->position))
		{
			int offset_ = max(-4,(it->level - you.level));
			if(!ok_)
				printlog("ħ���϶�! ",false,false,false,CL_yuigi);
			if(randA(10+offset_)>3+offset_ || (you.s_catch && !it->isplayer() && ((monster*)&(*it))->s_catch))
			{
				it->SetMute(rand_int(20+pow/5,40+pow/5));
				enter_++;
				if(enter_==3)
				{
					enterlog();
					enter_ = 0;
				}
			}
			ok_ = true;
		}
	}
	if(ok_)
	{
		return true;
	}
	else
	{
		printlog("��ȿ�� ���� ��밡 ����.",true,false,false,CL_normal);
		return false;	
	}
	return false;
}
bool skill_yuugi_sambo(int power, bool short_, unit* order, coord_def target)
{
	printlog("�ﺸ�ʻ�! ",false,false,false,CL_yuigi);
	for(int i = 0; i < 3; i++)
	{
		textures* t_ = i==0?&img_fog_cold[0]:i==1?&img_fog_slow[0]:&img_fog_fire[0];
		{
			dif_rect_iterator rit(order->position,2+i);
		
			for(;!rit.end();rit++)
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if(env[current_level].isSight(*rit) && you.isSightnonblocked(*rit))
					{
						env[current_level].MakeEffect(*rit,t_,false);
					}
				}
		}
		{
			dif_rect_iterator rit(order->position,2+i);
		
			for(;!rit.end();rit++)
			{
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if(env[current_level].isInSight(*rit) && you.isSightnonblocked(*rit))
					{
						if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							if(hit_ != order)
							{
								int att_ = randC(4,4+i+power/20);
								int m_att_ = 4*(4+i+power/20);
								if(you.s_catch && !hit_->isplayer() && ((monster*)hit_)->s_catch)
								{
									att_ *= 2;
									m_att_ *= 2;
								}

								attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor("�����",false));
								hit_->damage(temp_att, true);
							}
						}
					}
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		Sleep(100);

	}
	return true;
}
bool skill_satori_trauma(int power, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = env[current_level].isMonsterPos(target.x,target.y,order))
	{
		if(!(hit_mon->isplayer()) && ((monster*)hit_mon)->id == MON_KOISHI)
		{
			printarray(true,false,false,CL_small_danger,1,"������ ������ �����ִ�.");
			return false;
		}

		if(hit_mon->CalcuateMR(GetDebufPower(SKL_SATORI_1,power)))
		{
			

			hit_mon->SetFear(rand_int(15,20));
		}
		else if(hit_mon->isYourShight())
		{					
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"�����ߴ�.");
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}
bool skill_satori_mind_reading(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;
	unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
	if(unit_ && order->isplayer() && !unit_->isplayer())
	{
		monster* mon_ = (monster*)unit_;
		if(you.isEnemyMonster(mon_))
		{
			int turn_ = 2+mon_->level/3+mon_->resist*3;

			turn_ = max(1,turn_-you.level/4);

			if(turn_>=20)
			{
				printarray(true,false,false,CL_small_danger,1,"�� ����� ������ ���� �� ����.");
				return false;
			}
			if(mon_->id == MON_KOISHI)
			{
				printarray(true,false,false,CL_small_danger,1,"������ ������ �����ִ�.");
				return false;
			}
			if(mon_->s_mind_reading)
			{
				printarray(true,false,false,CL_normal,1,"�̹� ������ ������ ����̴�.");
				return false;

			}

			int fail_ = 0;
			for(int i=0; i<turn_; i++)
			{
				printarray(false,false,false,CL_danger,1,"������ �д� ��... ");
				if(you.s_confuse || you.s_paralyse)
				{
					fail_ = 1;
					break;
				}
				if(!env[current_level].isInSight(mon_->position))
				{
					fail_ = 2;
					break;
				}
				you.time_delay += you.GetNormalDelay();
				you.TurnEnd();
				Sleep(100);
			}
			if(fail_)
				printarray(true,false,false,CL_small_danger,1,fail_==1?"���ظ� �޾� ������ �дµ� �����ߴ�.":"����� �þ߿� ������� �����ߴ�.");
			else
			{
				//printarray(true,false,false,CL_normal,3,mon_->GetName()->name.c_str(),mon_->GetName()->name_is(true),"������ ���Ĵ��ߴ�.");
				mon_->SetMindReading(1);
			}
			return true;
		}

	}

	return false;
}

bool skill_shinki_low_demon(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;

	for(int i = rand_int(2,3); i>0 ; i--)
	{
		if(BaseSummon((randA(1)?MON_EVIL_EYE:MON_LITTLE_IMP), rand_int(30,50), true, false, 2, order, target, SKD_SUMMON_SHINKI, -1))
			return_ = true;
	}
	if(return_)
	{		
		printarray(true,false,false,CL_magic,1,"������ �������� ��ſ��� ��ȯ�Ǿ���. ");	
	}
	return return_;
}
bool skill_shinki_mid_demon(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	if(monster* mon_=BaseSummon(randA(2)==0?MON_SARA:(randA(1)?MON_LUIZE:MON_ELIS), rand_int(90,120), true, false, 2, order, target, SKD_SUMMON_SHINKI, -1))
	{			
		printarray(false,false,false,CL_magic,3,mon_->name.name.c_str(),mon_->name.name_do(true),"��ſ��� ��ȯ�Ǿ���. ");		
		if(randA(99)<=8)
		{
			printarray(false,false,false,CL_danger,2,mon_->name.name.c_str(),"�� ����� �� ���ƺ����� �ʴ´�.");				
			mon_->ReturnEnemy();			
		}
		return_ = true;
		enterlog();
	}
	return return_;

} 
bool skill_shinki_high_demon(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	int id_ = randA(3)==0?MON_YUKI:(randA(2)==0?MON_MAI:randA(1)?MON_YUUGENMAGAN:MON_SARIEL);
	if(monster* mon_=BaseSummon(id_, rand_int(90,120), true, false, 2, order, target, SKD_SUMMON_SHINKI, -1))
	{			
		printarray(false,false,false,CL_magic,3,mon_->name.name.c_str(),mon_->name.name_do(true),"��ſ��� ��ȯ�Ǿ���. ");		
		if(randA(99)<=(id_==MON_YUKI?5:id_==MON_MAI?11:8))
		{
			printarray(false,false,false,CL_danger,2,mon_->name.name.c_str(),"�� ����� �� ���ƺ����� �ʴ´�.");				
			mon_->ReturnEnemy();			
		}
		return_ = true;
		enterlog();
	}
	return return_;
} 
bool skill_yuyuko_on(int power, bool short_, unit* order, coord_def target)
{	
	if(order->isplayer() && !you.s_ghost)
	{
		printlog("������ �ҷ����̱� �����Ѵ�.",true,false,false,CL_normal);
		you.SetGhost(1);
		int temp = you.Ability(SKL_YUYUKO_ON,true,true,1);
		you.Ability(SKL_YUYUKO_OFF,true,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_ghost)
		printlog("�̹� ������ ������ �ִ�(����).",true,false,false,CL_normal);	

	return false;
}
bool skill_yuyuko_off(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("���� ��ȯ�� �����.",true,false,false,CL_normal);
		you.s_ghost = 0;
		int temp = you.Ability(SKL_YUYUKO_OFF,true,true,1);
		you.Ability(SKL_YUYUKO_ON,true,false,temp);
		return true;
	}
	return false;

}
bool skill_yuyuko_recall(int power, bool short_, unit* order, coord_def target)
{	
	if(!order->isplayer())
		return false;
	unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
	if(unit_ && !unit_->isplayer())
	{
		
		int j=0;
		
		if(you.god_value[0])
		{
			for(auto it = env[you.god_value[1]].mon_vector.begin(); j == 0 && it != env[you.god_value[1]].mon_vector.end();it++)
			{
				if(it->isLive() && (*it).isUserAlly() && it->map_id == you.god_value[0])
				{
					dif_rect_iterator rit(target,2);
					for(; j == 0 && !rit.end();rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y,it->isFly(),it->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
						{
							if(you.god_value[1] == current_level)
							{
								it->SetXY(rit->x,rit->y);
								if(unit_){
									it->FoundTarget(unit_,30);
								}
								j++;
							}
							else
							{								
								if(env[current_level].movingfloor((*rit), you.god_value[1], &(*it)))
								{
									j++;
								}
							}
						}
					}
				}
			}

		}

		deque<monster*> dq;
		for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
		{
			if(it->isLive() && it->isUserAlly()  && it->GetId() == MON_GHOST)
			{
				dq.push_back(&(*it));
			}
		}
		random_shuffle(dq.begin(),dq.end());
		dif_rect_iterator rit(target,2);
		for(int i = 0;!rit.end() && i < dq.size();rit++)
		{
			if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
			{
				dq[i]->SetXY(rit->x,rit->y);
				if(dq[i] && unit_){
					dq[i]->FoundTarget( unit_,30);
				}
				j++;
				i++;
			}
		}
		if(j>0)
		{
			printarray(true,false,false,CL_normal,2,unit_->GetName()->name.c_str(),"���� ������ �����´�.");
			unit_->AttackedTarget(order);
			return true;
		}
		else
		{
			printarray(true,false,false,CL_normal,1,"������ ����.");
			return false;
		}
	}
	printlog("������ ������� ����ؾ��Ѵ�.",true,false,false,CL_normal);
	return false;
}
bool skill_yuyuko_boost(int power, bool short_, unit* order, coord_def target)
{	
	if(order->isplayer())
	{
		printlog("����� �뷮�� ������ �ҷ����̱� �����Ѵ�!",true,false,false,CL_white_blue);
		int time_ = rand_int(35,45);
		you.SetGhost(time_);
	}
	return true;

}
bool skill_yuyuko_enslave(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;	
	if(unit* hit_mon = DebufBeam(SKL_YUYUKO_3, order, target))
	{
		/*
	if(unit* hit_mon = env[current_level].isMonsterPos(target.x,target.y,order))
	{*/
		if(1/*hit_mon->CalcuateMR(GetDebufPower(SKL_YUYUKO_3,power))*/)
		{
			if(!hit_mon->SetGhost(rand_int(40,60)))
			{
				return false;
			}
		}
		/*else if(hit_mon->isYourShight())
		{					
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"�����ߴ�.");
		}*/
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}



bool skill_yukari_supporter(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isInSight(coord_def(target.x,target.y)))
	{
		if(floor_effect* hit_eff = env[current_level].isFloorEffectPos(target.x,target.y))
		{
			if(hit_eff->type == FLOORT_SCHEMA)
			{
				if(BaseSummon(MON_SCHEMA_EYE, 40+randA_1(power/10), true, false, 0, order, target, SKD_OTHER, -1))
				{
					hit_eff->time = 0;
					return true;
				}
				else
				{
					printarray(true,false,false,CL_normal,1,"������ �� ���� ��ġ��.");
					return false;
				}
			}
		}
		printarray(true,false,false,CL_normal,1,"ƴ���� ������� �����ؾ��Ѵ�.");
	}
	return false;

}
bool skill_yukari_schema(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isInSight(coord_def(target.x,target.y)))
	{
		if(floor_effect* hit_eff = env[current_level].isFloorEffectPos(target.x,target.y))
		{
			if(hit_eff->type == FLOORT_SCHEMA)
			{
				if(you.control_blink(target))
				{
					printarray(true,false,false,CL_normal,1,"ƴ���� Ÿ�� �̵��Ͽ���.");
					hit_eff->time = 0;
					return true;
				}
				else
				{
					printarray(true,false,false,CL_normal,1,"�̵��� �� ���� ��ġ��.");
					return false;
				}
			}
		}
		printarray(true,false,false,CL_normal,1,"ƴ���� ������� �����ؾ��Ѵ�.");
	}
	return false;

}
bool skill_yukari_shield(int power, bool short_, unit* order, coord_def target)
{	
	if(order == &you)
	{
		you.SetBuff(BUFFSTAT_SH,BUFF_YUKARI,15,rand_int(70,100));
		printlog("��谡 ����� ��ȣ�ϰ� �ִ�.",true,false,false,CL_white_blue);
		return true;
	}
	return false;
}
bool skill_yukari_dimension(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(env[current_level].isBamboo())
		{
			printlog("�� �������� ������ ������ �� ����!",true,false,false,CL_small_danger);
			return false;
		}
		you.god_value[0] = target.x;
		you.god_value[1] = target.y;
		you.SetDimension(rand_int(50,70));
		printlog("������ �����Ǿ���!",false,false,false,CL_white_blue);
		return true;
	}
	return false;
}



bool skill_swako_jump(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isInSight(target) && you.isSightnonblocked(target))
	{
		if(env[current_level].isMove(target.x,target.y) && !env[current_level].isMonsterPos(target.x,target.y))
		{
			you.SetXY(target.x,target.y);
			printarray(false,false,false,CL_normal,1,"����! ");
			return true;
		}
	}
	return false;
}
bool skill_swako_temple(int power, bool short_, unit* order, coord_def target)
{	
	auto tile_ = env[current_level].dgtile[order->position.x][order->position.y].tile;

	if(tile_ >= DG_FLOOR && tile_ <= DG_FLOOR_END)
	{		
		env[current_level].dgtile[order->position.x][order->position.y].tile = DG_TEMPLE_SUWAKO;
		printlog("����� �߹ؿ� �����ڴ��� ������ ������. �žӽ��� ǳ�������� ���� ������.",true,false,false,CL_swako);
		you.PietyUpDown(2+randA(2));
		return true;
	}
	else
		printlog("���⿣ ������ ���� �� ����.",true,false,false,CL_small_danger);

	return false;
}
bool skill_swako_water_gun(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randA_1(5+power/5),5+power/5,15,order,order->GetParentType(),SkillLength(SKL_SWAKO_WATER_GUN),1,BMT_NORMAL,ATT_THROW_WATER,name_infor("����",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(14,beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_swako_tongue(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;	
	if(unit* hit_mon = DebufBeam(SKL_SWAKO_TOUGUE, order, target))
	{
		beam_iterator beam(order->position,target);
		if(CheckThrowPath(order->position,target,beam))
		{
			beam.init();

			if(env[current_level].isMove(coord_def(beam->x,beam->y),hit_mon->isFly(),hit_mon->isSwim(),false))
			{
				hit_mon->SetXY(*beam);
				hit_mon->AttackedTarget(order);
				printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_to(true),"���� ����.");
				return true;
			}
		}
		printlog("���� ��� �� ���� ��ġ�Դϴ�.",true,false,false,CL_small_danger);

	}
	return false;

}
bool skill_swako_curse(int power, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = env[current_level].isMonsterPos(target.x,target.y,order))
	{
		int level_ = min(10,max(0,order->GetLevel() - hit_mon->GetLevel() + 5));
		if(hit_mon->isYourShight())
		{				
			printarray(false,false,false,CL_swako,2,hit_mon->GetName()->name.c_str(),"�� ����� ���ȴ�.");
			hit_mon->SetSlow(rand_int(2,10)+randA(level_*3));
			hit_mon->SetPoison(rand_int(20,35)+randA(level_*4),150,true);
			hit_mon->SetPoisonReason(order->GetParentType());
			hit_mon->AttackedTarget(order);

			
			rand_rect_iterator rit(target,1,1);
			int smoke_ = rand_int(2,3);
			for(int i = 0; !rit.end() && i < smoke_;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, true))
				{
					env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_FOG,rand_int(6,12),0,&you);
					i++;
				}
			}
			return true;
		}
	}
	return false;
}
bool skill_swako_digging(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;	
	beam_iterator beam(order->position,target);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam.init();
		int length_ = SkillLength(SKL_SWAKO_DIGGING);
		if(short_)
			length_ = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		if(length_ == 0)
			return false;

		while(length_>0)
		{
			if(env[current_level].dgtile[beam->x][beam->y].isBreakable())
				env[current_level].dgtile[beam->x][beam->y].tile = DG_FLOOR;
			beam++;
			length_--;
		}
		return true;
	}

	return false;
}
bool skill_swako_summon_flog(int power, bool short_, unit* order, coord_def target)
{	
	bool return_=false;
	if(monster* mon_=BaseSummon(MON_FROG, rand_int(60,80), true, false, 2, order, target, SKD_SUMMON_SWAKO_FLOG, -1))
	{			
		printarray(false,false,false,CL_magic,3,mon_->name.name.c_str(),mon_->name.name_do(true),"��ſ��� ��ȯ�Ǿ���. ");		
		return_ = true;
		enterlog();
	}
	return return_;
}
bool skill_swako_statue(int power, bool short_, unit* order, coord_def target)
{
	auto tile_ = env[current_level].dgtile[target.x][target.y].tile;

	if(tile_ >= DG_FLOOR && tile_ <= DG_FLOOR_END)
	{		
		if(!env[current_level].isMonsterPos(target.x,target.y))
		{
			env[current_level].dgtile[target.x][target.y].tile = DG_STATUE;
			env[current_level].MakeEvent(EVL_FLOOR, target, EVT_COUNT,rand_int(30,50));
			return true;
		}
		else
			printlog("���⿣ ������ ���� �� ����.",true,false,false,CL_small_danger);
	}
	else
		printlog("���⿣ ������ ���� �� ����.",true,false,false,CL_small_danger);
	return false;
}
bool skill_swako_rain(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;

	for(int i = rand_int(3,4); i>0 ; i--)
	{
		if(BaseSummon(MON_FROG, rand_int(30,50), true, true, 3, order, target, SKD_SUMMON_SWAKO_FLOG, -1))
			return_ = true;
	}
	if(BaseSummon(MON_DEAGAMA, rand_int(30,50), true, true, 3, order, target, SKD_SUMMON_SWAKO_FLOG, -1))
		return_ = true;


	dif_rect_iterator rit(target,2);
	while(!rit.end())
	{
		auto tile_ = env[current_level].dgtile[rit->x][rit->y].tile;
		if(tile_ >= DG_FLOOR && tile_ <= DG_FLOOR_END)
		{		
			auto mons_ = env[current_level].isMonsterPos(rit->x,rit->y);
			if(!mons_ || mons_->isFly() || mons_->isSwim())
			{
				env[current_level].dgtile[rit->x][rit->y].tile = DG_SEA;
			}
		}
		rit++;
	}

	printarray(true,false,false,CL_magic,1,"����� �ֺ��� ���ٴٰ� �Ǿ���. ");	
	
	return true;
}
bool skill_swako_sleep(int power, bool short_, unit* order, coord_def target)
{
	you.SetTimeStep(100);
	return true;
}
bool skill_swako_misyaguzi(int power, bool short_, unit* order, coord_def target)
{
	return false;
}
bool skill_hina_plusminus(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_CURSE_ENCHANT,"���� �������� ���ðڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			list<item>::iterator it;
			for(it = you.item_list.begin(); it != you.item_list.end();it++)
			{
				if((*it).id == key_)
				{
					if(((*it).type>=ITM_WEAPON_FIRST && (*it).type<ITM_WEAPON_LAST) || ((*it).type>=ITM_ARMOR_FIRST && (*it).type<ITM_ARMOR_LAST))
					{		
						if(!it->isArtifact())
						{
							if(it->curse && it->identify_curse)
							{
								if(((*it).type>=ITM_WEAPON_FIRST && (*it).type<ITM_WEAPON_LAST) && (it->value4 < 0))
								{
									int value4_ = it->value4;
									//if(value3_<0)
									//	it->Enchant(ET_WEAPON, value3_*-2);
									if(value4_<0)
										it->Enchant(ET_WEAPON,value4_*-2);
									printlog("������ ����� ������ �׶��� ���־���.",true,false,false,CL_hina);
									return true;	
								}
								else if(((*it).type>=ITM_ARMOR_FIRST && (*it).type<ITM_ARMOR_LAST) && (it->value4 < 0))
								{
									if(it->value4<0)
										it->Enchant(ET_ARMOR,it->value4*-2);
									printlog("������ ����� ���� �׶��� ���־���.",true,false,false,CL_hina);
								
									return true;	

								}
								else
								{
									printlog("���̳ʽ� ��æƮ�� �Ǿ��ִ� �����۸� ������ �� �ִ�.",true,false,false,CL_normal);
									return false;	
								}
							}
							else
							{
								printlog("���� �ɷ��ִ� �����ۿ��� ����� �� �ִ�.",true,false,false,CL_normal);
								return false;	
							}
						}
						else
						{
							printlog("��Ƽ��Ʈ�� ����� �� ����.",true,false,false,CL_normal);
							return false;	
						}
					}
					else
					{
						printlog("�ùٸ��� ���� ����̴�.",true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog("�������� �ʴ� ������.",true,false,false,CL_normal);
			return false;	
		}
		else if(key_ == VK_DOWN)//-----�̵�Ű-------
		{
			changemove(32);  //��
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //�Ʒ�
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----�̵�Ű��-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"���� �������� ���ðڽ��ϱ�?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}
bool skill_hina_curse_weapon(int power, bool short_, unit* order, coord_def target)
{	
	if(you.equipment[ET_WEAPON])
	{
		if(you.equipment[ET_WEAPON]->curse)
		{
			printlog("�̹� ���ֿ� �ɷ��ִ�.",true,false,false,CL_normal);
			return false;
		}
		string before_name = you.equipment[ET_WEAPON]->GetName(); //���ֹޱ��� �̸�
		if(you.equipment[ET_WEAPON]->Curse(true,ET_WEAPON))
		{
			printlog("�����ϰ� �ִ� ",false,false,false,CL_small_danger);	
			printlog(before_name,false,false,false,CL_small_danger);	
			printlog(you.equipment[ET_WEAPON]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
			printlog("�˰� �����鼭 ��ſ��� �ź��� ���� ���´�.",true,false,false,CL_small_danger);		
			you.SetMight(rand_int(80,100));
			return true;
		}
		else
		{
			printlog("�� ����� ���ָ� �� �� ����.",true,false,false,CL_small_danger);
			return false;
		}

	}
	printlog("���⸦ ���� �־�� �ȴ�.",true,false,false,CL_normal);
	return false;
}
bool skill_hina_curse_armour(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_UEQ_ARMOR,"���� ���� ���ðڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			list<item>::iterator it;
			for(it = you.item_list.begin(); it != you.item_list.end();it++)
			{
				if((*it).id == key_)
				{
					if(((*it).type>=ITM_ARMOR_FIRST && (*it).type<ITM_ARMOR_LAST))
					{		
						for(equip_type i = ET_ARMOR;i!=ET_ARMOR_END;i=(equip_type)(i+1))
						{
							if(you.equipment[i] && you.equipment[i]->id == key_)
							{
								if(!it->curse && it->identify_curse)
								{
									string before_name = you.equipment[i]->GetName(); //���ֹޱ��� �̸�
									if(it->Curse(true,i))
									{
										int time_ = rand_int(25,40);
										printlog("�����ϰ� �ִ� ",false,false,false,CL_small_danger);	
										printlog(before_name,false,false,false,CL_small_danger);	
										printlog(you.equipment[i]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
										printlog("�˰� �����鼭 ����� ��� �������� �ݻ��Ѵ�.",true,false,false,CL_small_danger);	
										if(i == ET_ARMOR)	
											time_*=3;
										you.SetMirror(time_);
										return true;
									}
									else
									{
										printlog("�� ������ ���ָ� �� �� ����.",true,false,false,CL_small_danger);
										return false;	
									}
								}
								else
								{
									printlog("�̹� ���ֿ� �ɷ��ִ�.",true,false,false,CL_normal);
									return false;	
								}
							}
						}
						printlog("�װ��� �԰� ���� �ʴ�!",true,false,false,CL_normal);
						return false;	
					}
					else
					{
						printlog("������ ����� �����ϴ�.",true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog("�������� �ʴ� ������.",true,false,false,CL_normal);
			return false;	
		}
		else if(key_ == VK_DOWN)//-----�̵�Ű-------
		{
			changemove(32);  //��
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //�Ʒ�
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----�̵�Ű��-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"���� ���� ���ðڽ��ϱ�?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}
bool skill_hina_curse_ring(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_UEQ_JEWELRY,"���� ��ű��� ���ðڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			list<item>::iterator it;
			for(it = you.item_list.begin(); it != you.item_list.end();it++)
			{
				if((*it).id == key_)
				{
					if(((*it).type>=ITM_JEWELRY_FIRST && (*it).type<ITM_JEWELRY_LAST))
					{		
						for(equip_type i = ET_JEWELRY;i!=ET_JEWELRY_END;i=(equip_type)(i+1))
						{
							if(you.equipment[i] && you.equipment[i]->id == key_)
							{
								if(!it->curse && it->identify_curse)
								{
									string before_name = you.equipment[i]->GetName(); //���ֹޱ��� �̸�
									if(it->Curse(true,i))
									{										
										int bonus_ = rand_int(10,15)+you.GetMaxHp()*rand_float(0.25f,0.35f);
										printlog("�����ϰ� �ִ� ",false,false,false,CL_small_danger);	
										printlog(before_name,false,false,false,CL_small_danger);	
										printlog(you.equipment[i]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
										printlog("�˰� �����鼭 ����� ȸ���Ѵ�.",true,false,false,CL_small_danger);											
										you.HpUpDown(bonus_,DR_NONE);										
										you.MpUpDown(you.max_mp *rand_float(0.3f,0.4f));
										return true;
									}
									else
									{
										printlog("�� ��ű����� ���ָ� �� �� ����.",true,false,false,CL_small_danger);
										return false;
									}
								}
								else
								{
									printlog("�̹� ���ֿ� �ɷ��ִ�.",true,false,false,CL_normal);
									return false;	
								}
							}
						}
						printlog("�װ��� �԰� ���� �ʴ�!",true,false,false,CL_normal);
						return false;	
					}
					else
					{
						printlog("��ű����� ����� �����ϴ�.",true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog("�������� �ʴ� ������.",true,false,false,CL_normal);
			return false;	
		}
		else if(key_ == VK_DOWN)//-----�̵�Ű-------
		{
			changemove(32);  //��
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //�Ʒ�
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----�̵�Ű��-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"���� ��ű��� ���ðڽ��ϱ�?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}


int UseSkill(skill_list skill, bool short_, coord_def &target)
{
	int power=min(SkillCap(skill),SkillPow(skill));
	if(SkillFlagCheck(skill, S_FLAG_SPEAK) && env[current_level].isSilence(you.position))
	{
		printlog("����� �Ҹ��� �� �� ����.",true,false,false,CL_normal);
		return 0;		
	}
	
	if(randA_1(100) > SkillDiffer(skill))
	{
		printlog("����� ��ų ��뿡 �����ߴ�.",true,false,false,CL_normal);
		return 2;
	}	
	if(!SkillPlusCost(skill,true))
		return 0;
	switch(skill)
	{
	case SKL_KANAKO_1:
		return skill_kanako_might(power,short_,&you,target);
		break;
	case SKL_KANAKO_2:
		return skill_kanako_2(power,short_,&you,target);
		break;
	case SKL_KANAKO_3:
		return skill_kanako_haste(power,short_,&you,target);
		break;
	case SKL_GRAZE:
		return skill_turn_graze(power,short_,&you,target);
		break;
	case SKL_GRAZE_OFF:
		return skill_off_graze(power,short_,&you,target);
		break;
	case SKL_LEVITATION:
		return skill_turn_levitation(power,short_,&you,target);
		break;
	case SKL_LEVITATION_OFF:
		return skill_off_levitation(power,short_,&you,target);
		break;
	case SKL_INVISIBLE:
		return skill_turn_invisible(power,short_,&you,target);
		break;
	case SKL_INVISIBLE_OFF:
		return skill_off_invisible(power,short_,&you,target);
		break;
	case SKL_EIRIN_0:
		return skill_eirin_throw_potion(power,short_,&you,target);
		break;
	case SKL_EIRIN_1:
		return skill_eirin_move_stat(power,short_,&you,target);
		break;
	case SKL_EIRIN_2:
		return skill_eirin_heal(power,short_,&you,target);
		break;
	case SKL_BYAKUREN_1:
		return skill_byakuren_smart(power,short_,&you,target);
		break;
	case SKL_BYAKUREN_2:
		return skill_byakuren_leg(power,short_,&you,target);
		break;
	case SKL_MINORIKO_1:
		return skill_minoriko_restore(power,short_,&you,target);
		break;
	case SKL_MINORIKO_2:
		return skill_minoriko_heal(power,short_,&you,target);
		break;
	case SKL_SIZUHA_1:
		return skill_sizuha_confuse(power,short_,&you,target);
		break;
	case SKL_SIZUHA_2:
		return skill_sizuha_autumn_armour(power,short_,&you,target);
		break;
	case SKL_YUUGI_1:
		return skill_yuugi_drink(power,short_,&you,target);
		break;
	case SKL_YUUGI_2:
		return skill_yuugi_german(power,short_,&you,target);
		break;
	case SKL_YUUGI_3:
		return skill_yuugi_throw(power,short_,&you,target);
		break;
	case SKL_YUUGI_4:
		return skill_yuugi_shout(power,short_,&you,target);
		break;
	case SKL_YUUGI_5:
		return skill_yuugi_sambo(power,short_,&you,target);
		break;
	case SKL_SATORI_1:
		return skill_satori_trauma(power,short_,&you,target);
		break;
	case SKL_SATORI_2:
		return skill_satori_mind_reading(power,short_,&you,target);
		break;
	case SKL_SHINKI_1:
		return skill_shinki_low_demon(power,short_,&you,target);
		break;
	case SKL_SHINKI_2:
		return skill_shinki_mid_demon(power,short_,&you,target);
		break;
	case SKL_SHINKI_3:
		return skill_shinki_high_demon(power,short_,&you,target);
		break;
	case SKL_YUYUKO_ON:
		return skill_yuyuko_on(power,short_,&you,target);
		break;
	case SKL_YUYUKO_OFF:
		return skill_yuyuko_off(power,short_,&you,target);
		break;
	case SKL_YUYUKO_1:
		return skill_yuyuko_recall(power,short_,&you,target);
		break;
	case SKL_YUYUKO_2:
		return skill_yuyuko_boost(power,short_,&you,target);
		break;
	case SKL_YUYUKO_3:
		return skill_yuyuko_enslave(power,short_,&you,target);
		break;		
	case SKL_YUKARI_1:
		return skill_yukari_supporter(power,short_,&you,target);
		break;
	case SKL_YUKARI_2:
		return skill_yukari_schema(power,short_,&you,target);
		break;
	case SKL_YUKARI_3:
		return skill_yukari_shield(power,short_,&you,target);
		break;
	case SKL_YUKARI_4:
		return skill_yukari_dimension(power,short_,&you,target);
		break;
	case SKL_SWAKO_JUMP:
		return skill_swako_jump(power,short_,&you,target);
		break;
	case SKL_SWAKO_TEMPLE:
		return skill_swako_temple(power,short_,&you,target);
		break;
	case SKL_SWAKO_WATER_GUN:
		return skill_swako_water_gun(power,short_,&you,target);
		break;
	case SKL_SWAKO_TOUGUE:
		return skill_swako_tongue(power,short_,&you,target);
		break;
	case SKL_SWAKO_CURSE:
		return skill_swako_curse(power,short_,&you,target);
		break;
	case SKL_SWAKO_DIGGING:
		return skill_swako_digging(power,short_,&you,target);
		break;
	case SKL_SWAKO_SUMMON_FLOG:
		return skill_swako_summon_flog(power,short_,&you,target);
		break;
	case SKL_SWAKO_STATUE:
		return skill_swako_statue(power,short_,&you,target);
		break;
	case SKL_SWAKO_RAIN:
		return skill_swako_rain(power,short_,&you,target);
		break;
	case SKL_SWAKO_SLEEP:
		return skill_swako_sleep(power,short_,&you,target);
		break;
	case SKL_SWAKO_MISYAGUZI:
		return skill_swako_misyaguzi(power,short_,&you,target);
		break;		
	case SKL_HINA_1:
		return skill_hina_plusminus(power,short_,&you,target);
		break;
	case SKL_HINA_2:
		return skill_hina_curse_weapon(power,short_,&you,target);
		break;
	case SKL_HINA_3:
		return skill_hina_curse_armour(power,short_,&you,target);
		break;
	case SKL_HINA_4:
		return skill_hina_curse_ring(power,short_,&you,target);
		break;
	}
	return 0;
}


