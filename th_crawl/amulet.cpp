//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: amulet.cpp
//
// ����: ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "amulet.h"
#include "common.h"

char *amulet_uniden_string[AMT_MAX] =
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

const char *amulet_iden_string[AMT_MAX] =
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
	return 1.0f;
}
bool isCanCharge(amulet_type kind)
{
	return true;
}