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

int EventOccur(int id, events* event_);

void bamboo_count(int num);

events::events()
:id(0),position(),type(EVT_ABOVE),prev_sight(false)
{
}

events::events(int id_, coord_def position_, event_type type_, int count_)
:id(id_),position(position_),type(type_),prev_sight(false), count(count_)
{
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
		printlog("ī���ڴ� ���ߴ� : wŰ�� ����, WŰ�� ������, iŰ�� ����, dŰ�� �������.",true,false,false,CL_warning);\
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
		printlog("ī���ڴ� ���ߴ� : ������ ������ �ֹ�������ų�� 1���̻� �ʿ�����.",true,false,false,CL_warning);
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
	case EVL_BAMBOO:
		{			
			bamboo_count(current_level);
		}
		return 0;
	default:
		break;
	}

	return 0;
}