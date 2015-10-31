//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: skill.h
//
// ����: skill����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SKILL_H__
#define  __SKILL_H__

#include "enum.h"
#include "d3dUtility.h"

typedef struct skill_exp_infor
{
	int level;
	int exper;
	int aptit;
	bool onoff;
	skill_exp_infor():level(0), exper(0), aptit(100), onoff(false)
	{}
}skill_exp_infor;

int AptCal(int aptitu_);
int need_skill_exp(int level, int aptit);
int exp_to_skill_exp(int level);
int skill_exp_penalty(int total_skill_exp);
char* skill_string(skill_type skill);
int GetSkillPercent(const skill_exp_infor &skill);
//int GetSkillDisplay(int aptit_);
D3DCOLOR GetSkillColor(int aptit_);


extern int aptitude[TRI_MAX][SKT_MAX];
extern int exp_aptitude[TRI_MAX];


#endif // __SKILL_H__