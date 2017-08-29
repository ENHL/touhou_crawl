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


int isRingGotValue(ring_type ring_);
ring_type goodbadring(int good_bad);
int isGoodRing(ring_type kind, int value);
int isPickableRIng(ring_type kind); //2���̻� ��� �Ǵ� ��
bool equipring(ring_type kind, int value); //���ϰ�: �ĺ��� true �̽ĺ��� false
bool unidenequipring(ring_type kind, int value);



#endif // __RING_H__