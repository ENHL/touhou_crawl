//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: rect.h
//
// ����: �簢�� �ݺ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __RECT_H__
#define  __RECT_H__

#include "common.h"
#include "enum.h"

class rect_iterator //���ϴ� �簢���� ����Ѵ�.
{
	coord_def start;
	coord_def current;
	int x_size;
	int y_size;

public:
	rect_iterator(const coord_def &start_, int x_size, int y_size);
	coord_def rect_iterator::operator *() const;
	const coord_def* rect_iterator::operator->() const;
	rect_iterator& operator ++ ();
	rect_iterator operator ++ (int);
	bool end();
	bool isdiagonal();
};



class rand_rect_iterator //Ư�� �������� ������������ �����س���.
{
	coord_def start;
	int current;
	int x_size;
	int y_size;
	deque<coord_def> dq;

public:
	rand_rect_iterator(const coord_def &start_, int x_size, int y_size, bool no_inside = true);
	coord_def rand_rect_iterator::operator *() const;
	const coord_def* rand_rect_iterator::operator->() const;
	rand_rect_iterator& operator ++ ();
	rand_rect_iterator operator ++ (int);
	bool end() const; 
};


class dif_rect_iterator //Ư�� ��ġ���� ���� �����鼭 �������� �����Ѵ�.
{
	coord_def start;
	int current;
	int distan; //�߾����κ��� �Ÿ�
	deque<coord_def> dq;

public:
	dif_rect_iterator(const coord_def &start_, int distan, bool random_ = false);
	void sort_distan(bool close_); //�������ִ� ������ ����
	coord_def dif_rect_iterator::operator *() const;
	const coord_def* dif_rect_iterator::operator->() const;
	dif_rect_iterator& operator ++ ();
	dif_rect_iterator operator ++ (int);
	bool end() const; 
};


#endif // __RECT_H__