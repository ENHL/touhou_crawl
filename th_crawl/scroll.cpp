//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: scroll.cpp
//
// ����: �η縶��
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "scroll.h"
#include "key.h"
#include "smoke.h"
#include "monster_texture.h"
#include "throw.h"
#include <algorithm>
extern HANDLE mutx;

char *scroll_uniden_string[SCT_MAX]=
{
	"ASASVQE�� ���ִ� ",
	"EFIIEQN�� ���ִ� ",
	"QEWFQFF�� ���ִ� ",
	"DIQHQNA�� ���ִ� ",
	"IVNUXTO�� ���ִ� ",
	"MDIMIKU�� ���ִ� ",
	"AFIQHQW�� ���ִ� ",
	"POIUGAW�� ���ִ� ",
	"MVDOQUR�� ���ִ� ",
	"TFJEOTT�� ���ִ� ",
	"XNEPBIQ�� ���ִ� ",
	"JUYBLNM�� ���ִ� ",
	"UNQIFNV�� ���ִ� ",
	"LVIWBAA�� ���ִ� ",
	"RWMVXCO�� ���ִ� ",
	"OFQXLFE�� ���ִ� "
};

const char *scroll_iden_string[SCT_MAX]=
{	
	"�����̵��� ",
	"�ĺ��� ",
	"���� ",
	"���������� ",
	"�������� ",
	"���������� ",
	"�����̵��� ",
	"����Ž���� ",
	"���Ⱝȭ�� ",
	"���Ⱝȭ�� ",
	"����ȭ�� ",
	"�Ȱ��� ",
	"����Ž���� ",
	"��ű������� ",
	"������ ",
	"���� "
};



bool identity_scroll();
bool curse_weapon_scroll();
bool curse_armour_scroll();
bool remove_curse_scroll();
bool blink_scroll();
bool enchant_weapon_1_scroll();
bool enchant_weapon_2_scroll();
bool enchant_armour_scroll();
bool fog_scroll();
bool detect_curse_scroll();
bool curse_jewelry_scroll();
bool skill_silence(int pow, bool short_, unit* order, coord_def target);
bool skill_soul_shot(int power, unit* order, coord_def target);




scroll_type goodbadscroll(int good_bad)
{
	if(good_bad==2)
	{
		scroll_type list_[5] = {SCT_BLINK, SCT_ENCHANT_WEAPON_1/*SCT_ENCHANT_WEAPON_2*/, SCT_ENCHANT_ARMOUR, SCT_FOG, SCT_SOUL_SHOT};
		return list_[randA(4)];
	}
	else if(good_bad==3)
	{
		scroll_type list_[1] = {SCT_SILENCE};
		return list_[randA(0)];
	}
	else //if(good_bad==1)
	{
		scroll_type list_[3] = {SCT_TELEPORT, SCT_IDENTIFY, SCT_REMOVE_CURSE/*SCT_DETECT_CURSE*/};
		return list_[randA(2)];
	}/*
	else
	{
		scroll_type list_[4] = {SCT_NONE, SCT_CURSE_WEAPON, SCT_CURSE_ARMOUR, SCT_CURSE_JEWELRY};
		return list_[randA(3)];
	}*/


}
int isGoodScroll(scroll_type kind)
{	
	switch(kind)
	{
	case SCT_SOUL_SHOT:
		return 3;
	case SCT_TELEPORT:
	case SCT_IDENTIFY:
	case SCT_REMOVE_CURSE:
	case SCT_BLINK:
		return 2;
	case SCT_ENCHANT_WEAPON_1:
	case SCT_ENCHANT_WEAPON_2:
	case SCT_ENCHANT_ARMOUR:
	case SCT_FOG:
	case SCT_MAPPING:
	case SCT_DETECT_CURSE:
	case SCT_SILENCE:
		return 1;
	case SCT_NONE:
		return 0;
	case SCT_CURSE_WEAPON:		
	case SCT_CURSE_ARMOUR:
	case SCT_CURSE_JEWELRY:
		return -1;
	}
	return 1;
}




void readscroll(scroll_type kind)
{
	switch(kind)
	{
	case SCT_TELEPORT:		
		if(you.god == GT_YUKARI)
		{
			if(iden_list.scroll_list[kind].iden != 3)
			{				
				printlog("��ī���� ����� ������ ���̵��� ����� �ѹ��� ���ֱ�� �Ͽ���.",true,false,false,CL_small_danger);
			}
			else
			{
				printlog("��ī���� ����� ������ ���̵��� ��뿡 �г��ߴ�!",true,false,false,CL_small_danger);
				you.PietyUpDown(-5);
			}
		}
		you.SetTele(rand_int(3,6));
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_IDENTIFY:
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		if(identity_scroll())
		{
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  2;
		WaitForSingleObject(mutx, INFINITE);
		return;
	case SCT_NONE:
		printlog("�� �η縶���� ���ִ� ���� ��������.",false,false,false,CL_normal);
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_CURSE_WEAPON:		
		iden_list.scroll_list[kind].iden = 3;
		if(curse_weapon_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_CURSE_ARMOUR:		
		iden_list.scroll_list[kind].iden = 3;
		if(curse_armour_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_REMOVE_CURSE:
		iden_list.scroll_list[kind].iden = 3;
		if(remove_curse_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_BLINK:
		ReleaseMutex(mutx);
		blink_scroll();
		iden_list.scroll_list[kind].iden = 3;
		WaitForSingleObject(mutx, INFINITE);
		return;
	case SCT_MAPPING:
		//�׸������� �ߵ������ʴ´�.
		return;
	case SCT_ENCHANT_WEAPON_1:
		iden_list.scroll_list[kind].iden = 3;
		if(enchant_weapon_1_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_ENCHANT_WEAPON_2:
		iden_list.scroll_list[kind].iden = 3;
		if(enchant_weapon_2_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_ENCHANT_ARMOUR:
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		if(enchant_armour_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  2;
		WaitForSingleObject(mutx, INFINITE);
		return;
	case SCT_FOG:
		fog_scroll();
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_DETECT_CURSE:
		detect_curse_scroll();
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_CURSE_JEWELRY:
		iden_list.scroll_list[kind].iden = 3;
		if(curse_jewelry_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_SILENCE:
		skill_silence(75, false, &you, you.position);
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_SOUL_SHOT://�߰�
		iden_list.scroll_list[kind].iden = 3;
		if(you.power >= 100)
		{
			ReleaseMutex(mutx);
			changedisplay(DT_GAME);
			you.PowUpDown(-100,true);
			printlog("��! ",false,false,false,CL_white_blue);
			skill_soul_shot(0, &you, you.position);
			WaitForSingleObject(mutx, INFINITE);
			iden_list.scroll_list[kind].iden = 3;
		}
		else
		{
			printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
			if(iden_list.scroll_list[kind].iden != 3)
				iden_list.scroll_list[kind].iden =  1;
		}
		return;
	}
}



bool identity_scroll()
{
	if(iden_list.scroll_list[SCT_IDENTIFY].iden == 3)
		view_item(IVT_UNIDEN,"���� �������� �ĺ��ðڽ��ϱ�?");
	else
		view_item(IVT_SELECT,"���� �����ۿ� ����Ͻðڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				if(!item_->isiden())
				{
					item_->Identify();
					char temp[2];
					sprintf(temp,"%c",item_->id);
					printlog(temp,false,false,false,item_->item_color());
					printlog(" - ",false,false,false,item_->item_color());
					printlog(item_->GetName(),true,false,false,item_->item_color());
					return true;
				}
				else
				{
					printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
					return false;
				}

			}
		}
		else if(key_ == VK_DOWN)//-----�̵�Ű-------
		{
			changemove(32);  //��
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //�Ʒ�
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----�̵�Ű��-------
		else if(key_ == '*')
		{	
			if(iden_list.scroll_list[SCT_IDENTIFY].iden == 3)
				view_item(IVT_SELECT,"���� �������� �ĺ��ðڽ��ϱ�?");
			else
				view_item(IVT_SELECT,"���� �����ۿ� ����Ͻðڽ��ϱ�?");
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}


bool curse_weapon_scroll()
{
	if(you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName(); //���ֹޱ��� �̸�
		if(you.equipment[ET_WEAPON]->Curse(true,ET_WEAPON))
		{
			printlog("�����ϰ� �ִ� ",false,false,false,CL_small_danger);	
			printlog(before_name,false,false,false,CL_small_danger);	
			printlog(you.equipment[ET_WEAPON]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
			printlog("�˰� ������.",true,false,false,CL_small_danger);		
			return true;
		}
		else
		{
			printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
			return false;
		}
	}
	else
	{
		printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
		return false;
	}
}
bool curse_armour_scroll()
{	
	deque<int> dq;
	for(int i=ET_ARMOR;i<ET_ARMOR_END;i++)
		dq.push_back(i);
	random_shuffle(dq.begin(),dq.end());

	for(int i = 0; i<dq.size() ; i++)
	{
		if(you.equipment[dq[i]])
		{
			string before_name = you.equipment[dq[i]]->GetName(); //���ֹޱ��� �̸�
			if(you.equipment[dq[i]]->Curse(true,(equip_type)dq[i]))
			{
				printlog("�����ϰ� �ִ� ",false,false,false,CL_small_danger);		
				printlog(before_name,false,false,false,CL_small_danger);	
				printlog(you.equipment[dq[i]]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
				printlog("�˰� ������.",true,false,false,CL_small_danger);		
				return true;
			}
			else
			{
				printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
				return false;
			}
		}
	}
	printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
	return false;
}

bool remove_curse_scroll()
{
	bool iden_ = false;
	for(int i = ET_FIRST; i<ET_LAST ; i++)
	{
		if(you.equipment[i])
		{
			if(you.equipment[i]->isRightType((equip_type)i))
			{	
				if(you.equipment[i]->curse)
				{
					you.equipment[i]->curse = false;
					you.equipment[i]->identify_curse = true;
					iden_ = true;
				}

			}
		}
	}
	if(iden_)
	{
		printlog("�������ִ� ����� ���ְ� Ǯ�ȴ�.",true,false,false,CL_normal);
		return true;
	}
	else
	{
		printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
		return false;
	}
}


bool blink_scroll()
{
	changedisplay(DT_GAME);
	you.search_pos = you.position;
	you.search = true;
	bool is_move = false;
	Search_Move(coord_def(you.position.x,you.position.y), false,VT_BLINK);
	while(1)
	{
		switch(waitkeyinput())
		{
		case 'j':
			is_move = Search_Move(coord_def(you.position.x,you.position.y-1), false,VT_BLINK);  //��
			break;
		case 'k':
			is_move = Search_Move(coord_def(you.position.x,you.position.y+1), false,VT_BLINK); //�Ʒ�
			break;
		case 'h':
			is_move = Search_Move(coord_def(you.position.x-1,you.position.y), false,VT_BLINK); //����
			break;
		case 'l':
			is_move = Search_Move(coord_def(you.position.x+1,you.position.y), false,VT_BLINK); //������
			break;
		case 'b':
			is_move = Search_Move(coord_def(you.position.x-1,you.position.y+1), false,VT_BLINK);
			break;
		case 'n':
			is_move = Search_Move(coord_def(you.position.x+1,you.position.y+1), false,VT_BLINK);
			break;
		case 'y':
			is_move = Search_Move(coord_def(you.position.x-1,you.position.y-1), false,VT_BLINK);
			break;
		case 'u':
			is_move = Search_Move(coord_def(you.position.x+1,you.position.y-1), false,VT_BLINK);
			break;
		case VK_RETURN:
			if(is_move)
			{
				if(you.control_blink(you.search_pos))
				{
					
					if(you.god == GT_YUKARI)
					{
						printlog("��ī���� ����� ������ ���̵��� ��뿡 �г��ߴ�!",true,false,false,CL_small_danger);
						you.PietyUpDown(-5);
					}


					you.search = false;
					deletelog();
					return true;
				}
			}
			break;
		case VK_ESCAPE:
			printlog("������ �����̵��� ����Ͻðڽ��ϱ�? (y/n)",true,true,false,CL_help);
			bool repeat_ = true;
			while(repeat_)
			{
				switch(waitkeyinput())
				{
				case 'Y':
				case 'y':
					deletelog();
					you.search = false;
					return false;
				case 'N':
				case 'n':
					repeat_ = false;
				}
			}
		}
	}
}


bool enchant_weapon_1_scroll()
{
	if(you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName();
		if(you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, 1, 0))
		{
			printlog("�����ϰ� �ִ� ",false,false,false,CL_good);	
			printlog(before_name,false,false,false,CL_good);	
			printlog(you.equipment[ET_WEAPON]->GetNameInfor().name_do(true),false,false,false,CL_good);
			printlog("���������� ������.",true,false,false,CL_good);
			you.equipment[ET_WEAPON]->curse = false;
			you.equipment[ET_WEAPON]->identify_curse = true;
			return true;
		}
		else
		{
			printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
			return false;
		}
	}
	else
	{
		printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
		return false;
	}
}

bool enchant_weapon_2_scroll()
{
	if(you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName();
		if(you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, 0, 1))
		{
			printlog("�����ϰ� �ִ� ",false,false,false,CL_good);	
			printlog(before_name,false,false,false,CL_good);	
			printlog(you.equipment[ET_WEAPON]->GetNameInfor().name_do(true),false,false,false,CL_good);
			printlog("���������� ������.",true,false,false,CL_good);
			you.equipment[ET_WEAPON]->curse = false;
			you.equipment[ET_WEAPON]->identify_curse = true;
			return true;
		}
		else
		{
			printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
			return false;
		}
	}
	else
	{
		printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
		return false;
	}
}



bool enchant_armour_scroll()
{
	if(iden_list.scroll_list[SCT_ENCHANT_ARMOUR].iden == 3)
		view_item(IVT_ARMOR_ENCHANT,"���� ���� ��ȭ�Ͻðڽ��ϱ�?");
	else
		view_item(IVT_SELECT,"���� �����ۿ� ����Ͻðڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				string before_name = item_->GetName();
				if(item_->Enchant(ET_ARMOR, 1, 0))
				{
					printlog(before_name,false,false,false,CL_good);	
					printlog(item_->GetNameInfor().name_do(true),false,false,false,CL_good);
					printlog("�ʷϻ����� ������.",true,false,false,CL_good);
					item_->curse = false;
					item_->identify_curse = true;
					return true;
				}
				else
				{
					printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
					return false;
				}

			}
		}
		else if(key_ == VK_DOWN)//-----�̵�Ű-------
		{
			changemove(32);  //��
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //�Ʒ�
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----�̵�Ű��-------
		else if(key_ == '*')
		{	
			if(iden_list.scroll_list[SCT_ENCHANT_ARMOUR].iden == 3)
				view_item(IVT_SELECT,"���� ���� ��ȭ�Ͻðڽ��ϱ�?");
			else
				view_item(IVT_SELECT,"���� �����ۿ� ����Ͻðڽ��ϱ�?");
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}


bool fog_scroll()
{
	MakeCloud(you.position, img_fog_normal, SMT_FOG, rand_int(10,15), rand_int(8,12), 0,5, &you);
	return true;
}

bool detect_curse_scroll()
{
	for(list<item>::iterator it = you.item_list.begin(); it != you.item_list.end() ; it++)
	{
		it->identify_curse = true;
	}
	printlog("�κ��丮�� ���ָ� Ž���ߴ�.",true,true,false,CL_normal);
	return true;
}
bool curse_jewelry_scroll()
{
	deque<int> dq;
	for(int i=ET_JEWELRY;i<ET_JEWELRY_END;i++)
		dq.push_back(i);
	random_shuffle(dq.begin(),dq.end());

	for(int i = 0; i<dq.size() ; i++)
	{
		if(you.equipment[dq[i]])
		{
			string before_name = you.equipment[dq[i]]->GetName(); //���ֹޱ��� �̸�
			if(you.equipment[dq[i]]->Curse(true,(equip_type)dq[i]))
			{
				printlog("�����ϰ� �ִ� ",false,false,false,CL_small_danger);		
				printlog(before_name,false,false,false,CL_small_danger);	
				printlog(you.equipment[dq[i]]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
				printlog("�˰� ������.",true,false,false,CL_small_danger);		
				return true;
			}
			else
			{
				printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
				return false;
			}
		}
	}
	printlog("�ƹ� �ϵ� �Ͼ���ʾҴ�.",true,false,false,CL_normal);
	return false;
}