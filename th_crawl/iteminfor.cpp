//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: iteminfor.cpp
//
// ����: �������� ��������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "key.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"
#include "skill_use.h"
#include "weapon.h"
#include "armour.h"
#include "evoke.h"

extern HANDLE mutx;



string GetItemInfor(item *it);

void iteminfor(bool gameover)
{
	view_item(IVT_INFOR,gameover?"����� ������":"���� �������� Ȯ���ϰڽ��ϱ�?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				while(1)
				{
					WaitForSingleObject(mutx, INFINITE);
					SetText() = GetItemInfor(item_);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
					if(item_->type == ITM_BOOK)
					{
						int key_ = waitkeyinput(true);
						if( (key_ >= 'a' && key_ <= 'f'))
						{
							if(int spell_ = item_->GetValue(key_ - 'a'+1))
							{	
								WaitForSingleObject(mutx, INFINITE);
								SetText() = GetSpellInfor((spell_list)spell_);
								ReleaseMutex(mutx);
								waitkeyinput();
								continue;
							}	
						}
					}
					else
						waitkeyinput();
					break;
				}
				view_item(IVT_INFOR,gameover?"����� ������":"���� �������� Ȯ���ϰڽ��ϱ�?");
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
		else if(key_ == VK_ESCAPE || (key_ == VK_RETURN && gameover))
			break;
	}
	changedisplay(DT_GAME);
}

string GetItemInfor(item *it)
{
	string text_ = it->GetName();
	text_ += "\n\n";
	switch(it->type)
	{
		//case ITM_WEAPON_DAGGER:
		//	text_ += "�ܰ��� �������� ���� Į�̴�. ���� ����ϴµ� Ư�� ������ �����̴�.\n\
		//			  ������ ź������ ���� �͵� �����ϴ�.\n";
	case ITM_WEAPON_SHORTBLADE:
	case ITM_WEAPON_LONGBLADE:
	case ITM_WEAPON_MACE:
	case ITM_WEAPON_SPEAR:
	case ITM_WEAPON_AXE:
	//case ITM_WEAPON_BOW:
		{
			skill_type ski_ = SKT_MACE;
			switch(it->type)
			{
			case ITM_WEAPON_SHORTBLADE:
				text_ += "���� ª�� ���̴�. ���� �ӵ��� ������ �� �ִ�.\n";
				ski_ = SKT_SHORTBLADE;
				break;
			case ITM_WEAPON_LONGBLADE:
				text_ += "���� �� ����̴�. ��ų� ���鼭 ��븦 �����Ѵ�.\n";
				ski_ = SKT_LONGBLADE;
				break;
			case ITM_WEAPON_MACE:
				text_ += "������ �б��.\n";
				ski_ = SKT_MACE;
				break;
			case ITM_WEAPON_SPEAR:
				text_ += "��ٶ� â�̴�. ���� �񷯼� ������ �� �ִ�.\n";
				ski_ = SKT_SPEAR;
				break;
			case ITM_WEAPON_AXE:
				text_ += "���� ���� �� �ִ� ����. �Ŵ��� ���� �����.\n";
				ski_ = SKT_AXE;
				break;
			//case ITM_WEAPON_BOW:
			//	text_ += "ȭ���� �ɰ� �ָ� �ִ� ������ ���� �� �ִ� Ȱ�̴�. ȭ���� ������ �ǹ̰� ����.\n";
			//	break;
			}


			
			if(it->value5 && it->value6)
			{
				text_ += "\n\n";
				text_ += GetBrandInfor((weapon_brand)it->value5);
				text_ += "\n";
			}

			char temp[100];
			sprintf(temp,"\n���ݷ� : %d       ���߷� : %d",it->value2,it->value1);
			text_ += temp;
			sprintf(temp,"\n������ݼӵ� : %g%%    ( �⺻���ݼӵ� : %d0%%       �ּҰ��ݼӵ� : %d0%% )",max((it->value8) , (it->value7-you.skill[ski_].level/2.0f))*10,it->value7,it->value8);
			text_ += temp;
			if(it->throw_item)
			{
				sprintf(temp,"\n�� �������� ���� �� �ִ�.");
				text_ += temp;
			}
			sprintf(temp,"\n\n�� �������� +9���� ��æƮ�� �����ϴ�.");
			text_ += temp;
			break;
		}
	case ITM_THROW_TANMAC:
		{
			switch(it->value4)
			{
			default://���� �̰� �߸� ����
				text_ += "ź�� ������ �⺻�� �Ǵ� ź���̴�. ������ ������ �����.\n";
				text_ += "������ �̰� ���� ź���̶�� ���̴�.\n";
				break;
			case TMT_BILL:
				text_ += "ź�� ������ �⺻�� �Ǵ� ź���̴�. ������ ������ �����.\n";
				text_ += "�� ������ ������ ������ ���Ÿ����� ���� ������ �� �ִ�.\n";
				break;
			case TMT_AMULET:
				text_ += "���̹��� ���� �� ġ���� �ƹķ����� ������ ȣ�ּ����� �پ��ִ�.\n";
				text_ += "���� �������� ���� �� �ִ� ���� �ڶ��̴�.\n";
				break;			
			case TMT_POISON_NEEDLE:
				text_ += "�̰��� �����鼭 ��뿡�� ������ ħ�̴�.\n";
				text_ += "�������� ������ �� ħ���� Ư���� ���� �߶����ִ°� ����.\n";
				break;
			case TMT_KIKU_COMPRESSER:
				text_ += "ı�ĵ��� �߸�ǰ�� �ϳ���. ���� ���� �����ϰ��ִ� ��ź�̴�.\n";
				text_ += "��뿡�� ������ ����Ǿ��ִ� ���� �ѹ��� ������.\n";
				text_ += "���� ���� ������ �� ���� �� ����.\n";
				break;
			}
			char temp[100];
			sprintf(temp,"\n���ݷ� : %d       ���߷� : %d",it->value2,it->value1);
			text_ += temp;
		}
		break;
	case ITM_ARMOR_BODY_ARMOUR_0:
	case ITM_ARMOR_BODY_ARMOUR_1:
	case ITM_ARMOR_BODY_ARMOUR_2:
	case ITM_ARMOR_BODY_ARMOUR_3:
		{
			switch(it->value5)
			{
			case AMK_NORMAL:
				text_ += "���ÿ� �Դ� ���� ��.\n";
				text_ += "õ�� �ƴ� ������ ���� �⺻�г�Ƽ�� ����� ��������. \n";
				text_ += "�׷��� �ּ��г�Ƽ�� �ٸ� �ʰ� �����ϹǷ� ���ʿ� �ͼ������� ������ ��������.\n\n";				 
				break;
			case AMK_MIKO:
				text_ += "������� �Դ� ��.\n";
				text_ += "���� ��ȣ�� �޾Ƽ� ������ ��ȣ���ش�. �԰��ִ� ���� ȥ�������� �����.\n\n";
				break;
			case AMK_WING:
				text_ += "����� ���ڵ��� �Դ´ٴ� ������.\n";
				text_ += "���⸦ ��������� Ư¡�� ������ �ִ�. �԰��ִ� ���� ���������� �����.\n\n";
				break;
			case AMK_KAPPA:
				text_ += "ı�ĵ��� ������ó�� �԰� �ִ� �Ķ��� ���̴�.\n";
				text_ += "���� �������� �ߵ� �� �ְ� ������ �Ǿ��ִ�. �԰��ִ� ���� �ñ������� �����.\n\n";
				break;
			case AMK_FIRE:
				text_ += "������ ����� �����ִ� ���̴�.\n";
				text_ += "�߰ſ� ������ �ߵ� �� ���� �� ����. �԰��ִ� ���� ȭ�������� �����.\n\n";
				break;
			case AMK_MAID:
				text_ += "ȫ������ ���̵���� �Դ� ��.\n";
				text_ += "ȫ���� ������ǥ Ư���� ������ ó���� �Ǿ��ִ�. �԰��ִ� ���� ���������� �ö󰣴�.\n\n";
				break;
			case AMK_POISON:
				text_ += "����� �ɹ��� ������ �԰� �ִ� �������� �� ����� Ŀ�� ���� �� ���� �� ����.\n";
				text_ += "����� ���� ����� ����� ��ȣ���ش�. �԰��ִ� ���� �������� �����.\n\n";
				break;
			case AMK_AUTUMN:
				text_ += "��ǳ���� ������� ��. �ǿܷ� ����ε� ���̴�.\n";
				text_ += "�����ϸ� �ϰ������� �ֺ��� ǳ�濡 ��ȭ�Ǿ ������ �ް��ϰ� �ö󰣴�.\n\n";
				break;
			}
			switch(it->type)
			{
			case ITM_ARMOR_BODY_ARMOUR_0:
				text_ += "�����̱� ���ϰ� õ���� �Ǿ��ִ� ��.\n";
				text_ += "���� �׷������ �������� ���� �ʰ����� �Ǿ��ִ�!\n";
				break;
			case ITM_ARMOR_BODY_ARMOUR_1:
				text_ += "���� ������ �Ǿ��ִ� ��.\n";
				text_ += "õ���� �����̱� ���������� �� ������.\n";
				break;
			case ITM_ARMOR_BODY_ARMOUR_2:
				text_ += "�罽�� �����ִ� ����.\n";
				text_ += "�� �ܴ������� �Ǳ����ε� ���ʺ��ٴ� ���ϴ�.\n";
				break;
			case ITM_ARMOR_BODY_ARMOUR_3:
				text_ += "��ö�� �� �Ǳ��� ���� ����.\n";
				text_ += "������ �������� ���������� ����� ������ å������.\n";
				break;
			}
			char temp[100];
			sprintf(temp,"\n\n���� : %d   �⺻�г�Ƽ : %d   �ּ��г�Ƽ : %d\n\n",it->value1,it->value2,it->value3);
			text_ += temp;
			sprintf(temp,"\n\n�г�Ƽ�� ���ʽ�ų�� �ø����� �پ��ϴ�. �ּ��г�Ƽ���Ϸδ� ���ϼ� �����ϴ�.\n\n");
			text_ += temp;
			sprintf(temp,"�հ� �г�Ƽ��ŭ ȸ�ǿ� ����, ������������ �����մϴ�.\n");
			text_ += temp;
			sprintf(temp,"�հ� �г�Ƽ�� %d���� ������ �г�Ƽ��ŭ �߰������� �������� �����մϴ�.\n", you.GetPenaltyMinus(1));
			text_ += temp;
			sprintf(temp,"�հ� �г�Ƽ�� %d���� ������ �г�Ƽ��ŭ �̵��ӵ��� �����մϴ�.\n", you.GetPenaltyMinus(2));
			text_ += temp;
			sprintf(temp,"�հ� �г�Ƽ�� %d���� ������ ��� �ൿ�� 2�� �����̵˴ϴ�.\n\n", you.GetPenaltyMinus(3));
			text_ += temp;
			sprintf(temp,"\n�� �������� +%d���� ��æƮ�� �����ϴ�.", it->value1);
			text_ += temp;
			break;
		}
	case ITM_ARMOR_SHIELD:
		{
		text_ += "����� ������ ���� ���� ����. ��չ��⸦ ��� ������ ������ �Ұ����ϴ�.\n";
		text_ += "����� ź���� ���� ��Ģ���� Ȱ�뵵 �����ϴ�.\n";
		char temp[100];
		sprintf(temp,"���� : %d   �⺻�г�Ƽ : %d   �ּ��г�Ƽ : %d\n\n",it->value1,it->value2,it->value3);
		text_ += temp;
		sprintf(temp,"�г�Ƽ�� ���н�ų�� �ø����� �پ��ϴ�. �ּ��г�Ƽ���Ϸδ� ���ϼ� �����ϴ�.\n\n");
		text_ += temp;
		sprintf(temp,"�հ� �г�Ƽ��ŭ ȸ�ǿ� ����, ����������, ������ �����մϴ�.\n", you.s_str/4);
		text_ += temp;
		sprintf(temp,"�հ� �г�Ƽ�� %d���� ������ �г�Ƽ��ŭ �߰������� �������� �����մϴ�.\n", you.GetPenaltyMinus(1));
		text_ += temp;
		sprintf(temp,"�հ� �г�Ƽ�� %d���� ������ �г�Ƽ��ŭ �̵��ӵ��� �����մϴ�.\n", you.GetPenaltyMinus(2));
		text_ += temp;
		sprintf(temp,"�հ� �г�Ƽ�� %d���� ������ ��� �ൿ�� 2�� �����̵˴ϴ�.\n\n", you.GetPenaltyMinus(3));
		text_ += temp;
		sprintf(temp,"�� �������� +%d���� ��æƮ�� �����ϴ�.",it->value1<=4?3:(it->value1<=8?6:9));
		text_ += temp;
		break;
		}
	case ITM_POTION:
		{
			if(iden_list.potion_list[it->value1].iden)
			{
				switch(it->value1)
				{
				case PT_WATER:
					text_ += "�ܼ��� ���� �����̴�.\n";
					break;
				case PT_HEAL:
					text_ += "ġ�� �����̴�. ���ø� ���� �������� �����̻󿡼� ȸ���ǰ� ü�µ� ȸ���ȴ�.\n";
					text_ += "ȿ���� ���� ��� ���ֵǴ� �ź��� ����\n";
					break;
				case PT_POISON:
					text_ += "���� ����ִ� �����̴�. ���ܿ� ���� ���� ���ø� ������ ���� �ɸ���.\n";
					break;
				case PT_HEAL_WOUND:
					text_ += "��ó�� ġ���ϴ� �����̴�. ������ ���������� ���� ü���� ġ���Ѵ�.\n";
					text_ += "�ٸ� �����̻��� ġ�������� ���Ѵ�.\n";
					break;
				case PT_MIGHT:
					text_ += "���������� ���� �ٷ��� �����ϰ� �Ǵ� ����. ���ݷµ� ��������.\n";
					break;
				case PT_HASTE:
					text_ += "���� �ӵ��� �����̰� �����ִ� ����. �̵�, �ൿ ��� 2����� �ȴ�.\n";
					break;
				case PT_CONFUSE:
					text_ += "���ø� ���ſ� ȥ���� �������ִ� ����.\n";
					text_ += "ȥ���� ������������� ���ڸ��� ���� ������ ��ٸ��� �͵� ����̴�.\n";
					break;
				case PT_SLOW:
					text_ += "�������� �������� ����. ��� �̵�, �ൿ�� 1/2����� �ȴ�.\n";
					break;
				case PT_PARALYSIS:
					text_ += "���ø� ���ϰ� ���� ����Ǵ� ����. �����ϴ�.\n";
					break;
				case PT_CLEVER:
					text_ += "���ø� �Ͻ������� ������ �������� ����.\n";
					text_ += "���ɰ� �Բ� ����������, �����Ŀ��� ���� �ö󰣴�.\n";
					break;
				case PT_AGILITY:
					text_ += "���ø� �Ͻ������� ��ø�� �������� ����.\n";
					text_ += "��ø�� �Բ� ȸ�ǵ� �ö󰣴�.\n";
					break;
				case PT_MAGIC:
					text_ += "���ø� ������ ���İ��� ä���ִ� ������ ����.\n";
					break;
				case PT_LEVETATION:
					text_ += "���ø� �Ͻ������� ������°� �Ǵ� ����. ������¿����� ������������ �ǳ� �� �ְԵȴ�.\n";
					break;
				case PT_POWER:
					text_ += "���ø� �Ŀ��� ����ϴ� �Ŀ��� ����.\n";
					text_ += "���� ��� P�� 1.00�����ϰ� �ȴ�.\n";
					break;
				case PT_DOWN_STAT:
					text_ += "���ø� �Ͻ������� �ɷ�ġ�� �����ϰ� �Ǵ� ���ܿ� ����.\n";
					text_ += "�� ���� ��ø�� ������ �ɷ�ġ�� �Ͻ������� ���ҵȴ�. �ð��� ������ �ǵ��� �´�.\n";
					break;
				case PT_RECOVER_STAT:
					text_ += "���ø� �Ͻ������� �Ҿ���� �ɷ�ġ�� �ٷ� ȸ�������ִ� ����.\n";
					break;
				case PT_ALCOHOL:
					text_ += "�̰��� ���̴�. ���ø� ���Ѵ�.\n";
					text_ += "���� ���� ���¸� �ȹٷ� �����̱� ����� ����.\n";
					break;

				default:
					text_ += "�̰� ���� �����̴�. �����ϱ�!\n";
					break;					
				}
			}
			else
			{
				text_ += "���� �ǽɽ����� ��ü�� ����ִ� ��. ���ź��� �ʰ� �� �� ���� �� ����.\n";
			}
		}
		break;
	case ITM_FOOD:
		text_ += "���� �� �ִ� �����̴�. ������ �̷� ���ĵ��� �������ִ� �͵� ���������� ���� �� �־� ���δ�.\n";
		break;
	case ITM_SCROLL:
		{
			if(iden_list.scroll_list[it->value1].iden == 3)
			{
				switch(it->value1)
				{
				case SCT_TELEPORT:
					text_ += "������ �̻��� �����̵��� ����Ű�� �η縶��. ��, ���ڸ��� �����̵��� ���� �ʴ´�.\n";
					text_ += "������ �غ�Ⱓ�� �ʿ��ϴ�. �����̵��� �ɸ� ���¿��� ������ �� ���� ��ȭ���� ������ �� �� �ִ�.\n";
					break;
				case SCT_IDENTIFY:
					text_ += "�ĺ��� �η縶��. �а��� �տ� �� ������ �ĺ��� �� �ְ� �ȴ�. �ſ� �߿��� �η縶��\n";
					text_ += "�� �ݿ� ���������� �ɷ°� �ſ� ����ϴ�.\n";
					break;
				case SCT_NONE:
					text_ += "�峭�ٷ��� �������� �ǹ̾��� ����� ������!\n";
					break;	
				case SCT_CURSE_WEAPON:
					text_ += "����ִ� ���⿡ ���ָ� �Ǵ�. ���ֿ� �ɸ� ���� ���ְ� Ǯ���������� ������ �� ���� �ȴ�.\n";
					break;
				case SCT_CURSE_ARMOUR:
					text_ += "����ִ� ���� ���ָ� �Ǵ�. ���ֿ� �ɸ� ���� ���ְ� Ǯ���������� ������ �� ���� �ȴ�.\n";
					break;
				case SCT_REMOVE_CURSE:
					text_ += "����ִ� ����� ���ָ� �����Ѵ�. ��� ���ݵ� �������.\n";
					break;
				case SCT_BLINK:
					text_ += "�þ߳��� ������ ��ġ�� �����̵��� �ϰ� �����ִ� �η縶��.\n";
					text_ += "����Ż������� �ְ��� �η縶����.\n";
					break;
				case SCT_MAPPING:
					text_ += "���� �ִ� ���� ���� �����ִ� �η縶��.\n";
					break;
				case SCT_ENCHANT_WEAPON_1:
				case SCT_ENCHANT_WEAPON_2:
					text_ += "���� �����Ǿ��ִ� ������ ���ݷ°� ���߷��� ��ȭ��ų �� �ִ�. ���� ���ֵ� �����ش�.\n";
					break;
				case SCT_ENCHANT_ARMOUR:
					text_ += "������ ���� ������ ��ȭ��ų �� �ִ�. ���� ���ֵ� �����ش�.\n";
					break;
				case SCT_FOG:
					text_ += "���⸦ ����� ���� �η縶��.\n";
					text_ += "����� ���� �ڽ��� �þ߸� �����ش�.\n";
					break;
				case SCT_DETECT_CURSE:
					text_ += "����ǰ�߿� ���ְ� �ɸ� �������� Ž���ϴ� �η縶��.\n";
					text_ += "Ž���� �������� ��� �ĺ��� �ȴ�.\n";
					break;
				case SCT_CURSE_JEWELRY:
					text_ += "�����ϰ� �ִ� ��ű��� ���ָ� �Ŵ� �η縶��.\n";
					text_ += "������ ������� ������ �Ѱ��� ��ű��� ���ְ� �ɸ���.\n";
					break;
				case SCT_SILENCE:
					text_ += "�ֺ��� ������ ���̴� �η縶��. �Ͻ������� �������°� �ȴ�.\n";
					text_ += "���������ȿ� �ִ� ���� ������ ����������ϸ� ������ �ð��� ������ ���� �پ���.\n";
					text_ += "��, �ڽŵ� �Ҹ��� �����ϴ� ������ �η縶��, �Ǵ��� ������� ���ϰ� �ȴ�.\n";
					break;
				case SCT_SOUL_SHOT:
					text_ += "������ ����ϴ� �η縶��, �ֺ��� ������ ������ �� ���� ª�� ���� �Ǵ�.\n";
					text_ += "ȿ���� ������������ P�� ��ĭ ������ �Ҹ��ϰԵȴ�.\n";
					break;
				default:
					text_ += "������ �η縶��. �� �����ڿ��� ���׷� �Ű��ع�����!\n";
					break;
				}
			}
			else
			{
				text_ += "�� �� ���� ���ڵ��� �����Ǿ��ִ� �η縶��.\n";
			}
			text_ += "�Ҹ���� ������ �η縶���� ����� ������ ���� ��� �� �ִ�.\n";
		}
		break;
	case ITM_SPELL:
		{
			if(iden_list.spellcard_list[it->value2].iden == 2)
			{
				switch(it->value2)
				{
				case SPC_V_FIRE:
					text_ += "ȭ���� ����� ���� ����ī���.\n";
					text_ += "��뿡�� ������ ȭ�������� ���Ѵ�.\n";
					break;
				case SPC_V_ICE:
					text_ += "�ñ��� ����� ���� ����ī���.\n";
					text_ += "��뿡�� ������ �ñ������ ���Ѵ�.\n";
					break;
				case SPC_V_EARTH:
					text_ += "������ ����� ���� ����ī���.\n";
					text_ += "��ü ������ ������ ���� �ε����� ���� ���߽��� ���� ���� �������� ������.\n";
					break;
				case SPC_V_AIR:
					text_ += "����� ����� ���� ����ī���.\n";
					text_ += "��ä���� ���� ������ ź���� ���� �������� ������ ����������.\n";
					break;
				case SPC_V_INVISIBLE:
					text_ += "����� ����� �����ϰ� ����� ����ī���.\n";
					break;
				default:
					text_ += "������ ����ī���.\n";
					break;
				}				
				text_ += "\n";
			}
			text_ += "����ī��� ������ Ƚ�������� ������� ����� �� ������ �ʰ��ϸ� ���̻� ����� �� ���Եȴ�.\n";
			text_ += "��Ȯ�� ���� ������ �ĺ��� �ؾ� Ȯ���� �� �ִ�. ����ī��� �ߵ����� ����ؼ� ������ �ö󰣴�.\n";
		}
		break;
	case ITM_SPELLCARD:
		{
			text_ += "������ ���� ����ִ� ����ī��.\n";
			text_ += "õ�������� ����ī�尡 ������ ���� ������ �ɷ��� ���� ������ �ִ�.\n";
			text_ += "����� ����ī��� 'c'�� ������ �����ϸ� �����߿��� 'v'�� �����ɷ��� ����� �� �ִ�.\n";
			text_ += "�� ����ī��� ���� P�� �ʿ�� �Ͽ� �����Ҷ�, �����Ҷ�, �����ɷ��� ����Ҷ� P�� �Ҹ� �ؽ��ϴ�.\n";
			//if(iden_list.amulet_list[it->value1].iden == 2)
			//{
			//	switch(it->value1)
			//	{
			//	//case AMT_AC:
			//	//	text_ += "�� �� �������� �� ��ȭ��Ű�ų� ��ȭ��Ű�� ����� �����.\n";
			//	//	text_ += "�� �������� ������� ��ġ�� �޷��ִ�.\n";
			//	//	break;
			//	//case AMT_EV:
			//	//	text_ += "�� �� �����ڿ��� ȸ�Ǹ� ���ϰ� ����ų� ���ϰ� ����� ȸ���� �����.\n";
			//	//	text_ += "�� �������� ������� ��ġ�� �޷��ִ�.\n";
			//	//	break;
			//	//case AMT_CONFUSE_RESIS:
			//	//	text_ += "ȥ���� ���� ������ �ִ� ������̴�.\n";
			//	//	break;
			//	//case AMT_INACCURACY:
			//	//	text_ += "�� ����̸� �����ϰ� ������ ���߷��� �����Ѵ�.\n";
			//	//	break;
			//	//case AMT_POWER_KEEP:
			//	//	text_ += "�� ����̴� ����� P�Ҹ� ���ҽ����ش�.\n";
			//	//	text_ += "P�� 3�����϶� ���ҷ��� ���ҽ�Ű�� �����̳� ������¿����� P�Ҹ� ���ӵ� �ٿ��ش�.\n";
			//	//	break;
			//	default:
			//		text_ += "�� ���� ����̴� �ڵ� ���� ȿ���� ����.\n";
			//		break;
			//	}
			//}
			//else
			//{
			//	text_ += "������ ���� ����ִ� �����.\n";
			//	text_ += "����� �ٷ� �� ���� �� �� �ִ� ����̵� �ִ� �ݸ�. ��ġä�� ���� ����̵� �ִ�.\n";
			//}
		}
		break;
	case ITM_RING:
		{
			if(iden_list.ring_list[it->value1].iden == 2)
			{
				switch(it->value1)
				{
				case RGT_STR:
					text_ += "�տ� �� �������� �ٷ��� ��ȭ��Ű�ų� ��ȭ��Ű�� ���� ����.\n";
					text_ += "�� �������� ������ ��ġ�� �޷��ִ�.\n";
					break;
				case RGT_DEX:
					text_ += "�տ� �� �������� ��ø���� ��ȭ��Ű�ų� ��ȭ��Ű�� ��ø�� ����.\n";
					text_ += "�� �������� ������ ��ġ�� �޷��ִ�.\n";
					break;				
				case RGT_INT:
					text_ += "�տ� �� �������� ������ ��ȭ��Ű�ų� ��ȭ��Ű�� ������ ����.\n";
					text_ += "�� �������� ������ ��ġ�� �޷��ִ�.\n";
					break;			
				case RGT_HUNGRY:
					text_ += "������ ���� �ڿ����� P�� �Ҹ� ������ �Ǵ� ������� ����.\n";
					break;		
				case RGT_FULL:
					text_ += "�̳븮�ڴ��� �ູ�� ����ִ� ������ ������ �ڰ� �������� ������ �ȴ�.\n";
					text_ += "������簡 �������� �����ڴ� �ڿ����� P�� �Ҹ� �������� �ȴ�.\n";
					text_ += "�����̳� ������¿����� P�Ҹ� ���ӵ� �ٿ��ش�.\n";
					break;
				case RGT_TELEPORT:
					text_ += "�����ڿ��� �����̵��� �ɷ��� �ο��ϴ� ����.\n";
					text_ += "�� ���ۿ����� ���� �ִ� ���� �������� �����̵��� ������ �߻��ϰԵȴ�.\n";
					break;		
				case RGT_POISON_RESIS:
					text_ += "���� ���� ������ ��� ����. ���� ��� ���� ������ �����.\n";
					break;		
				case RGT_FIRE_RESIS:
					text_ += "ȭ���� ���� ������ ��� ����. �� 3�ܰ���� ��ø������ ���� �� �ִ�.\n";
					break;
				case RGT_ICE_RESIS:
					text_ += "�ñ⿡ ���� ������ ��� ����. �� 3�ܰ���� ��ø������ ���� �� �ִ�.\n";
					break;
				case RGT_SEE_INVISIBLE:
					text_ += "�����ϰ� ������ ������ ���� �� �� �ְ� �ȴ�.\n";
					break;
				case RGT_GRAZE:
					text_ += "�׷���� ����� �� �ִ� ����. �����ϸ� �ɷ»�뿡�� �׷�����ߵ��� �����.\n";
					text_ += "�׷�������¿����� ��� ���Ÿ� ������ ����Ȯ���� ���� �� �ְ� �ȴ�.\n";
					text_ += "��뿡�� �ߵ���ų�� �ʿ��ϸ� P�� �ణ �Ҹ�ȴ�.\n";
					break;
				case RGT_LEVITATION:
					text_ += "������ ����� �� �ִ� ����. �����ϸ� �ɷ»�뿡�� ����ߵ��� �����.\n";
					text_ += "������¿����� ������������ �ǳ� �� �ְԵȴ�.\n";
					text_ += "��뿡�� �ߵ���ų�� �ʿ��ϸ� P�� �ణ �Ҹ�ȴ�.\n";
					break;
				case RGT_INVISIBLE:
					text_ += "������ ����� �� �ִ� ����. �����ϸ� �ɷ»�뿡�� ����ߵ��� �����.\n";
					text_ += "������¿����� ������ ��ų Ȯ���� �ſ� �������� �ȴ�.\n";
					text_ += "������¿����� P�� �Ҹ��� ���ӵǴ� ������ �ִ�.\n";
					text_ += "��뿡�� �ߵ���ų�� �ʿ��ϸ� P�� �ణ �Ҹ�ȴ�.\n";
					break;
				case RGT_MANA:
					text_ += "����� �ִ븶���� �����ϴ� ����.\n";
					text_ += "���������� ������� ���ƿ´�.\n";
					break;
				case RGT_MAGACIAN:
					text_ += "����� ������������ �����Ŀ��� ��½�Ű�� ����.\n";
					break;
				case RGT_AC:
					text_ += "����� �� �����ϴ� ����.\n";
					text_ += "������ �Ǵ� ��ġ�� ������ ������ ���ڿ� ����.\n";
					break;
				case RGT_EV:
					text_ += "����� ȸ�ǰ� �����ϴ� ����.\n";
					text_ += "���� �Ǵ� ��ġ�� ������ ������ ���ڿ� ����.\n";
					break;
				case RGT_CONFUSE_RESIS:
					text_ += "����� ȥ���� ���⿡ ������ ����� ����.\n";
					break;
				case RGT_ELEC_RESIS:
					text_ += "����� ���������� �ö󰡴� ����.\n";
					text_ += "�Ϻ��ϰ� �������� ������ ����� �������� �ٿ��ش�.\n";
					break;
				case RGT_MAGIC_RESIS:
					text_ += "����� ���������� �ö󰡴� ����.\n";
					text_ += "���������� �������� �ٿ����� �������� ��������� �������κ��� ��ȣ���ش�.\n";
					break;
				default:
					text_ += "������ ���� ��� ������.\n";
					break;
				}
			}
			else
			{
				text_ += "������ ���� ����ִ� ����.\n";
				text_ += "����� �ٷ� �� ���� �� �� �ִ� ������ �ִ� �ݸ�. ��ġä�� ���� ������ �ִ�.\n";
			}
		}
		break;
	case ITM_BOOK:
		{
			text_ += "å�̴�.\n\n\n";
			if(it->identify)
			{
				char temp[100], sp_char='a';
				sprintf(temp,"%-34s%-30s%s\n","�����̸�","����","����");
				text_ += temp;
				for(int i=0;i<8;i++)
				{
					spell_list spell_;
					if((spell_ = (spell_list)it->GetValue(i+1)) != SPL_NONE)
					{
						sprintf(temp,"%c - %-30s%-30s%d\n",sp_char++,SpellString(spell_),GetSpellSchoolString(spell_).c_str(),SpellLevel(spell_));
						text_ += temp;
					}
				}
			}
		}
		break;
	case ITM_MISCELLANEOUS:
		{
			switch(it->value1)
			{
			case EVK_PAGODA:
				text_ += "�������� �Ҿ���� ��ž. ������ ���� ����ִ�.\n";
				text_ += "�ߵ��ϰԵǸ� �ȿ� ���ִ� ���� �������� ���·� �߻�ȴ�.\n";
				break;
			case EVK_AIR_SCROLL:
				text_ += "����� �������� ���� �ִ� ����. ������ ���� ��� �ִ�.\n";
				text_ += "�ߵ��ϰԵǸ� �Ŀ��� �밡�� ������� ������ ���İ��� ȸ�������ش�.\n";
				break;
			case EVK_DREAM_SOUL:
				text_ += "���� ���迡�� �ظް��ִ� ��ȥ�̴�.\n";
				text_ += "����ϸ� ���� ����κ��� ȯ���� ��üȭ�� ��õ��� �����ϴ�.\n";
				text_ += "����� ������ �ִ� ���� �������� �Ʊ��� �Ǿ� ��ȯ�ȴ�.\n";
				break;
			default:
				text_ += "���׸� ���� �ߵ����̴�.\n";
				break;
			}
			text_ += "\n\n";					
			text_ += "�� ���� Ƚ�����Ѿ��� �ߵ��� ������ ���̴�. ����� �ߵ���ų�� ����ؼ� �������� �����ȴ�.\n";
			text_ += "VŰ�� �Ŀ��� �Ҹ��Ͽ� �ߵ��� �� �ִ�.\n\n";
			char temp[100];
			sprintf(temp,"�� �ߵ����� ����Ҷ����� �ʿ��� �Ŀ�: %d.%02d\n",Evokeusepower((evoke_kind)it->value1,true)/100,Evokeusepower((evoke_kind)it->value1,true)%100);
			text_ += temp;

		}
		break;

	case ITM_GOAL:
		text_ += "�̰��� ���� ������ ������ ������ ���̴�. \n";
		text_ += "3���� ������ �ֽɺ� ������ �Ż��� ���� �� �� �ִ�.\n";
		break;
	case ITM_ORB:
		text_ += "�̰��� ������ ���� ���� ������̴�. �Ż� ���ο� �����ϰ� ����� �ִ�.\n";
		text_ += "�� ���� ������ Ż���ϸ� �� �̺��� �����ų� ��û�� ���� ���� �� ���� �� ����.\n";
		text_ += "��� ����ϴ����� ����� �����̴�! �׷��� Ż���Ҷ����� ���� �ƴϹǷ� �����ϱ�!\n";
		text_ += "Ư�� �Ż��� ȫ���� ���డ ���� ���� Ű�� ����� �Ѿƿ� ���̴�.\n";
		break;
	default:
		text_ += "�������̴�. �����ڿ��� �Ű�����.\n";
		break;
	}




	if(it->isArtifact() && it->identify)
	{
		text_ += "\n\n";
		for(auto it2 = it->atifact_vector.begin(); it2 != it->atifact_vector.end(); it2++)
		{
			text_ += GetAtifactInfor((ring_type)it2->kind, it2->value);
			text_ += "\n";
		}
	}

	//char temp[100];
	//if(!it->is_pile || it->num == 1)
	//	sprintf(temp,"\n\n\n���� : %g\n",it->weight);
	//else
	//	sprintf(temp,"\n\n\n���� : %g * %d\n",it->weight/it->num,it->num);
	//text_ += temp;
	return text_;

}