//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: debuf.h
//
// ����: ����� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DEBUF_H__
#define  __DEBUF_H__

#include "skill_use.h"
#include "common.h"

class unit;

unit* DebufBeam(spell_list spell_, unit* order, coord_def target);
unit* DebufBeam(skill_list skill_, unit* order, coord_def target);
int GetDebufPower(spell_list skill, int power_);//������� �Ŀ�
int GetDebufPower(skill_list skill, int power_);//������� �Ŀ�(��ų��)


#endif // __DEBUF_H__