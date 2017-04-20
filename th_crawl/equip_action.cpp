//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: equip_action.cpp
//
// ����: player�� �ൿ��(���� ���� �ൿ��)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "key.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"

void Equip_Weapon()
{
	if(you.s_lunatic)
	{
		printlog("���⿡ �۽��� ���·� ���⸦ �ٲ� �� ����!",true,false,false,CL_danger);
		return;
	}

	view_item(IVT_EQ_WEAPON,"���� ���⸦ �����Ͻðڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equip(key_,ET_WEAPON);
			break;
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
			view_item(IVT_SELECT,"���� ���⸦ �����Ͻðڽ��ϱ�?");
		else if(key_ == '-')
		{
			if(!you.unequip(ET_WEAPON))
			{				
				printlog("���ֿ� �ɷ� �־ ��� ���� �� ����.",true,false,false,CL_normal);
			}
			break;
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);

}


void Equip_Armor()
{
	if(you.s_lunatic)
	{
		printlog("���⿡ �۽��� ���·� ���� �ٲ� �� ����!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_EQ_ARMOR,"���� ���� �����ϰڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equiparmor(key_);
			break;
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
			view_item(IVT_SELECT,"���� ���� �����ϰڽ��ϱ�?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Armor()
{	
	if(you.s_lunatic)
	{
		printlog("���⿡ �۽��� ���·� ���� ���� �� ����!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_UEQ_ARMOR,"���� ���� ���ڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			
			changedisplay(DT_GAME);
			you.unequiparmor(key_);
			break;
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
			view_item(IVT_SELECT,"���� ���� ���ڽ��ϱ�?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}



void Equip_Jewelry()
{	
	if(you.s_lunatic)
	{
		printlog("���⿡ �۽��� ���·� ������ �� �� ����!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_EQ_JEWELRY,"���� ��ű��� �����ϰڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equipjewerly(key_);
			break;
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
			view_item(IVT_SELECT,"���� ��ű��� �����ϰڽ��ϱ�?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Jewelry()
{	
	if(you.s_lunatic)
	{
		printlog("���⿡ �۽��� ���·� ������ ���� �� ����!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_UEQ_JEWELRY,"���� ��ű��� ���ڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.unequipjewerly(key_);
			break;
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
			view_item(IVT_SELECT,"���� ��ű��� ���ڽ��ϱ�?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}




