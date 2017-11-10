//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: event.cpp
//
// ����: �̺�Ʈ ó���� ���� �Լ�, Ŭ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "event.h"
#include "environment.h"
#include "save.h"
#include "rect.h"
#include "key.h"
#include "mon_infor.h"
#include "skill_use.h"
#include "floor.h"

int EventOccur(int id, events* event_);

void bamboo_count(int num);
void arena_event(int num);
bool skill_summon_namaz2(int power, bool short_, unit* order, coord_def target);

events::events()
:id(0),position(),type(EVT_ABOVE),prev_sight(false)
{
}

events::events(int id_, coord_def position_, event_type type_, int count_)
:id(id_),position(position_),type(type_),prev_sight(false), count(count_)
{
	start();
}



void events::SaveDatas(FILE *fp)
{	
	SaveData<int>(fp, id);
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<event_type>(fp, type);
	SaveData<int>(fp, count);
	SaveData<bool>(fp, prev_sight);
}
void events::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, id);
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<event_type>(fp, type);
	LoadData<int>(fp, count);
	LoadData<bool>(fp, prev_sight);
}

int events::start()
{	
	switch(id)
	{
	case EVL_VIOLET:
		{
			int violet_range = min(10, (count+1) / 2) ;
			env[current_level].MakeViolet(position, violet_range, true);
		}
		break;
	case EVL_SANTUARY:
	{
		int santuary_range = min(10, (count + 1) / 2);
		env[current_level].MakeSantuary(position, santuary_range, true);
	}
	break;
	default:
		break;
	}
	return 0;
}
int events::action(int delay_)
{
	bool is_sight = false;
	if(env[current_level].isInSight(position))
		is_sight = true; //���� ���� ���̴���

	if(count>=0)
	{
		count--;
		if(type == EVT_COUNT && count<=0)
		{			
			if(EventOccur(id,this))
				return 0;
		}
	}
	if(type == EVT_SIGHT && is_sight && !prev_sight)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_ABOVE && position == you.position)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_APPROACH_SMALL && distan_coord(position,you.position)<=2)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_APPROACH_MIDDLE && distan_coord(position,you.position)<=10)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_ALWAYS)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(is_sight)
		prev_sight = true;
	else if(prev_sight)
		prev_sight = false;
	return 1;
	
}






int EventOccur(int id, events* event_) //1�� �����ϰ� ������
{
	enterlog();
	switch(id)
	{
	case 1:
		printlog("ī���ڴ� ���ߴ� : ���� ������ �� ������ OŰ��, �������� CŰ�� ���� �� ����.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ����Ű�� �о �ڵ����� ���⵵ �Ѵܴ�.",true,false,false,CL_warning);
		return 1;
	case 2:
		printlog("ī���ڴ� ���ߴ� : Ű�е��� ����Ű�� y u b nŰ�� �밢���� ����������.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : oŰ�� ������ Ž�� ���� �������� �ڵ����� �̵�����.",true,false,false,CL_warning);
		return 1;
	case 3:
		printlog("ī���ڴ� ���ߴ� : ,�� g�� ������ �������� �ֿ��� �����غ���.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : wŰ�� ����, WŰ�� ������, iŰ�� ����, dŰ�� �������.",true,false,false,CL_warning);
		return 1;
	case 4:
		printlog("ī���ڴ� ���ߴ� : ũ���� ������ ������ ��������, ������ ���� �ε����� ��.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� ���� 1:1�� �ο�°� �����ϴ� ������� �����Ϸ�.",true,false,false,CL_warning);
		return 1;
	case 5:
		printlog("ī���ڴ� ���ߴ� : �׻� �ο��� �Ŀ� ü���� ä��� ������ ���̷�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : .Ű�� 1���޽���, 5Ű�� 100�� �޽��� �� �� �־�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �׸��� ���Ͱ� ���� P���� �� �ֿ��� �Ŀ��� ä�쵵�� ��.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �Ŀ��� �������, �ɷ»��, ���������� ��¿� ������ ����.",true,false,false,CL_warning);
		return 1;
	case 6:
		printlog("ī���ڴ� ���ߴ� : ����� ���������� >Ű, �ö�ö� <Ű�� �ö�� �� �־�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �̹� ������ ������ ���� ������ ���� ������ ��������.",true,false,false,CL_warning);
		return 1;
	case 7:
		if(you.power>150)
			you.PowUpDown(-(you.power-150),true);
		printlog("ī���ڴ� ���ߴ� : �Ŀ��� 2.00���ϰ� �Ǹ� ���ݷ��� �����ع����ܴ�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� ��Ƽ� P���� �Դ°� ���� ������ ������ ���ؼ��� ȸ���� ��������.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : eŰ�� ������ ���� ������ �Ŀ��� ȸ���� �� �־�.",true,false,false,CL_warning);
		return 1;
	case 8:
		printlog("ī���ڴ� ���ߴ� : ���Ÿ� ������ ������ ������. ������ �ֿ�����.",true,false,false,CL_warning);
		return 1;
	case 9:
		printlog("ī���ڴ� ���ߴ� : ���Ÿ� ���⸦ �������� FŰ�� ������ ���� ���� ���.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : fŰ�� �غ�Ǿ��ִ� ź���� �ٷ� ���� �� �ִܴ�.",true,false,false,CL_warning);
		return 1;
	case 10:
		printlog("ī���ڴ� ���ߴ� : ȿ���� �� �� ���� ��ű��� �η縶����. �ϴ� ����غ���.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �ϴ� ������ �ֿ��� PŰ�� ������. RŰ�� ���� �� �־�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �η縶���� �д°� rŰ��. ����â�� �߸� ������ ����غ�.",true,false,false,CL_warning);
		return 1;
	case 11:
		printlog("ī���ڴ� ���ߴ� : ����, ����� ������ ���� ������ �ȵ���. dŰ�� ���� �� �־�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ������ ���̴±�. ������ qŰ�� ���� �� �־�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� �Ա����� ȿ���� �� �� ���� ���� ���� ȿ���� ����.",true,false,false,CL_warning);
		return 1;
	case 12:
	you.GiveSkillExp(SKT_SPELLCASTING,20,true);
	you.GiveSkillExp(SKT_CONJURE,100,true);
		printlog("ī���ڴ� ���ߴ� : ������ ������ å���� �ֹ��� ���� ���������.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �ϴ� å�� �ֿ��� MŰ�� ������ź���� �������.",true,false,false,CL_warning);\
		return 1;
	case 13:
		printlog("ī���ڴ� ���ߴ� : ������ ����ϱ����ؼ� zŰ�� ZŰ�� ������ ����Ҽ��־�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ����� ����������� �Ȱ��ܴ�! �� ���� �������� ��ƺ���.",true,false,false,CL_warning);
		return 1;
	case 14:
		printlog("ī���ڴ� ���ߴ� : <Ű�� �ٽ� �������� �ö� �� �־�.",true,false,false,CL_warning);
		return 1;
	case 15:
		printlog("�ż��� ����� ������ �ִ�.",true,false,false,CL_normal);
		return 1;
	case 16:
		printlog("ī���ڴ� ���ߴ� : �ο�� �Ŀ� 5Ű�� �޽� ����ϰ�����? ���� �ɷȴٸ� Ǯ���.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ������ ã���� ������ pŰ�� �⵵�� �� �� �־�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �� �����̴ϱ� �ѹ� �Ͼ��. �ϰ��� ^Ű�� ������ ����.",true,false,false,CL_warning);
		return 1;
	case 17:
		printlog("ī���ڴ� ���ߴ� : aŰ�� ������ �Ǵ��� �ѹ� ����ؼ� �ο�����.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �Ǵ��� ���� �žӽ��� �Ǹ� ���� �þ�Ե���.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : Ư�� �� �Ǵ��� �žӽ��� ������ �Ҹ��ϴϱ� �����ؼ� ��.",true,false,false,CL_warning);
		return 1;
	case 18:
		printlog("ī���ڴ� ���ߴ� : �Ÿ��� �žӽ��� ��� ����� �ٸ��� �Ⱦ��ϴ� �͵� �ִܴ�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� ���� ���� ���϶����� �žӽ��� ���ݾ� �����ܴ�.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �� ���� ���� ���� ���̸� �ڵ����� �žӽ��� ������.",true,false,false,CL_warning);
		return 1;
	case 19:
		printlog("ī���ڴ� ���ߴ� : �䱫 ����̱���. �Ӹ����� �̸��� ������ ���� ���ӵ����.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���ӵ���� ���� ������ ������. ���ܰ� ����� ��������.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : �׵��� ���� �����۰� ����� Ȱ���ؼ� ���� �� ������ �����غ���.",true,false,false,CL_warning);
		return 1;
	case 20:
		printlog("ī���ڴ� ���ߴ� : Ʃ�丮���� ���⼭ ���̶��� �糪��.",true,false,false,CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� ���ӿ����� ������ �η����������Ŷ�!",true,false,false,CL_warning);
		return 1;
	case 21:
		printlog("������ ���Ⱑ ��������. �����̶� ������!",true,false,false,CL_small_danger);
		return 1;
	case 22:
		printlog("���� �и� ����� ���ұ�. ���� ������ ��!",true,false,false,CL_help);
		return 1;
	case 23:
		printlog("�� ���� ������ �̱��̱�! �ⱸ�� ã�ƾ� �Ѵ�. �ƴϸ� ���ο� ��Ҹ� ã������..?",true,false,false,CL_small_danger);
		return 1;
	case 24:
		return 1;
	case 25:
		printlog("����ũ�ѿ��� �Ѽհ� ����� ������ ���� �����ϴ�. (���� �߰��� �� �ֽ��ϴ�.)",true,false,false,CL_warning);
		printlog("��� ����� �Ѽչ����� �����ϰ� ������ּ���.",true,false,false,CL_warning);
		return 1;
	case 26:
		printlog("������� ������ ������ �������ְ� �׿ܿ� �������� ���а� �ֽ��ϴ�.",true,false,false,CL_warning);
		printlog("���ʿ� ������ ���� ����г�Ƽ�� �����Ͽ� �ջ�Ǿ� ����â�� ǥ�õ˴ϴ�.",true,false,false,CL_warning);
		return 1;
	case 27:

		you.GiveSkillExp(SKT_ARMOUR,1200,true);
		you.GiveSkillExp(SKT_SHIELD,300,true);
		printlog("�� ����г�Ƽ�� ���� ����,���� ��ų�� ���� ���ҵ˴ϴ�.",true,false,false,CL_warning);
		printlog("�ڼ��� ��ġ�� ������ i�� ������ �ڼ��� ��ġ�� Ȯ���غ�����.",true,false,false,CL_warning);
		return 1;
	case 28:
		printlog("����ũ�ѿ� Ȱ�̳� ��ο�ǰ��� ���Ÿ� ���Ⱑ ������ ��� ������ ���� �� �ֽ��ϴ�.",true,false,false,CL_warning);
		printlog("��ħ�� ��ο�Ǿ��� ������ ���� �� ������ �򰥸��� �����ּ���.",true,false,false,CL_warning);
		printlog("��� ź�� ��ų�� ������ �޽��ϴ�.",true,false,false,CL_warning);
		return 1;
	case 29:
		printlog("����ũ�ѿ� ����� ������ ���� ��ſ� ����� P��� �������� �����մϴ�.",true,false,false,CL_warning);
		printlog("�ƻ�� ���������ʴ� ��� 2ĭ���Ϸ� �������� �����г�Ƽ�� �ֽ��ϴ�.",true,false,false,CL_warning);
		printlog("��� ���� ����Ȯ���� P���� ����߸��� �̰��� ������ P�� ȸ���˴ϴ�.",true,false,false,CL_warning);
		return 1;
	case 30:
		printlog("����ī��� ������ �ϵ带 ��ü�ϴ� �������Դϴ�.",true,false,false,CL_warning);
		printlog("{�ߵ�}�� ���� ���� P�� �Ҹ��Ͽ� �ߵ��ϴ� �������� ��Ҹ�ߵ����Դϴ�.",true,false,false,CL_warning);
		printlog("�Ѵ� V�� �ߵ��� �����ϸ� �ߵ���ų�� ������ �޾� ���������ϴ�.",true,false,false,CL_warning);
		return 1;
	case 31:
		printlog("����ũ�ѿ� �� 10���� ���� �ְ� ��Ʈ�� ���� ��ü�ϴ� ������ �Ż簡 �����Ͽ�",true,false,false,CL_warning);
		printlog("��Ʈ�� ���긦 ��ü�ϴ� ������̶� ���� �ֿ��� Ż���ϸ� ���ӿ��� �¸��մϴ�.",true,false,false,CL_warning);
		printlog("���ڶ� ���������� �� ��Ź�帳�ϴ�.",true,false,false,CL_warning);
		return 1;
	case EVL_KISME:
		{
			dif_rect_iterator rit(you.position,2);
			int i = 1; 
			for(;!rit.end() && i> 0;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y) && you.position != (*rit))
				{
					printlog("�ϴÿ��� Ű���ް� ��������!",true,false,false,CL_small_danger);
					monster *mon_ = env[current_level].AddMonster(MON_KISUME,M_FLAG_EVENT,(*rit));
					mon_->PlusTimeDelay(-mon_->GetWalkDelay()); //Ű���޴� �������� �ٷ� ���������ʴ´�.
					MoreWait();
					i--;
				}
			}
		}
		return 1;
	case EVL_SIGHT_P:
		{
			item_infor temp;
			env[current_level].MakeItem(event_->position,makePitem(MON_MOOK, 1, &temp));
		}
		return 1;
	case EVL_FLOOR:
		{			
			env[current_level].dgtile[event_->position.x][event_->position.y].tile = DG_FLOOR;
		}
		return 1;
	case EVL_DREAM_FLOOR:
	{
		env[current_level].dgtile[event_->position.x][event_->position.y].tile = DG_DREAM_FLOOR;
	}
	return 1;
	case EVL_BAMBOO:
		{			
			bamboo_count(current_level);
		}
		return 0;
	case EVL_LUNATICTIME:
		{			
			for(int i=-3;i<=3;i++)
			{
				if(i!=0)	
					env[current_level].dgtile[event_->position.x+i][event_->position.y+1].tile = DG_FLOOR;
			}
			for(int i = 0; i<5 ; i++)
			{
				for(int j = 0; j<2; j++)
				{
					env[current_level].dgtile[event_->position.x+4*(j*2-1)][event_->position.y+i*2].tile = DG_OPEN_DOOR;
				}
			}
			
			for(int i = 0; i<3 ; i++)
			{
				for(int j = 0; j<3; j++)
				{
					if(i!=1 || j!=1)
						env[current_level].dgtile[event_->position.x-1+i][event_->position.y+4+j].tile = DG_GLASS;
				}
			}
			printlog("It's LUNATIC TIME!!",true,false,false,CL_small_danger);
			env[current_level].MakeNoise(event_->position,16,NULL);
			you.resetLOS();
			MoreWait();
		}
		return 1;
	case EVL_KOGASA:
		{
			dif_rect_iterator rit(you.position,2);
			int i = 1; 
			for(;!rit.end() && i> 0;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y) && you.position != (*rit))
				{
					printlog("�ϴÿ��� �ڰ��簡 ��������!",true,false,false,CL_small_danger);
					monster *mon_ = env[current_level].AddMonster(MON_KOGASA,M_FLAG_EVENT,(*rit));
					MoreWait();
					printlog("...�׷��� �ڰ���� ���ٴڿ� �Ӹ����� �ε�����.",true,false,false,CL_normal);
					mon_->SetConfuse(5+randA(5));
					mon_->hp = mon_->hp*2/3;
					i--;
				}
			}
		}
		return 1;
	case EVL_NOISE:
		{			
			env[current_level].MakeNoise(event_->position,8,NULL);
		}
		return 1;
	case EVL_VIOLET:
		{
			int prev_range = min(10, (event_->count+2) / 2) ;
			int violet_range = min(10, (event_->count+1) / 2) ;
			if(event_->count<=0)
			{		
				env[current_level].MakeViolet(event_->position, prev_range, false);
				return 1;
			}
			else if(prev_range != violet_range)
			{
				env[current_level].MakeViolet(event_->position, prev_range, false);
				env[current_level].MakeViolet(event_->position, violet_range, true);
			}
		}
		return 0;
	case EVL_SANTUARY:
	{
		int prev_range = min(10, (event_->count + 2) / 2);
		int santuary_range = min(10, (event_->count + 1) / 2);
		if (event_->count <= 0)
		{
			env[current_level].MakeSantuary(event_->position, prev_range, false);
			return 1;
		}
		else if (prev_range != santuary_range)
		{
			env[current_level].MakeSantuary(event_->position, prev_range, false);
			env[current_level].MakeSantuary(event_->position, santuary_range, true);
		}
	}
	return 0;
	case EVL_DREAM_MONSTER:
		{		
			int arr_[] = { MON_MAC, MON_NIGHTMARE, MON_LUNATIC, MON_BLUE_UFO, MON_MOON_RABIT_ATTACK, MON_MOON_RABIT_SUPPORT
			};
			rand_rect_iterator rit(event_->position,3,3);
			int mon_id_ = arr_[randA(5)];
			int i = mon_id_==MON_BLUE_UFO?3:1; 
			for(;!rit.end() && i> 0;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y) && you.position != (*rit))
				{
					monster *mon_ = env[current_level].AddMonster(mon_id_,0,(*rit));
					i--;
				}
			}
		}
		return 1;
	case EVL_DREAM_MESSAGE:
		{
			int i = 0;
			for(list<events>::iterator it = env[current_level].event_list.begin();it != env[current_level].event_list.end() ; it++)
			{
				if(it->id == EVL_DREAM_MESSAGE)
					i++;
			}
			switch(i)
			{
			case 5:
				you.resetLOS();
				printlog("���� ���谡 �о����� �����Ѵ�! �ڰ� �ִ� ������ �����!",true,false,false,CL_danger);
				MoreWait();
				break;
			case 4:
				you.resetLOS();
				printlog("���� ���谡 �о����� �ִ�!",true,false,false,CL_danger);
				MoreWait();
				break;
			case 3:
				you.resetLOS();
				printlog("���� ���谡 �� �ٽ� �о�����! ������ ����� ��ġë��!",true,false,false,CL_danger);
				MoreWait();
				break;
			case 2:
				you.resetLOS();
				printlog("���� ����� ���� ��κ� ���ȴ�! �� ���Ͱ� ����� �����Ѵ�!",true,false,false,CL_danger);
				MoreWait();
				break;
			case 1:
				for(int k = 3;k<DG_MAX_X-3;k++)
				{
					for(int h = 3;h<DG_MAX_Y-3;h++)
					{
						if(env[current_level].dgtile[k][h].tile == DG_WALL2)
							env[current_level].dgtile[k][h].tile = DG_DREAM_FLOOR;
					}
				}
				{
					for(int i = 0;i<DG_MAX_X;i++)
						for(int j = 0;j<DG_MAX_Y;j++)
							env[current_level].magicmapping(i,j);
				}
				while(1)
				{
					int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
					if(!env[current_level].isInSight(coord_def(x_,y_)) && env[current_level].dgtile[x_][y_].isFloor()  && !(env[current_level].dgtile[x_][y_].flag & FLAG_NO_STAIR) )
					{
						env[current_level].dgtile[x_][y_].tile = DG_MOON_STAIR;
						env[current_level].stair_vector.push_back(stair_info(coord_def(x_,y_),MOON_LEVEL));
						break;
					}
				}
				you.resetLOS();
				printlog("���� ����� ������ ����Ǿ���! �޷� ���� ��Ż�� ��𼱰� ���ȴ�!",true,false,false,CL_danger);
				MoreWait();
				env[current_level].MakeEvent(EVL_REGEN, coord_def(0,0), EVT_ALWAYS,30);
				break;
			}
		}
		return 1;
	case EVL_AGRO:
		if(event_->count <=0)
		{
			for(vector<monster>::iterator it =  env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
			{
				if(it->isLive())
				{
					it->AttackedTarget(&you);
				}
			}
		}
		return 1;
	case EVL_REGEN:
		if(randA(10)==0)
		{			
			int arr_[] = { MON_MAC, MON_NIGHTMARE, MON_LUNATIC, MON_BLUE_UFO, MON_MOON_RABIT_ATTACK, MON_MOON_RABIT_SUPPORT
			};
			int mon_id_ = arr_[randA(5)];
			
			while(1)
			{
				int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
				if(env[current_level].isMove(x_,y_) && !env[current_level].isMonsterPos(x_,y_) && !env[current_level].isInSight(coord_def(x_,y_)))
				{
					monster *mon_ = env[current_level].AddMonster(mon_id_,0,coord_def(x_,y_));
					mon_->AttackedTarget(&you);
					break;
				}
			}

		}
		return 0;
	case EVL_REGEN2:
		if(randA(50)==0)
		{			
			int arr_[] = { MON_HELL_SPIDER, MON_BLOOD_HAUNT, MON_LANTERN_YOUKAI, MON_HELL_HOUND, MON_ONI, MON_BLUE_ONI
			};
			int mon_id_ = arr_[randA(5)];
			
			while(1)
			{
				int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
				if(env[current_level].isMove(x_,y_) && !env[current_level].isMonsterPos(x_,y_) && !env[current_level].isInSight(coord_def(x_,y_)))
				{
					monster *mon_ = env[current_level].AddMonster(mon_id_,0,coord_def(x_,y_));
					mon_->state.SetState(MS_NORMAL);
					break;
				}
			}

		}
		return 0;
	case EVL_ARENA:
		{			
			arena_event(current_level);
		}
		return 0;
	case EVL_NAMAZ:
		{	
			int power=min(SpellCap(SPL_SUMMON_NAMAZ),you.GetSpellPower(SpellSchool(SPL_SUMMON_NAMAZ,0),SpellSchool(SPL_SUMMON_NAMAZ,1),SpellSchool(SPL_SUMMON_NAMAZ,2)));	
			skill_summon_namaz2(power, false, &you, event_->position);
			return 1;
		}
		return 0;
	case EVL_KOISHI:
		{		
			if(event_->count==-1)
			{
				event_->type = EVT_ALWAYS;
				event_->count = 11;
			}
			if(event_->count==10)
			{
				enterlog();
				printlog("��, �޸���",true,false,false,CL_small_danger);
				MoreWait();
				you.SetInter(IT_EVENT);
			}			
			if(event_->count==5)
			{
				enterlog();
				printlog("����, �����",true,false,false,CL_small_danger);
				MoreWait();
				you.SetInter(IT_EVENT);
			}				
			if(event_->count==0)
			{
				
				dif_rect_iterator rit(you.position,2);
				int i = 1; 
				for(;!rit.end() && i> 0;rit++)
				{
					if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y) && you.position != (*rit))
					{
						enterlog();
						printlog("�� �ڿ� �־�",true,false,false,CL_danger);
						MoreWait();
						monster *mon_ = env[current_level].AddMonster(MON_KOISHI,M_FLAG_EVENT,(*rit));
						mon_->PlusTimeDelay(-mon_->GetWalkDelay()); //���̽ô� �������� �ٷ� ���������ʴ´�.
						mon_->SetHaste(20+randA(20));
						return 1;
					}
				}
				enterlog();
				printlog("... ������ �ʴ� ���� �־�",true,false,false,CL_small_danger); //���̽� �������
				MoreWait();
				return 1;
			}
		}
		return 0;
	case EVL_KYOKO:
		{
			monster *kyoko_ = env[current_level].AddMonster(MON_KYOUKO,M_FLAG_EVENT,coord_def(0,-5)+event_->position);
			
			for(int i=rand_int(2,4);i>0;i--)
			{
				item_infor temp;
				env[current_level].MakeItem(coord_def(rand_int(-1,1),rand_int(-5,-3))+event_->position,makePitem(MON_HUMAM_MAN, 1, &temp));
			}

			dif_rect_iterator rit(coord_def(0,-3)+event_->position,1);
			int i = rand_int(2,4); 
			for(;!rit.end() && i> 0;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y) && you.position != (*rit))
				{
					monster *mon_ = env[current_level].AddMonster(MON_HUMAM_MAN,M_FLAG_EVENT | M_FLAG_NETURALY,(*rit));
					mon_->hp = mon_->hp*rand_int(3,9)/10;
					mon_->FoundTarget(kyoko_, mon_->FoundTime());
					mon_->s_fear = 20+randA(20);
					i--;
				}
			}
			kyoko_->CheckSightNewTarget();
		}		
		return 1;
	case EVL_AUTUMN:
		{
			int rand_ = randA(1);
			env[current_level].MakeFloorEffect(event_->position,&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,rand_int(50,100),NULL);
		}
		return 1;
	case EVL_SUKIMA:
		{
			textures* t_ = &img_effect_schema[randA(2)];
			env[current_level].MakeFloorEffect(event_->position,t_,t_,FLOORT_SCHEMA,2,NULL);
		}
		return 0;
	case EVL_RUN_FAIRY:
		{
			monster *sunny_ = env[current_level].AddMonster(MON_SUNNY,M_FLAG_EVENT,coord_def(1,0)+event_->position);
			monster *star_ = env[current_level].AddMonster(MON_STAR,M_FLAG_EVENT,coord_def(-1,0)+event_->position);
			monster *lunar_ = env[current_level].AddMonster(MON_LUNAR,M_FLAG_EVENT,coord_def(0,0)+event_->position);
			
			sunny_->s_fear = 30+randA(20);
			star_->s_fear = 30+randA(20);
			lunar_->s_fear = 30+randA(20);
			char temp[100];
			sprintf(temp,"%s%s���ƴ�. \"������!\"",star_->GetName()->name.c_str(), star_->GetName()->name_is(true));
			printlog(temp,true,false,false,CL_speak);

			sunny_->SetInvisible(10);
			lunar_->s_confuse = 5;
			star_->SetHaste(10);
			
		}
		return 1;
	case EVL_SCALET_TRAP:
		{
			env[current_level].dgtile[event_->position.x-4][event_->position.y+1].tile = DG_OPEN_DOOR;
			env[current_level].dgtile[event_->position.x-2][event_->position.y+1].tile = DG_OPEN_DOOR;
			env[current_level].dgtile[event_->position.x-4][event_->position.y-1].tile = DG_OPEN_DOOR;
			env[current_level].dgtile[event_->position.x-2][event_->position.y-1].tile = DG_OPEN_DOOR;
			
			env[current_level].dgtile[event_->position.x+1][event_->position.y].tile = DG_GLASS;
			
			printlog("�������۵�. Ĩ���ڸ� ó���϶�!",true,false,false,CL_small_danger);
			env[current_level].MakeNoise(event_->position,8,NULL);
		}
		return 1;
	case EVL_KOGASATIME:
		{			
			for(int i=-3;i<=3;i++)
			{
				if(i!=0)	
					env[current_level].dgtile[event_->position.x+i][event_->position.y+1].tile = DG_FLOOR;
			}
			for(int i = 0; i<5 ; i++)
			{
				for(int j = 0; j<2; j++)
				{
					env[current_level].dgtile[event_->position.x+4*(j*2-1)][event_->position.y+i*2].tile = DG_OPEN_DOOR;
				}
			}
			
			for(int i = 0; i<3 ; i++)
			{
				for(int j = 0; j<3; j++)
				{
					if(i!=1 || j!=1)
						env[current_level].dgtile[event_->position.x-1+i][event_->position.y+4+j].tile = DG_GLASS;
				}
			}
			printlog("It's SURPRISE TIME!!",true,false,false,CL_small_danger);
			env[current_level].MakeNoise(event_->position,16,NULL);
			you.resetLOS();
			MoreWait();
			printlog("...�׷��� �ڰ���� ���� �߸��Ǿ����� ������.",true,false,false,CL_normal);
		}
		return 1;
	default:
		break;
	}

	return 0;
}