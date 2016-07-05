//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mainloop.h
//
// ����: �ְ��ӷ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "environment.h"
#include "display.h"
#include "key.h"
#include "save.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"
#include "map.h"
#include "dump.h"
#include "god.h"
#include "throw.h"
#include "skill_use.h"
#include "note.h"
#include "tribe.h"
#include "network.h"





extern bool saveexit;

extern HANDLE mutx;

const char *version_string = "ver0.66";


void Initialize();


void SetJob(job_type select_, string name_);
void TouhouPlayerble(const string name_, bool aptit_);
skill_type itemtoskill(item_type type_);


void Test_char_init(item_type item_, int bonus)
{

	item_infor t;

	t.type = item_;
	t.num = 1;
	t.curse = false;
	t.value3 = (int)(bonus == 6);
	t.value4 = (int)(bonus == 6);
	t.is_pile = false;
	t.name2.name = "";
	t.name2.name_type = true;
	switch(item_)
	{
	case ITM_WEAPON_SHORTBLADE:
		t.value1 = 4;
		t.value2 = 7;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 10;
		t.value8 = 5;
		t.can_throw = true;
		t.image = &img_item_weapon_dagger;
		t.name.name = "���";
		t.name.name_type = false; //true ��ħ����
		t.weight = 2.0f;
		t.value = 50;
		break;
	case ITM_WEAPON_AXE:	
		t.value1 = 2;
		t.value2 = 8;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = true;
		t.image = &img_item_weapon_handaxe;
		t.name.name = "�յ���";
		t.name.name_type = false; //true ��ħ����
		t.weight = 3.0f;
		t.value = 60;
		break;
	case ITM_WEAPON_MACE:
		t.value1 = 4;
		t.value2 = 7;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = false;
		t.image = randA(1)?&img_item_weapon_gohey:&img_item_weapon_gohey2;
		t.name.name = "������";
		t.name.name_type = false; //true ��ħ����
		t.weight = 3.0f;
		t.value = 60;
		break;
	case ITM_WEAPON_SPEAR:
		t.value1 = 2;
		t.value2 = 8;
		t.value5 = 12;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = true;
		t.image = &img_item_weapon_spear;
		t.name.name = "â";
		t.name.name_type = true; //true ��ħ����
		t.weight = 4.0f;
		t.value = 70;
		break;
	}
	item *it;
	if(item_ != ITM_LAST)
	{
		it = env[current_level].MakeItem(you.position,t);
		it->identify = true;
		it->identify_curse = true;
		you.additem(it,false);
		you.equip('a',ET_WEAPON,false);
		env[current_level].DeleteItem(it);
	}


	t.type = ITM_ARMOR_BODY_ARMOUR_0;
	t.num = 1;
	t.curse = false;
	t.value1 = 1;
	t.value2 = 0;
	t.value3 = 0;
	t.value4 = (int)(bonus == 6);
	t.value5 = 0;
	t.value6 = 0;
	t.is_pile = false;
	t.can_throw = false;
	t.image = &img_item_armor_robe;
	t.name.name = "���ູ";
	t.name.name_type = true;
	t.weight = 6.0f;
	t.value = 40;

	it = env[current_level].MakeItem(you.position,t);
	it->identify = true;
	it->identify_curse = true;
	you.additem(it,false);
	you.equiparmor(item_ != ITMS_LAST?'b':'a',false);
	env[current_level].DeleteItem(it);

	t.type = ITM_FOOD;
	t.num = 1;
	t.curse = false;
	t.value1 = 1;
	t.value2 = 0;
	t.value3 = 0;
	t.value4 = 0;
	t.value5 = 100;
	t.value6 = 0;
	t.is_pile = true;
	t.can_throw = false;
	t.image = &img_item_food_bread;
	t.name.name = "��";
	t.name.name_type = true;
	t.weight = 5.0f;
	t.value = 30;
	it = env[current_level].MakeItem(you.position,t);
	you.additem(it,false);
	env[current_level].DeleteItem(it);

	switch(bonus)
	{
	case 1:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 1));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 1));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 3));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_HEAL].iden = true;
		iden_list.potion_list[PT_HEAL_WOUND].iden = true;
		break;
	case 2:		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_MIGHT].iden = true;
		break;
	case 3:		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_HASTE));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_HASTE].iden = true;
		break;
	case 4:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.scroll_list[SCT_TELEPORT].iden = 3;
		iden_list.scroll_list[SCT_IDENTIFY].iden = 3;
		break;
	case 5:	
		it = env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t, 30));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;	
	}


	skill_type s_type_ = (item_ != ITM_LAST)?itemtoskill(item_):SKT_UNWEAPON;


	you.GiveSkillExp(SKT_FIGHT,s_type_==SKT_SHORTBLADE?20:30,false);
	you.GiveSkillExp(s_type_,s_type_==SKT_UNWEAPON?80:s_type_==SKT_SHORTBLADE?30:45,false);
	if(bonus == 5)
		you.GiveSkillExp(SKT_TANMAC,70,false);
	you.GiveSkillExp(SKT_DODGE,50,false);
	if(s_type_==SKT_SHORTBLADE)
	{
		you.GiveSkillExp(SKT_STEALTH,30,false);
		//you.GiveSkillExp(SKT_BACKSTAB,30,false);
	}
}


extern void start_mainmenu();

void charter_selete()
{//�ΰ�,������,����,ī���ٱ�,����ٱ�,ı��,�ݿ�,�����𰡹�,������,����,���, ���䳢, õ��, ����ǻ���, �� ��, ����, �ҷ�
	for(int i = 0; i<MAXLEVEL; i++)
		env[i].floor = i;
	

	WaitForSingleObject(mutx, INFINITE);
	SetText() = "touhou crawl ";
	SetText() += version_string;
	SetText() += "\n����������Ʈ�� ����ũ���� ���ΰ���\n\n";
	if(load_name(user_name_file.c_str()))
	{
		SetText() += "����� �̸��� \"";
		SetText() += you.user_name.name;
		SetText() += "\" �̴�.\n";
	}
	else
	{
		SetText() += "����� �̸��� \"";
		SetText() += you.user_name.name;
		SetText() += "\" �̴�.\n";
		SetText() += "user_name.txt���� ����� �̸��� �ٲ� �� �־�.\n";

	}
	SetDisplayTexture(&img_title);
	ReleaseMutex(mutx);
	waitkeyinput();	
	WaitForSingleObject(mutx, INFINITE);
	SetText() += "�����Ѵ�!\n";
	ReleaseMutex(mutx);
	Sleep(500);
	SetDisplayTexture(NULL);
	
	start_mainmenu();

	//bool main_= true;
	//while(main_)
	//{
	//	main_ =false;
	//	WaitForSingleObject(mutx, INFINITE);
	//	SetText() = "���� �޴�.\n\n\n";
	//	SetText() += "a - ���ӽ���\n";
	//	SetText() += "b - Ʃ�丮��";
	//	ReleaseMutex(mutx);
	//	bool loop_= true;
	//	while(loop_)
	//	{
	//		int select = waitkeyinput(true);
	//		if(select>='a' && select<='b')
	//		{
	//			switch(select)
	//			{
	//			case 'a':
	//				tutorial = false;
	//				loop_ = false;
	//				break;
	//			case 'b':
	//				tutorial = true;
	//				loop_ = false;
	//				break;
	//			break;
	//			}
	//		}
	//	}

	//	if(!tutorial && !load_data(save_file.c_str()))
	//	{
	//		bool sub_main_ = true;
	//		while(sub_main_)
	//		{
	//			sub_main_ = false;
	//			bool touhouable_ = false;
	//			WaitForSingleObject(mutx, INFINITE);
	//			SetText() = "���� ���� �����Ұž�?\n\n\n";

	//			SetText() += "a - ���� ĳ���ͷ� �����ϱ� (EASY)\n\n";
	//			SetText() += "b - ���� ĳ���� �����ϱ� (NORMAL)\n\n";
	//			ReleaseMutex(mutx);
	//	
	//			while(1)
	//			{
	//				int select = waitkeyinput();
	//				if(select>='a' && select<='b')
	//				{
	//					WaitForSingleObject(mutx, INFINITE);
	//					if( select == 'a')
	//					{
	//						SetText() += "���� ���� ���� ��Ź��.\n";
	//						touhouable_ = true;
	//					}
	//					else if(select == 'b')
	//					{
	//						SetText() += "������. ��������.\n";
	//						touhouable_ = false;
	//					}
	//					else if(select == VK_ESCAPE)
	//					{
	//						ReleaseMutex(mutx);
	//						main_ = true;
	//						break;
	//					}

	//					ReleaseMutex(mutx);
	//					Sleep(300);
	//					break;
	//				}
	//			}
	//			if(main_)
	//				break;

	//			if(touhouable_)
	//			{
	//				WaitForSingleObject(mutx, INFINITE);
	//				SetText() = "ĳ���͸� �����մϴ�.\n\n\n\n";
	//				SetText() += "a - �ΰ� ���� ���̹�\n\n";
	//				SetText() += " ��Ƽ���� �� ������. ����� ȣ�ֹ���� ��� ���� ��������!\n";
	//				SetText() += " �������ʽ�) ź������ +3, ȸ������ +3\n";
	//				SetText() += " ���ʽ�) ����, 24���� ȣ�־ƹķ�, ���� �ϰ� ���������ʴ´�.\n\n\n";
	//				SetText() += "b - �ΰ� ������ ������\n\n";
	//				SetText() += " : ���Ѱ��� & ��ð�����. ź���� �Ŀ�! �����ڸ��� ������!\n";
	//				SetText() += " �������ʽ�) �ֹ��������� +2, �ı��������� +3, ȸ������ +1\n";
	//				SetText() += " ���ʽ�) +2,+2 ���ڷ�, ������ ����, �ı��� ����å\n\n\n";
	//				SetText() += "c - �ΰ� ���� �糪��\n\n";
	//				SetText() += " : ������ & ������ �۷���. �����ڴ��� �������!\n";
	//				SetText() += " �������ʽ�) �������� +2, ȸ������ +1, �ߵ����� +3\n";
	//				SetText() += " ���ʽ�)  ������ ����ī��(9), ����� ����ī��(9), �����ڸ� �ϰ� �����Ѵ�.\n\n\n";
	//				SetText() += "d - ����ٱ� ���� �����\n\n";
	//				SetText() += " : �ڵ�Ž�� & �ڵ�������. O�� TAB�� ����� �����������\n";
	//				SetText() += " �������ʽ�) ������� +1\n";
	//				SetText() += " ���ʽ�) +2,+2 �����, +2 ö����, +2 �߰� �߰���, ��óġ�Ṱ�� 2��, ������ 2��, ������ ����\n\n\n";

	//				ReleaseMutex(mutx);
	//		
	//				while(1)
	//				{
	//					int select = waitkeyinput();
	//					if(select>='a' && select<='d')
	//					{
	//						switch( select )
	//						{
	//						case 'a':						
	//						default:
	//							you.tribe = TRI_HUMAN;
	//							you.job = JOB_SHAMAN;
	//							you.char_name.name = "���̹�";
	//							you.char_name.name_type = false;
	//							you.image = &img_play_reimu;
	//							break;
	//						case 'b':
	//							you.tribe = TRI_HUMAN;
	//							you.job = JOB_WIZARD;
	//							you.char_name.name = "������";
	//							you.char_name.name_type = false;
	//							you.image = &img_play_marisa;
	//							break;
	//						case 'c':
	//							you.tribe = TRI_HUMAN;
	//							you.job = JOB_SHAMAN;
	//							you.char_name.name = "�糪��";
	//							you.char_name.name_type = false;
	//							you.image = &img_play_sanae;
	//							break;
	//						case 'd':
	//							you.tribe = TRI_WOLFTENGU;
	//							you.job = JOB_WARRIOR;
	//							you.char_name.name = "�����";
	//							you.char_name.name_type = false;
	//							you.image = &img_play_momizi;
	//							break;
	//						}						
	//						WaitForSingleObject(mutx, INFINITE);
	//						SetText() += "Kill Them All!\n";
	//						ReleaseMutex(mutx);
	//						Sleep(300);
	//						break;
	//					}
	//				}
	//			}
	//			else
	//			{		
	//				WaitForSingleObject(mutx, INFINITE);
	//				SetText() = "������ �����մϴ�.\n\n\n";
	//				for(int i=0;i<TRI_MAX;i++)
	//				{
	//					char temp[64];
	//					sprintf_s(temp,"%c - %s",'a'+i,tribe_type_string[i]);
	//					int remain_num_ = 23-strlen(temp);
	//					SetText() += temp;
	//					if(i%2 ==0)
	//					{
	//						for(int j=0;j<remain_num_;j++)
	//							SetText() += " ";
	//					}
	//					if(i%2 == 1 || i == TRI_MAX-1)
	//					{
	//						SetText() += "\n";
	//					}
	//				}
	//				ReleaseMutex(mutx);
	//				while(1)
	//				{
	//					int select = waitkeyinput();
	//					if(select>='a' && select<'a'+TRI_MAX)
	//					{
	//						you.tribe = (tribe_type)(select - 'a');
	//						WaitForSingleObject(mutx, INFINITE);
	//						SetText() += "�׷� �������� ��������?\n";
	//						ReleaseMutex(mutx);
	//						Sleep(300);
	//						break;
	//					}
	//				}
	//				WaitForSingleObject(mutx, INFINITE);
	//				SetText() = "������ �����մϴ�.\n\n\n";
	//				for(int i=0;i<JOB_MAX;i++)
	//				{
	//					char temp[64];
	//					sprintf_s(temp,"%c - %s",'a'+i,job_type_string[i]);
	//					int remain_num_ = 23-strlen(temp);
	//					SetText() += temp;
	//					if(i%2 ==0)
	//					{
	//						for(int j=0;j<remain_num_;j++)
	//							SetText() += " ";
	//					}			
	//					if(i%2 == 1 || i == JOB_MAX-1)
	//					{
	//						SetText() += "\n";
	//					}
	//				}
	//				ReleaseMutex(mutx);
	//				while(1)
	//				{
	//					int select = waitkeyinput();
	//					if(select>='a' && select<'a'+JOB_MAX)
	//					{
	//						you.job = (job_type)(select - 'a');
	//						WaitForSingleObject(mutx, INFINITE);
	//						SetText() += "���� �����̴�.\n";
	//						ReleaseMutex(mutx);
	//						Sleep(300);
	//						break;
	//					}
	//				}



	//				you.image = &img_play_normal;
	//				you.char_name.name = "";
	//				//you.SetXY(DG_MAX_X/2, DG_MAX_Y/2);


	//			}
	//		}
	//		if(main_)
	//			continue;


	//if(isTutorial())
	//{
	//	//you.image = &img_play_sanae;
	//	//you.char_name.name = "�糪��";
	//	//you.tribe = TRI_HUMAN;
	//	//you.job = JOB_SHAMAN;
	//	//SetTribe(you.tribe);
	//	//you.CalcuHP();
	//	//env[current_level].EnterMap(0,deque<monster*>());	
	//	//printlog("ī���ڴ� ���ߴ� : ȯ���Ѵ�, �糪��! �̹� Ʃ�丮���� ���� �������.",true,false,false,CL_warning);
	//	//printlog("ī���ڴ� ���ߴ� : ������ ���� ��Ʈ��+P�� �α׸� Ȯ���ϰ� �ñ��Ѱ� ?�� ����.",true,false,false,CL_warning);
	//	//printlog("ī���ڴ� ���ߴ� : �ϴ� h j k l�� ����Ű�� ������ �� �־�. ��ҹ��ڿ� ������.",true,false,false,CL_warning);
	//	////you.resetLOS(false);
	//}
	if(isNormalGame() && !saveexit)
	{
		char temp[200];
		sprintf_s(temp,200,"%s, %s %s %s. ������ Ž���� �����ߴ�.", you.user_name.name.c_str(),tribe_type_string[you.tribe],job_type_string[you.job],you.GetCharNameString()->c_str());
		AddNote(you.turn,CurrentLevelString(),temp,CL_normal);

		SetTribe(you.tribe);
		TouhouPlayerble(you.char_name.name, true);
		SetJob(you.job,you.char_name.name);
		TouhouPlayerble(you.char_name.name, false);
		/*Test_char_init(item_, bonus);*/
		you.CalcuHP();
		Initialize();
	}
	changedisplay(DT_GAME);
	saveexit = true;
}


void Initialize()
{
	env[current_level].EnterMap(0,deque<monster*>());

	printlog("ȯ���⿡ �°� ȯ���Ѵ�!",true,false,false,CL_normal);
	//you.resetLOS(false);

}



void MainLoop()
{
	int a=0,b=0;
	while(1)
	{
		you.player_move = true;

		if(you.s_timestep)
		{
			turn_skip();
			Sleep(16);
			continue;
		}

		switch(waitkeyinput())
		{
		case 'j':
			Move(coord_def(you.position.x,you.position.y-1));  //��
			break;
		case 'k':
			Move(coord_def(you.position.x,you.position.y+1)); //�Ʒ�
			break;
		case 'h':
			Move(coord_def(you.position.x-1,you.position.y)); //����
			break;
		case 'l':
			Move(coord_def(you.position.x+1,you.position.y)); //������
			break;
		case 'b':
			Move(coord_def(you.position.x-1,you.position.y+1));
			break;
		case 'n':
			Move(coord_def(you.position.x+1,you.position.y+1));
			break;
		case 'y':
			Move(coord_def(you.position.x-1,you.position.y-1));
			break;
		case 'u':
			Move(coord_def(you.position.x+1,you.position.y-1));
			break;
		case 'x': //����Ž��
			Search();
			break;
		case 's': //�Ͻ�ŵ
		case '.': //�Ͻ�ŵ
			turn_skip();
			break;
		case 'g':
		case ',': //�ݱ�
			PickUp();
			break;
		case 'i': //������Ȯ��
			iteminfor();
			break;	
		case 'd': //�����۹�����
			iteminfor_discard();
			break;
		case 'D': //�������� ���� ������ ������
			fast_discard();
			break;
		case 'w': //��������
			Equip_Weapon();
			break;
		case 'W': //������
			Equip_Armor();
			break;
		case 'T': //������
			Unequip_Armor();
			break;
		case 'C': //���ݱ�
			Close_door();
			break;
		case 'O': //������
			Open_door();
			break;
		case 'o': //�ڵ��̵�
			auto_Move();
			break;
		case '5': //100�ϳѱ��
			long_rest();
			break;
		case 0x88: //��Ʈ��P - �α�
			view_log();
			break;
		case 'e': //�Ա�
			Eatting();
			break;
		case 'q': //���ñ�
			Drinking();
			break;
		case 'r': //�б�
			Reading();
			break;
		case 'm': //��ų����â
			skill_view();
			break;
		case 'P': //��ű�����
			Equip_Jewelry();
			break;
		case 'R': //��ű�����
			Unequip_Jewelry();
			break;
		case 'S': //üũ�� ����
			saveandcheckexit();
			break;
		case 0x89: //��������
			nosaveandexit();
			break;
		case 0x8A: //����� ����
			saveandexit();
			break;
		case 'X': //����Ž��
			Wide_Search();
			break;
		case 'f': //������(����)
			Quick_Throw(you.GetThrowIter(),you.GetTargetIter());
			break;
		case 'F': //������(����)
			Select_Throw();
			break;
		case '\\': //�ĺ��� Ȯ��
			Iden_Show();
			break;
		case '>':
			Stair_move(true);
			break;
		case '<':
			Stair_move(false);
			break;
		case '%':
			stat_view();
			break;
		case '}':
			Weapon_Show();
			break;
		case '[':
			Armour_Show();
			break;
		case '\"':
			Amulet_Show();
			break;
		case '@':
			Simple_State_Show();
			break;
		case 'N':
			//sendScore();
			break;
		case 'E':
			Experience_Show();
			break;
		//case 'c':
		//	Spelllcard_Declare();
		//	//Eat_Power();
		//	break;
		case 'v':
		case 'V':
			Spelllcard_Evoke();
			break;
		case 'p':
			Pray();
			break;
		case '#':
			if(isNormalGame() && Dump(0))
				printlog("������ �����߽��ϴ�.",true,false,false,CL_normal);
			break;
		case 'Z':
		case 'z':
			SpellUse();
			break;
		case 'I':
			SpellView();
			break;
		case 'a':
			SkillUse();
			break;
		case 'A':
			PropertyView();
			break;
		case 'M':
			run_spell();
			break;
		case 't':
			shout();
			break;
		case '^':
			God_show();
			break;
		case '&': //���ڵ���!
			//waitkeyinput();
			wiz_mode();
			break;
		case '_':
			save_mode();
			break;
		case 0x8B:
			auto_pick_onoff(false);
			break;
		case '?'://����
			Help_Show();
			break;
		case VK_ESCAPE://esc
			escape();
			break;
		case VK_TAB:
			auto_battle();
			break;
		}
	}
}