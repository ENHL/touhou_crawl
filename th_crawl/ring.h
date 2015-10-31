//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: ring.h
//
// ����: ���� �ƹķ� ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __RING_H__
#define  __RING_H__


#include "player.h"

extern char *ring_uniden_string[RGT_MAX];
extern const char *ring_iden_string[RGT_MAX];

extern char *amulet_uniden_string[AMT_MAX];
extern const char *amulet_iden_string[AMT_MAX];


int isRingGotValue(ring_type ring_);
ring_type goodbadring(int good_bad);
int isGoodRing(ring_type kind, int value);
bool equipring(ring_type kind, int value); //���ϰ�: �ĺ��� true �̽ĺ��� false
bool unidenequipring(ring_type kind, int value);

int isAmuletGotValue(amulet_type amulet_);
amulet_type goodbadamulet(int good_bad);
int isGoodAmulet(amulet_type kind, int value);
bool equipamulet(amulet_type kind, int value); //���ϰ�: �ĺ��� true �̽ĺ��� false
bool unidenequipamulet(amulet_type kind, int value); //���ϰ�: �ĺ��� true �̽ĺ��� false


#endif // __RING_H__