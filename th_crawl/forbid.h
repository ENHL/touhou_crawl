//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: forbid.h
//
// ����: ���������� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "common.h"


class forbid
{
public:
	coord_def position;
	bool big;
	bool change;
	list<coord_def> stack;
	forbid() :position(), big(true), change(true){}
	forbid(coord_def position_) :position(position_), big(true), change(true) {}
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);


	void setChange(coord_def position);
	void reset();
	void removeArea();
};
