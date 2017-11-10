//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: FSM.cpp
//
// ����: fsmŬ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "FSM.h"

FSMstate::FSMstate(monster_state id_):
NumofTran(0), id(id_)
{
	trans.reserve(32);
}

void FSMstate::AddTransition(monster_state_input input_, monster_state after_)
{
	trans.push_back(state_trans_infor(input_,after_));
	NumofTran++;
}
void FSMstate::DelTransition(monster_state_input input_)
{
	vector<state_trans_infor>::iterator it;
	for(it = trans.begin(); it!=trans.end() ; it++)
	{
		if((*it).input == input_)
		{
			trans.erase(it);
			return;
		}
	}
}

monster_state FSMstate::Transition(monster_state_input input_)
{
	vector<state_trans_infor>::iterator it;
	for(it = trans.begin(); it!=trans.end() ; it++)
	{
		if((*it).input == input_)
		{ 
			return (*it).after;
		}
	}
	return id;
}

FSMclass::FSMclass(monster_state current_state_):
current_state(current_state_)
{
}

void FSMclass::AddState(FSMstate* Newstate_)
{
	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //�̹� �����ϴ� �����ΰ��
	{
		it = state_map.find(Newstate_->GetId());
		if(it != state_map.end())
			return;
	}

	state_map.insert(pair<monster_state,FSMstate*>(Newstate_->GetId(),Newstate_));
}

void FSMclass::DeleteState(monster_state state_)
{
	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //�����ϴ� ���
	{
		it = state_map.find(state_);
		if(it != state_map.end())
		{
			state_map.erase(it);
		}
	}
}


monster_state FSMclass::StateTransition(monster_state_input input_)
{	
	if(!current_state)
		return MS_ERROR;


	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //�����ϴ� ���
	{
		it = state_map.find(current_state);
		if(it != state_map.end())
		{
			FSMstate *pState = (FSMstate*)((*it).second);
			current_state = pState->Transition(input_);
			return current_state;
		}
	}
	return MS_ERROR;
}



//�Ʒ����� ����
FSMstate state_normal(MS_NORMAL);
FSMstate state_sleep(MS_SLEEP);
FSMstate state_atack(MS_ATACK);
FSMstate state_rest(MS_REST);
FSMstate state_follow(MS_FOLLOW);
FSMstate state_find(MS_FIND);


void init_state()
{
	//���� �븻: ���� �߰������ʰ� ������ ����
	state_normal.AddTransition(MSI_FOUND,MS_ATACK);
	state_normal.AddTransition(MSI_ATACKED,MS_ATACK);
	state_normal.AddTransition(MSI_NOISE,MS_ATACK);
	state_normal.AddTransition(MSI_REST,MS_REST);
	state_normal.AddTransition(MSI_SEARCH, MS_FIND);

	//���� ����: �� �ڸ����� �ڴ� ����
	state_sleep.AddTransition(MSI_NOISE,MS_ATACK);
	state_sleep.AddTransition(MSI_ATACKED,MS_ATACK);
	state_sleep.AddTransition(MSI_FOUND,MS_ATACK);
	state_sleep.AddTransition(MSI_WAKE,MS_NORMAL);

	//���� ����: ��ǥ�� ����
	state_atack.AddTransition(MSI_LOST,MS_NORMAL);
	state_atack.AddTransition(MSI_REST,MS_NORMAL);
	state_atack.AddTransition(MSI_SEARCH, MS_FIND);
	
	//���� �޽�: �޽���
	state_rest.AddTransition(MSI_ATACKED,MS_ATACK);
	state_rest.AddTransition(MSI_NOISE,MS_ATACK);
	state_rest.AddTransition(MSI_FOUND,MS_ATACK);
	state_rest.AddTransition(MSI_REST,MS_SLEEP);
	state_rest.AddTransition(MSI_WAKE,MS_NORMAL);

	//���� ����: ������ �÷��̾ ����
	state_follow.AddTransition(MSI_ATACKED,MS_ATACK);
	state_follow.AddTransition(MSI_LOST,MS_NORMAL);
	state_follow.AddTransition(MSI_FOUND,MS_ATACK);

	state_find.AddTransition(MSI_ATACKED, MS_ATACK);
	state_find.AddTransition(MSI_FOUND, MS_ATACK);
	state_find.AddTransition(MSI_LOST, MS_NORMAL);
	state_find.AddTransition(MSI_REST, MS_NORMAL);
	
}

void base_state_setup(FSMclass& state, monster_state first_state)
{
	state.AddState(&state_normal);
	state.AddState(&state_sleep);
	state.AddState(&state_atack);
	state.AddState(&state_rest);
	state.AddState(&state_follow);
	state.AddState(&state_find);

	state.SetState(first_state);
}