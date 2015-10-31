//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: scroll.h
//
// ����: scroll���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SCROLL_H__
#define  __SCROLL_H__


#include "player.h"
#include "item.h"

scroll_type goodbadscroll(int good_bad);

extern char *scroll_uniden_string[SCT_MAX]; //��ũ�� ��Ʈ��
extern const char *scroll_iden_string[SCT_MAX];

int isGoodScroll(scroll_type kind);
void readscroll(scroll_type kind);

#endif // __SCROLL_H__