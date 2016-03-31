//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: skill.cpp
//
// ����: skill����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "skill.h"
#include "player.h"

//50 60 70 84 100 120 140 170 200 250

int aptitude[TRI_MAX][SKT_MAX]=
{
//			 ����|�Ǽ�|�ܰ�|���|�б�|����| â |ź��|ȸ��|����|����|����|����|ȭ��|�ñ�|����|���|���|����|����|��ȯ|����|�ߵ�|
/*�ΰ�*/	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},//�ΰ�
/*������*/	{ -2,  -2,  -1,  -2,  -1,  -3,  -3,   1,   2,   2,  -2,  -2,   3,   1,   1,   1,   1,   1,   1,   1,   1,   1,  -1},//������
/*����*/	{ -3,  -2,   1,  -2,  -3,  -3,  -1,   2,   3,   3,  -3,  -3,   1,   2,   2,   2,   3,   2,  -2,  -2,  -2,   1,  -2},//����
/*ī����*/{  1,  -1,   0,   0,   2,   1,   1,   1,   2,   0,  -2,  -1,  -1,  -2,  -2,  -3,   2,   1,  -2,  -1,  -1,   0,   0},//ī���ٱ�
/*����ٱ�*/{  2,   0,   0,   2,   2,   2,   1,   1,  -1,  -3,   3,   3,  -3,  -2,  -2,   0,  -2,  -2,   0,  -2,  -2,  -2,   1},//����ٱ�
/*ı��*/	{  1,   2,  -2,   0,   1,  -1,   3,   0,   2,   0,  -2,  -2,   1,  -4,   2,  -2,   0,   0,  -1,  -1,   0,   0,   2},//ı��
/*������*/{ -1,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -2,  -2,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   1,  -2,   0,  -1,   0},//�����𰡹�
/*����*/	{  3,   0,  -2,  -1,   0,  -1,  -2,  -2,  -1,  -4,  -4,  -3,  -3,  -2,  -2,  -1,  -2,  -2,  -2,  -3,  -2,  -3,  -1},//����
/*�ݿ�*/	{  0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,  -1,  -1,  -1,  -1,   0,  -1,  -1,   0,  -1,   0},//�ݿ�
/*����*/	{ -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -1,   4,  -5,  -2,  -1,  -1,   0,  -2,   0,   0,  -3,   3,   1,   2,  -2},//����
/*�����̾�*/{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2} //�����̾�
};
int exp_aptitude[TRI_MAX]=
{
/*�ΰ�*/	100,
/*������*/	140,
/*����*/	130,
/*ī����*/130,	
/*����ٱ�*/120,
/*ı��*/	120,
/*������*/150,
/*����*/	110,
/*�ݿ�*/	160,
/*����*/	150,
/*�����̾�*/130
};



int AptCal(int aptitu_)
{
	switch(aptitu_)
	{
	case -5:
		return 250;
	case -4:
		return 200;
	case -3:
		return 170;
	case -2:
		return 140;
	case -1:
		return 120;
	case 0:
	default:
		return 100;
	case 1:
		return 84;
	case 2:
		return 70;
	case 3:
		return 60;
	case 4:
		return 50;
	}
}


int need_skill_exp(int level, int aptit)
{ 
	if(level<0) return 0;
	return (200+(level)*(80+(level-1)*20))*aptit/100;
}

int exp_to_skill_exp(int level)
{
	int exp_ = (level<=10?max(1,level):(level-10+7)*(level-10)/2+10);
	int exp2_ = skill_exp_penalty(you.total_skill_exp);
	exp_ += (exp2_<=10?exp2_: (exp2_-10+7)*(exp2_-10)/2+11);
	if(exp_>250)
		exp_ = 250;
	//exp_ -= randA(4);
	if(exp_<=0)
		exp_ = 1;
	return exp_;
}

int skill_exp_penalty(int total_skill_exp)
{
	int penalty_ = 0;
	int exp_ = (total_skill_exp-2000);
	if(total_skill_exp < 33500)
	{
		while(exp_>0)
		{
			exp_ -= (penalty_>13?13:penalty_)*300+300;
			penalty_++;
		}
	}
	else
		penalty_ = (total_skill_exp - 33500)/4200+15;

	return penalty_;
}

char* skill_string(skill_type skill)
{
	switch(skill)
	{
	case SKT_FIGHT:
		return "����";
		break;
	case SKT_UNWEAPON:
		return "�Ǽհ���";
		break;
	case SKT_SHORTBLADE:
		return "�ܰ�";
		break;
	case SKT_LONGBLADE:
		return "���";
		break;
	case SKT_MACE:
		return "�б�";
		break;
	case SKT_AXE:
		return "����";
		break;
	case SKT_SPEAR:
		return "â";
		break;
	//case SKT_BOW:
	//	return "Ȱ";
	//	break;
	case SKT_TANMAC:
		return "ź��";
		break;
	case SKT_DODGE:
		return "ȸ��";
		break;
	case SKT_STEALTH:
		return "����";
		break;
	case SKT_ARMOUR:
		return "����";
		break;
	case SKT_SHIELD:
		return "����";
		break;
	//case SKT_BACKSTAB:
	//	return "�Ͻ�";
	//	break;
	//case SKT_TRAP:
	//	return "������";
	//	break;
	case SKT_SPELLCASTING:
		return "�ֹ�����";
		break;
	//case SKT_ENCHARM:
	//	return "��ȭ";
	//	break;
	case SKT_FIRE:
		return "ȭ������";
		break;
	case SKT_COLD:
		return "�ñ⸶��";
		break;
	case SKT_EARTH:
		return "��������";
		break;
	case SKT_AIR:
		return "��⸶��";
		break;
	case SKT_CONJURE:
		return "�ı�����";
		break;
	case SKT_ALCHEMY:
		return "���ݼ�";
		break;
	case SKT_MENTAL:
		return "���Ÿ���";
		break;
	case SKT_SUMMON:
		return "��ȯ����";
		break;
	case SKT_TRANS:
		return "�ð�����";
		break;
	//case SKT_WATER:
	//	return "������";
	//	break;
	//case SKT_POISON:
	//	return "������";
	//	break;
	//case SKT_ELEC:
	//	return "���⸶��";
	//	break;
	case SKT_EVOCATE:
		return "�ߵ�";
		break;
	default:
		return "�˼�����";
		break;
	}
}

int GetSkillPercent(const skill_exp_infor &skill)
{
	int max_exp = need_skill_exp(skill.level, AptCal(skill.aptit))-need_skill_exp(skill.level-1, AptCal(skill.aptit));
	int cur_exp = skill.exper - need_skill_exp(skill.level-1, AptCal(skill.aptit));
	return cur_exp*100/max_exp;
}
//int GetSkillDisplay(int aptit_)
//{
//	if(aptit_<=50)
//		return 4;
//	else if(aptit_<=60)
//		return 3;
//	else if(aptit_<=70)
//		return 2;
//	else if(aptit_<=84)
//		return 1;
//	else if(aptit_<=100)
//		return 0;
//	else if(aptit_<=120)
//		return -1;
//	else if(aptit_<=140)
//		return -2;
//	else if(aptit_<=170)
//		return -3;
//	else if(aptit_<=200)
//		return -4;
//	else if(aptit_<=250)
//		return -5;
//	else
//		return -6;
//} 

D3DCOLOR GetSkillColor(int aptit_)
{
	switch(aptit_)
	{
	case -5:
		return D3DCOLOR_XRGB(255,0,0);
		break;
	case -4:
		return D3DCOLOR_XRGB(255,50,50);
		break;
	case -3:
		return D3DCOLOR_XRGB(255,100,100);
		break;
	case -2:
		return D3DCOLOR_XRGB(255,150,150);
		break;
	case -1:
		return D3DCOLOR_XRGB(255,200,200);
		break;
	case 0:
	default:
		return D3DCOLOR_XRGB(255,255,255);
		break;
	case 1:
		return D3DCOLOR_XRGB(200,200,255);
		break;
	case 2:
		return D3DCOLOR_XRGB(150,150,255);
		break;
	case 3:
		return D3DCOLOR_XRGB(100,100,255);
		break;
	case 4:
		return D3DCOLOR_XRGB(50,50,255);
		break;
	}
}