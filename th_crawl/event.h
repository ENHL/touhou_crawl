//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: event.h
//
// ����: �̺�Ʈ Ŭ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EVENT_H__
#define  __EVENT_H__

#include "common.h"
#include "enum.h"

enum event_list
{
	EVL_KISME=100,
	EVL_SIGHT_P, //�þ߿� ���;� ����� P
	EVL_FLOOR, //���� �ȴ�
	EVL_DREAM_FLOOR, //���� �ȴ�2
	EVL_BAMBOO, //�̱����׸�
	EVL_LUNATICTIME, //�糪ƽ Ÿ��!
	EVL_KOGASA, //Ű���޸� �����ϴ� �ڰ���
	EVL_NOISE,//����
	EVL_VIOLET,//�ʵ� ���̿÷�
	EVL_DREAM_MONSTER,//�帲�� ���� ����
	EVL_DREAM_MESSAGE, //���� ���谡 ��������.
	EVL_AGRO, //��� ���� �÷��̾�� ��׷ΰ� ������.
	EVL_REGEN, //���� ���� (���� ����).
	EVL_REGEN2, //���� ���� (����).
	EVL_ARENA, //�Ʒ���
	EVL_NAMAZ, //������  ������
	EVL_KOISHI,
	EVL_KYOKO, //������ ����
	EVL_AUTUMN, //��ǳ
	EVL_SUKIMA, //��Ű��
	EVL_RUN_FAIRY, //����ġ�� �����
	EVL_SCALET_TRAP, //ȫ���� Ʈ��
	EVL_KOGASATIME //�ڰ��� Ÿ��!
};

class events
{
public:
	int id;
	coord_def position;
	event_type type;
	int count;
	bool prev_sight;

	events();
	events(int id_, coord_def position_, event_type type_, int count_ = -1);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	int start();
	int action(int delay_);
};
#endif // __EVENT_H__