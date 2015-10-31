//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: FSM.h
//
// ����: fsmŬ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __FSM_H__
#define  __FSM_H__

#include "common.h"
#include "enum.h"
#include <map>

typedef struct state_trans_infor//�������� ����
{
	monster_state_input input; //���� �� �ִ� �Է��� ����
	monster_state after; //�Է¿� ���� ��������
	state_trans_infor(monster_state_input input_, monster_state after_)
	{
		input = input_;
		after = after_;
	}
}state_trans_infor;


class FSMstate //�������α׷�����..
{
	unsigned char NumofTran; //�Ͼ �� �ִ� ���������� ����

	vector<state_trans_infor> trans; //�������̿� ���� ����
	monster_state id; //���� ID

public:
	FSMstate(monster_state id_);

	monster_state GetId(){ return id;};
	void AddTransition(monster_state_input input_, monster_state after_); //�������� �߰�
	void DelTransition(monster_state_input input_); //�������� ����
	monster_state Transition(monster_state_input input_); //��������
};



class FSMclass //����Ŭ������ �����ͷ� �Ѱ������� new��ä�� �ѱ�������. Ŭ�����ȿ��� �޸������� ��������.
{
	map<monster_state,FSMstate*> state_map; //���¸� ���� ��
	monster_state current_state;

public:
	FSMclass(monster_state current_state_ = MS_NORMAL);

	monster_state GetState(){return current_state;};
	void SetState(monster_state state_){current_state = state_;};

	void AddState(FSMstate* Newstate_); //�����߰�
	void DeleteState(monster_state state_); //���»���

	monster_state StateTransition(monster_state_input input_); //��������
};


extern FSMstate state_normal;
extern FSMstate state_sleep;
extern FSMstate state_atack;


void init_state();


void base_state_setup(FSMclass& state, monster_state first_state);


#endif // __FSM_H__