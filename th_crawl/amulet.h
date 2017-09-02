//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: amulet.h
//
// ����: �ƹķ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __AMULET_H__
#define  __AMULET_H__


enum amulet_type
{
	AMT_PERFECT = 0, //��������, 100%�� �Ǹ� ��Ȱ
	AMT_BLOSSOM, //�����, 100%�� �Ǹ� ���ݹߵ�
	AMT_TIMES, //����, 100%�� �Ǹ� ����
	AMT_FAITH, //�ž�, 100%�� �Ǹ� �ڵ����� �ž� ����
	AMT_WAVE, //����, 100%�� �Ǹ� ���ΰ���
	AMT_SPIRIT, //�ŷ�, 100%�� �Ǹ� ����ī�� ����
	AMT_GRAZE, //�׷�����, 100%�� �Ǹ� �׷��������, �ߵ��� �ټ�ȸ��
	AMT_WEATHER, //����, 100%�� �Ǹ� ü���������. ���� ȸ����밡��
	AMT_POPULAR, //�α⵵, 100%�� �Ǹ� 
	AMT_OCCULT, //����Ʈ, 100%�� �Ǹ� ��ȯ�� �߹氡��
	AMT_MAX
};



extern char *amulet_uniden_string[AMT_MAX];
extern const char *amulet_iden_string[AMT_MAX];


int isAmuletGotValue(amulet_type amulet_);
amulet_type goodbadamulet(int good_bad);
int isGoodAmulet(amulet_type kind, int value);
bool equipamulet(amulet_type kind, int value); //���ϰ�: �ĺ��� true �̽ĺ��� false
bool unidenequipamulet(amulet_type kind, int value); //���ϰ�: �ĺ��� true �̽ĺ��� false

#endif // __AMULET_H__
