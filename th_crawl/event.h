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
	EVL_BAMBOO, //�̱����׸�
	EVL_LUNATICTIME, //�糪ƽ Ÿ��!
	EVL_KOGASA, //Ű���޸� �����ϴ� �ڰ���
	EVL_NOISE//����
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
	int action(int delay_);
};
#endif // __EVENT_H__