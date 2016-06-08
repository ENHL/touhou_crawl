//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: dump.h
//
// ����: �����ؿ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DUMP_H__
#define  __DUMP_H__


enum dump_action_type
{
	DACT_NONE = -1,
	DACT_MELEE,
	DACT_SHOOT,
	DACT_SPELL,
	DACT_INVOKE,
	DACT_EVOKE,
	DACT_USE,
	DACT_MAX
};

class action_class
{
public:
	dump_action_type type;
	string name;
	int num[27];
	
	action_class();
	action_class(dump_action_type type_, string name_, int level_);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	void plus(int level_){num[level_-1]++;}
};

const char* GetDumpActionString(dump_action_type type_);


bool Dump(int type);


#endif // __DUMP_H__
