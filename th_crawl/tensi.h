//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: tensi.h
//
// ����: �ٽ� Ŭ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __TENSI_H__
#define  __TENSI_H__

enum tensi_do_list
{
	TENSI_NOTHING,
	TENSI_POTION,
	TENSI_SUMMON,
	TENSI_TELE,
	TENSI_EARTHQUAKE,
	TENSI_MUNYUM,
	TENSI_BURST

};

int GetHazard(); //������ ���赵�� ���
void tensi_action();

const char* tensi_talk(bool good_, tensi_do_list list_);


#endif // __TENSI_H__