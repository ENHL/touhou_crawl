//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: potion.h
//
// ����: potion���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __POTION_H__
#define  __POTION_H__


#include "player.h"
potion_type goodbadpotion(int good_bad);
extern const char *potion_uniden_string[PT_MAX]; //�������Ʈ��
extern const char *potion_iden_string[PT_MAX];
int isGoodPotion(potion_type kind);
void drinkpotion(potion_type kind, bool waste_);

#endif // __POTION_H__