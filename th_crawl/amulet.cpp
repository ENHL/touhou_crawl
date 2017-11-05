//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: amulet.cpp
//
// ����: ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "amulet.h"
#include "common.h"
#include "const.h"
#include "display.h"
#include "player.h"
#include "skill_use.h"
#include "environment.h"


char *amulet_uniden_string[AMT_MAX+2] =
{
	"�㰡 �׷��� ",
	"�Ұ� �׷��� ",
	"ȣ���̰� �׷��� ",
	"������ �׷��� ",
	"�䳢�� �׷��� ",
	"���� �׷��� ",
	"���� �׷��� ",
	"���� �׷��� ",
	"�����̰� �׷��� ",
	"���� �׷��� "
};

const char *amulet_iden_string[AMT_MAX+2] =
{
	"���������� ",
	"������� ",
	"������ ",
	"�ž��� ",
	"������ ",
	"�ŷ��� ",
	"�׷������� ",
	"������ ",
	"�α⵵�� ",
	"����Ʈ�� "
};



int isAmuletGotValue(amulet_type amulet_)
{
	return 0;
	/*return ( amulet_ == AMT_AC || amulet_ == AMT_EV);*/
}

amulet_type goodbadamulet(int good_bad)
{
	return (amulet_type) randA(AMT_MAX - 1);
}

int isGoodAmulet(amulet_type kind, int value)
{
	return 1;
}

bool equipamulet(amulet_type kind, int value)
{
	return false;
}
bool unidenequipamulet(amulet_type kind, int value)
{
	return false;
}
float getAmuletCharge(amulet_type kind)
{
	switch (kind)
	{
	case AMT_PERFECT:
		return 2.0f;
	case AMT_POPULAR:
		return 1.5f;
	case AMT_BLOSSOM:
	case AMT_TIMES:
	case AMT_FAITH:
	case AMT_SPIRIT:
	case AMT_GRAZE:
	case AMT_OCCULT:
	case AMT_WEATHER:
		return 1.0f;
	case AMT_WAVE:
		return 0.5f;

	}
}
bool isCanCharge(amulet_type kind)
{
	switch (kind) {
	case AMT_FAITH:
	case AMT_PERFECT:
		return false;
	}
	return true;
}
bool isCanEvoke(amulet_type kind)
{
	return true;
}
bool chargingFinish(amulet_type kind, int value)
{
	switch (kind)
	{
	case AMT_GRAZE:
		if (value > 0) {
			you.SetGraze(-1);
			int temp = you.Ability(SKL_GRAZE, false, true, 1);
			if (temp) {
				you.Ability(SKL_GRAZE_OFF, false, false, temp);
			}
			enterlog();
		}
		else {
			int temp = you.Ability(SKL_GRAZE_OFF, false, true, 1);
			if (temp) {
				you.Ability(SKL_GRAZE_OFF, false, false, temp);
				//�׷���� �������̸� �׷���� ��������
			} else 
			{
				you.s_graze = 0;
				printlog("�� �̻� ź���� �׷����� ���� �ʴ´�.", true, false, false, CL_blue);
			}
		}
		break;
	case AMT_WEATHER:
		if (value > 0) {
			printlog("������ ���� ü�� ������� �ö󰬴�!", true, false, false, CL_blue);
		}
		else {
			printlog("�� �̻� �������κ��� ������� ���� ���Ѵ�.", true, false, false, CL_blue);
		}
		break;
	case AMT_FAITH:
		if (value > 0) {
			if (you.god == GT_NONE) {
				printlog("����� �ž��� ���⶧���� ���� �žӽ��� �ϴ÷� ���󰬴�.", true, false, false, CL_blue);
				you.resetAmuletPercent(kind);
			}
			else {
				printlog("������ ���� �Ű� �����Ͽ���!", true, false, false, CL_blue);
				if (you.god != GT_SEIJA)
					you.PietyUpDown(10);
				you.GiftCount(10);
				you.resetAmuletPercent(kind);
			}
		}
		break;
	}
	return true;
}

bool skill_soul_shot(int power, unit* order, coord_def target);
bool recharging_scroll(bool pre_iden_, bool ablity_);

bool evokeAmulet(amulet_type kind) 
{

	switch (kind)
	{
	case AMT_PERFECT:
	case AMT_FAITH:
		//�ߵ���������
		break;
	case AMT_BLOSSOM:
		printlog("��! ", false, false, false, CL_white_blue);
		skill_soul_shot(0, &you, you.position);
		break;
	case AMT_TIMES:
		you.SetHaste(rand_int(50, 80));
		break;
	case AMT_WAVE:
		if (env[current_level].isBamboo())
		{
			printlog("���� Ž���� �̱��� �׸����� ȿ���� ���� ���Ѵ�.", true, false, false, CL_normal);
			return false;
		}
		else
		{
			env[current_level].MakeMapping(100);
			printlog("����� ���� ���� �����س´�.", true, false, false, CL_normal);
		}
		break;
	case AMT_SPIRIT:
		return recharging_scroll(true, true);
		break;
	case AMT_GRAZE:
		you.SetSuperGraze(rand_int(10, 15));
		printlog("����� ���������� ȸ�ǿ� ��� �Ű��� ��´�!", false, false, false, CL_white_blue);
		break;
	case AMT_WEATHER:
		printlog("����� ü���� ȸ���ߴ�. ", false, false, false, CL_normal);
		you.HpUpDown(rand_int(10, 15) + you.GetMaxHp()*rand_float(0.15f, 0.25f), DR_NONE);
		break;
	case AMT_POPULAR:
		//???

		//�̱���
		break;
	case AMT_OCCULT:
		//����Ʈ ����

		//�׽�
		//��ô�ͽ�
		//��Ʋ �׸���
		//���ݻ��߽�Ű
		//������
		//.....
		//���� �����ϱ�
		break;
	}
	return true;
}