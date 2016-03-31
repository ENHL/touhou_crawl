//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: tribe.h
//
// ����: ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "tribe.h"
#include "enum.h"
#include "player.h"
#include "skill.h"
#include "save.h"
#include "skill_use.h"
#include "key.h"
extern HANDLE mutx;



void tribe_property::SaveDatas(FILE *fp)
{
	SaveData<tribe_proper_type>(fp, id);
	SaveData<int>(fp, value);

}
void tribe_property::LoadDatas(FILE *fp)
{
	LoadData<tribe_proper_type>(fp, id);
	LoadData<int>(fp, value);
}



string tribe_property::GetName()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		return "ȭ������";
	case TPT_COLD_RESIST:
		return "�ñ�����";
	case TPT_ELEC_RESIST:
		return "��������";
	case TPT_POISON_RESIST:
		return "������";
	case TPT_STEALTH:
		return "������";
	case TPT_FLY:
		return "����";
	case TPT_SWIM:
		return "����";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "�Ŵ������";
			case -1:
				return "�̴ϻ�����";
			default:
				return "���׻�����";
			}
		}
	case TPT_HORN:
		return "��";
	case TPT_GHOST_FOOT:
		return "���ɴٸ�";
	case TPT_CHEUKUMOGAMI:
		return "����𰡹�";
	}
	return "����Ư��";
}
string tribe_property::GetInfor()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		return "����� ȭ���� ���ϴ�.";
	case TPT_COLD_RESIST:
		return "����� �ñ⿡ ���ϴ�.";
	case TPT_ELEC_RESIST:
		return "����� ���⿡ ���ϴ�.";
	case TPT_POISON_RESIST:
		return "����� ���� ���ϴ�.";
	case TPT_STEALTH:
		return "����� �����ϰ� �����δ�.";
	case TPT_FLY:
		return "����� ū ������ ������.";
	case TPT_SWIM:
		return "����� ������ �� �ִ�.";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "����� ������ Ŀ�� ������ ���� �� �´´�.";
			case -1:
				return "����� ������ �۾Ƽ� ������ ���� �� �´´�.";
			default:
				return "����� ������ ���״�.";
			}
		}
	case TPT_HORN:
		return "����� �Ӹ��� ���� �޷��ִ�.";
	case TPT_GHOST_FOOT:
		return "����� �����̱⿡ �ٸ��� ����.";
	case TPT_CHEUKUMOGAMI:
		return "����� ��ü�� �����̴�.(�̱���)";
	}
	return "�� Ư���� ���״�.";
}
string tribe_property::GetDetail()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		return "ȭ�� ������ 1�ܰ� �����Ѵ�.";
	case TPT_COLD_RESIST:
		return "�ñ� ������ 1�ܰ� �����Ѵ�.";
	case TPT_ELEC_RESIST:
		return "���� ������ �����Ѵ�.";
	case TPT_POISON_RESIST:
		return "�� ������ �����Ѵ�.";
	case TPT_STEALTH:
		return "���е��� ������.";
	case TPT_FLY:
		return "������ �ɷ��� ���� Ű�� �� �� �ִ�.";
	case TPT_SWIM:
		return "���� �������� ����ó�� �̵��� �ٴ� �� �ִ�.";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "�κ� �̿��� ���� ���� ���� �� ����.";
			case -1:
				return "�κ� �̿��� ���� ���� ���� �� ����.";
			default:
				return "�κ� �̿��� ���� ���� ���Ա� ���� ���״�.\n�����ڿ��� �Ű�����.";
			}
		}
	case TPT_HORN:
		return "�Ӹ����� �� �� ����. ���� �Կ� ���� ��ġ�� ������ �߰��ȴ�.\n�� ���ݸ��� ����Ȯ���� ��ġ�Ⱑ ������ �Ǽ����� �οﶧ �� ���� Ȯ���� ������.";
	case TPT_GHOST_FOOT:
		return "�ٸ����� �� �� ����.";
	case TPT_CHEUKUMOGAMI:
		return "����� ��ü�� ������ ���� �� ����.\n����� ��ü�� �տ� ��� ������ �� ���� ������ ��ų�� 5�����ϴ� ���ʽ��� �޴´�.";
	}
	return "�� Ư���� �����̹Ƿ� ������ü�� �ؾ��̴�.\n�����ڿ��� �Ű�����.";
}

void tribe_property::gain(bool gain_)
{
	int value_ = gain_?value:-value;
	switch(id)
	{
	case TPT_FIRE_RESIST:
		you.ResistUpDown(value_,RST_FIRE);
		return;
	case TPT_COLD_RESIST:
		you.ResistUpDown(value_,RST_ICE);
		return;
	case TPT_ELEC_RESIST:
		you.ResistUpDown(value_,RST_ELEC);
		return;
	case TPT_POISON_RESIST:
		you.ResistUpDown(value_,RST_POISON);
		return;
	case TPT_STEALTH:
		return;
	case TPT_FLY:
		{
			int temp = you.Ability(SKL_LEVITATION_OFF,false,true);
			you.Ability(SKL_LEVITATION,false,value<=0,value>0?(temp>0?temp+1:0):0);
			if(value<=0 && temp == 1 && you.s_levitation)
			{
				you.s_levitation=0; 
			}
			return;
		}
	case TPT_SWIM:
		return;
	case TPT_SIZE:
		return;
	case TPT_HORN:
		return;
	case TPT_GHOST_FOOT:
		return;
	case TPT_CHEUKUMOGAMI:
		return;
	}
}


void PropertyView()
{
	int i=0;
	changedisplay(DT_PROPERTY);
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
			if(num < you.property_vector.size())
			{
				WaitForSingleObject(mutx, INFINITE);
				SetText() = "Ư�� : " + you.property_vector[num].GetName();
				SetText() += "\n\nȿ�� : " + you.property_vector[num].GetDetail();
				changedisplay(DT_TEXT);
				ReleaseMutex(mutx);
				waitkeyinput();
				changedisplay(DT_PROPERTY);
				changemove(0);
			}
			else
				break;
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}




void SetTribe(tribe_type select_)
{
	switch(select_)
	{
	case TRI_HUMAN:

		break;
	case TRI_WIZARD:
		you.max_hp-=2;
		you.max_mp+=1;
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(2,STAT_INT);
		break;
	case TRI_FAIRY:
		you.max_hp-=2;
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(1,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_SIZE,-1);

		break;
	case TRI_CROWTENGU:
		you.max_hp+=1;
		you.StatUpDown(-1,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_FLY,1);
		break;
	case TRI_WOLFTENGU:
		you.max_hp+=2;
		you.StatUpDown(2,STAT_STR);
		you.StatUpDown(-1,STAT_INT);
		you.StatUpDown(-1,STAT_DEX);
		break;
	case TRI_KAPPA:
		you.max_hp+=1;
		you.SetProperty(TPT_SWIM,1);
		break;
	case TRI_CHEUKUMOGAMI:
		you.max_hp-=1;
		you.StatUpDown(-1,STAT_STR);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_POISON_RESIST,1);
		you.SetProperty(TPT_CHEUKUMOGAMI,1);
		break;
	case TRI_ONI:
		you.max_hp+=3;
		you.StatUpDown(3,STAT_STR);
		you.StatUpDown(-2,STAT_INT);
		you.StatUpDown(-1,STAT_DEX);
		you.SetProperty(TPT_SIZE,1);
		you.SetProperty(TPT_HORN,1);
		break;
	case TRI_HALFYOKAI:
		break;
	case TRI_WRAITH:
		you.SetProperty(TPT_COLD_RESIST,1);
		you.SetProperty(TPT_STEALTH,1);
		you.SetProperty(TPT_POISON_RESIST,1);
		you.SetProperty(TPT_GHOST_FOOT,1);
		break;
	case TRI_VAMPIRE:
		break;
	}
	for(int i=0;i<SKT_MAX;i++)
		you.skill[i].aptit = aptitude[select_][i];
	you.exper_aptit = exp_aptitude[select_];
}

void LevelUpTribe(int level_)
{
	switch(you.tribe)
	{
	case TRI_HUMAN:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		break;
	case TRI_WIZARD:
		if(level_%4 == 0)
		{
			you.StatUpDown(1,STAT_INT);
		}
		you.max_mp++;
		you.mp++;
		if(level_%3 != 0)
		{
			you.max_hp--;
			you.hp--;
		}
		break;
	case TRI_FAIRY:
		if(level_%5 == 0)
		{
			(randA(1)?you.StatUpDown(1,STAT_DEX):you.StatUpDown(1,STAT_INT));
		}
		if(level_%2 == 0)
		{
			you.max_mp++;
			you.mp++;
		}
		you.max_hp--;
		you.hp--;
		break;
	case TRI_CROWTENGU:
		if(level_%5 == 0)
		{
			(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX));
		}
		if(level_%3 == 0)
		{
			you.max_hp++;
			you.hp++;
		}
		break;
	case TRI_WOLFTENGU:
		if(level_%4 == 0)
		{
			you.StatUpDown(1,STAT_STR);
		}
		if(level_%2 == 0)
		{
			you.max_hp++;
			you.hp++;
		}
		if(level_%3 == 0)
		{
			you.max_mp--;
			you.mp--;
		}
		break;
	case TRI_KAPPA:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		if(level_%3 == 0)
		{
			you.max_hp++;
			you.hp++;
		}
		break;
	case TRI_CHEUKUMOGAMI:
		if(level_%3 == 0)
		{
			you.max_hp--;
			you.hp--;
		}
		break;
	case TRI_ONI:
		if(level_%3 == 0)
		{
			you.StatUpDown(1,STAT_STR);
		}
		you.max_hp++;
		you.hp++;
		if(level_%2 == 0)
		{
			you.max_mp--;
			you.mp--;
		}
		break;
	case TRI_HALFYOKAI:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		break;
	case TRI_WRAITH:
		break;
	case TRI_VAMPIRE:
		break;
	}
}