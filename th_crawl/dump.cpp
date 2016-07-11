//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: dump.cpp
//
// ����: ��������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <direct.h>
#include <stdio.h>
#include <time.h>
#include "player.h"
#include "display.h"
#include "environment.h"
#include "skill_use.h"
#include "note.h"
#include "god.h"
#include "dump.h"
#include "network.h"
#include "save.h"

extern const char *version_string;






extern display_manager DisplayManager;


action_class::action_class():type(DACT_MELEE),name()
{
	for(int i=0;i<27;i++)
		num[i] = 0;

}

action_class::action_class(dump_action_type type_, string name_, int level_)
	:type(type_), name(name_)
{
	for(int i=0;i<27;i++)
		num[i] = 0;
	num[level_-1] = 1;
}

void action_class::SaveDatas(FILE *fp)
{
	SaveData<dump_action_type>(fp, type);
	
	char temp[100];
	sprintf(temp,"%s",name.c_str());
	SaveData<char>(fp,*temp, strlen(temp)+1);

	for(int i=0;i<27;i++)
		SaveData<int>(fp, num[i]);	
}
void action_class::LoadDatas(FILE *fp)
{	
	LoadData<dump_action_type>(fp, type);

	char temp[100];
	LoadData<char>(fp, *temp);
	name = temp;

	for(int i=0;i<27;i++)
		LoadData<int>(fp, num[i]);	

}













int caculScore()
{
	//����ġ+���ϳ��� 500000��
	int base = you.exper * 99; //���� 19���� 185000
	base += 5000000 * you.haveGoal();


	if(you.dead_reason == DR_ESCAPE && you.haveOrb())
	{ //Ŭ���� �ߴ�.
		base += 500000; //Ŭ���� ���ʽ� ����
		double multi = 2 * (max(you.turn,5000) +10000)/ (max(you.turn,5000)) - min(you.turn,200000)/200000;
		multi = max(multi,1.2);
		base*=multi;
	}
	if(!you.GetCharNameString()->empty()) //ĳ���� �г�Ƽ
	{		
		base*=0.7;
	}
	base/=2;
	return base;
}


bool Dump(int type)
{
	char filename[100];
	char sql_[256];
	mkdir("morgue");
	FILE *fp;  
	struct tm *t;
	time_t now;
	time(&now);
	t=localtime(&now);

	sprintf_s(filename,100,"morgue/%s-%04d%02d%02d-%02d%02d%02d.txt",you.user_name.name.c_str(),1900+t->tm_year,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	fp = fopen(filename,"wt");
	
	fprintf_s(fp,"����ũ�� %s ���� ����\n\n",version_string);
	if(type == 1)
	{
		char death_reason[64] = "";
		char temp_reason[64];

		if(wiz_list.wizard_mode == 1)
		{
			fprintf_s(fp,"*���ڵ� ���*\n");
		}
		else if(wiz_list.wizard_mode == 2)
		{
			fprintf_s(fp,"*���̺� ����*\n");
		}
		fprintf_s(fp,"%d    ���� %d�� %s %s %s \"%s\" (HP %d/%d)\n",caculScore(),you.level,tribe_type_string[you.tribe],job_type_string[you.job],you.GetCharNameString()->c_str(), you.user_name.name.c_str(),you.hp,you.max_hp);
		fprintf_s(fp,"             %s���� ",CurrentLevelString());
		switch(you.dead_reason)
		{
			case DR_NONE:
				strncat(death_reason,"�˼����� ����",64);
				if(you.dead_order)
				{
					sprintf_s(temp_reason,64,"(%d ������", you.dead_order->damage);
					strncat(death_reason,temp_reason,64);
					if(you.dead_order->order)
					{
						sprintf_s(temp_reason,64,",%s", you.dead_order->order->GetName()->name.c_str());
						strncat(death_reason,temp_reason,64);

					}
					strncat(death_reason,")",64);
				}
				strncat(death_reason,"�� ���� �׾���.",64);
				break;
			case DR_HITTING:
				if(you.dead_order)
				{
					if(you.dead_order->order)
					{
						sprintf_s(temp_reason,64,"%s", you.dead_order->order->GetName()->name.c_str());
						strncat(death_reason,temp_reason,64);
					}
					switch(you.dead_order->type)
					{
						case ATT_NONE:
						case ATT_SMITE:
						default:
							if(you.dead_order->order)
								strncat(death_reason,"�� ���� ",64);
							strncat(death_reason,"�׾���.",64);
							break;
						case ATT_BLOOD:
							if(you.dead_order->order)
								strncat(death_reason,"�� ���� ",64);
							strncat(death_reason,"�Ǹ� ���ϸ� �׾���.",64);
							break;
						case ATT_NOISE:
							if(you.dead_order->order)
								strncat(death_reason,"�� ������ ���� ",64);
							strncat(death_reason,"���� �����׾���.",64);
							break;
						case ATT_SPEAR:
							if(you.dead_order->order)
								strncat(death_reason,"���� ",64);
							strncat(death_reason,"����׾���.",64);
							break;
						case ATT_NORMAL:
						case ATT_S_POISON:
						case ATT_M_POISON:
						case ATT_SICK:
						case ATT_NORMAL_HIT:
						case ATT_CURSE:
						case ATT_WEATHER:
						case ATT_AUTUMN:
						case ATT_CHOAS:
							if(you.dead_order->order)
								strncat(death_reason,"���� ",64);
							strncat(death_reason,"�¾��׾���.",64);
							break;
						case ATT_VAMP:
							if(you.dead_order->order)
								strncat(death_reason,"���� ",64);
							strncat(death_reason,"�����׾���.",64);
							break;
						case ATT_WALL:
							if(you.dead_order->order)
								strncat(death_reason,"���� ",64);
							else
								strncat(death_reason,"���� ",64);
							strncat(death_reason,"�ε��� �׾���.",64);
							break;
						case ATT_STONE_TRAP:
							strncat(death_reason,"������ �����߰����� ���� �׾���.",64);
							break;
						case ATT_THROW_NORMAL:
						case ATT_THROW_WATER:
							if(you.dead_order->order)
								strncat(death_reason,"���� ",64);
							strncat(death_reason,"��ź���ߴ�.",64);
							break;
						case ATT_NORMAL_BLAST:
						case ATT_AC_REDUCE_BLAST:
							if(you.dead_order->order)
								strncat(death_reason,"���� ",64);
							strncat(death_reason,"������ߴ�.",64);
							break;
						case ATT_FIRE:
						case ATT_THROW_FIRE:
						case ATT_CLOUD_FIRE:
						case ATT_FIRE_BLAST:
						case ATT_FIRE_PYSICAL_BLAST: 
							if(you.dead_order->order)
								strncat(death_reason,"�� ���� ",64);
							strncat(death_reason,"��Ÿ�׾���.",64);
							break;
						case ATT_COLD:
						case ATT_THROW_COLD:
						case ATT_CLOUD_COLD:
						case ATT_COLD_BLAST: 
						case ATT_COLD_PYSICAL_BLAST: 
							if(you.dead_order->order)
								strncat(death_reason,"�� ���� ",64);
							strncat(death_reason,"����׾���.",64);
							break;
						case ATT_CLOUD_ELEC:
							if(you.dead_order->order)
								strncat(death_reason,"�� ���� ",64);
							strncat(death_reason,"�����Ǿ��׾���.",64);
							break;
						case ATT_CLOUD_NORMAL:
							if(you.dead_order->order)
								strncat(death_reason,"�� ���� ",64);
							strncat(death_reason,"�ٶ��� �۾��� �׾���.",64);
							break;
						case ATT_CLOUD_CURSE:
							if(you.dead_order->order)
								strncat(death_reason,"�� ���� ",64);
							strncat(death_reason,"���ֹ޾� �׾���.",64);
							break;
						case ATT_BURST:
							if(you.dead_order->order)
								strncat(death_reason,"�� ���� ",64);
							strncat(death_reason,"�����׾���.",64);
							break;
					}
					sprintf_s(temp_reason,64,"(%d ������)", you.dead_order->damage);
					strncat(death_reason,temp_reason,64);
				}
				else
					strncat(death_reason,"�˼����� �������� ���� �׾���.",64);
				break;
			case DR_POISON:
				strncat(death_reason,"���� �ߵ��Ǿ� �׾���.",64);
				break;
			case DR_POTION:	
				strncat(death_reason,"���࿡ ����",64);
				if(you.dead_order){
					sprintf_s(temp_reason,64,"(%d ������)", you.dead_order->damage);
					strncat(death_reason,temp_reason,64);
				}
				strncat(death_reason,"�� ���� �׾���.",64);
				break;
			case DR_QUIT:
				strncat(death_reason,"������ �����ߴ�.",64);
				break;
			case DR_HUNGRY:
				strncat(death_reason,"�����׾���.",64);
				break;
			case DR_MIRROR:
				if(you.dead_order)
				{
					if(you.dead_order->order)
					{
						sprintf_s(temp_reason,64,"%s", you.dead_order->order->GetName()->name.c_str());
						strncat(death_reason,temp_reason,64);
						strncat(death_reason,"�� ",64);
					}

				}
				strncat(death_reason,"�ݻ絥������ �׾���.",64);
				if(you.dead_order)
				{
					sprintf_s(temp_reason,64,"(%d ������)", you.dead_order->damage);
					strncat(death_reason,temp_reason,64);
				}
				break;

			case DR_EFFECT:
				strncat(death_reason,"���ۿ뿡 ���� �׾���.",64);
				break;
			case DR_ESCAPE:
				if(you.haveOrb()){
					sprintf_s(temp_reason,64,"������� %d���� ���� ��� Ż���ϴµ� �����ߴ�.", you.haveGoal());
					strncat(death_reason,temp_reason,64);
				}
				else if(you.haveOrb()){
					sprintf_s(temp_reason,64,"%d���� �鸸 ��� �����ƴ�.", you.haveGoal());
					strncat(death_reason,temp_reason,64);
				}
				else
					strncat(death_reason,"�������� Ż���ߴ�.",64);
				break;
		}		

		fprintf_s(fp,"%s\n             ",death_reason);
		fprintf_s(fp,"������ %d\n\n",you.turn);
		
		sprintf_s(sql_,256,"'%s'|%d|%d|'%s'|'%s'|'%s'|'%s'|%d|'%s'|%d|'%s'",you.user_name.name.c_str(),you.level,caculScore(),tribe_type_string[you.tribe],job_type_string[you.job],you.GetCharNameString()->c_str(),death_reason,
			you.turn,(you.god == GT_NONE)?"":GetGodString(you.god),you.haveGoal(),version_string
			);


	}

	fprintf_s(fp,"%s (%s %s %s)      ��: %d      ",you.user_name.name.c_str(),tribe_type_string[you.tribe],job_type_string[you.job],you.GetCharNameString()->c_str(),you.turn);




	if(you.god == GT_NONE)
	{
		fprintf_s(fp,"���ž�\n\n");
	}
	else
	{
		fprintf_s(fp,"�ž�: %s %c%c%c%c%c%c\n\n",GetGodString(you.god),pietyLevel(you.piety)>=1?'*':'.',pietyLevel(you.piety)>=2?'*':'.',pietyLevel(you.piety)>=3?'*':'.',pietyLevel(you.piety)>=4?'*':'.',pietyLevel(you.piety)>=5?'*':'.',pietyLevel(you.piety)>=6?'*':'.');
	}
	fprintf_s(fp,"HP: %4d/%4d             AC:%4d             ��  :%4d\n",you.hp,you.max_hp,you.ac,you.s_str);
	fprintf_s(fp,"MP: %4d/%4d             EV:%4d             ��ø:%4d\n",you.mp,you.max_mp,you.ev,you.s_dex);
	fprintf_s(fp,"                          SH:%4d             ����:%4d\n\n",you.sh,you.s_int);
	int resist_ = you.fire_resist;
	int resist2_ = you.confuse_resist;
	fprintf_s(fp,"ȭ������: %c %c %c      ȥ������: %c           ����: " ,resist_>=1?'+':(resist_<=-1?'-':'.'),resist_>=2?'+':(resist_<=-2?'-':'.'),resist_>=3?'+':(resist_<=-3?'-':'.'),resist2_>=1?'+':(resist2_<=-1?'-':'.'));
	if(you.equipment[ET_WEAPON])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_WEAPON]->id,you.equipment[ET_WEAPON]->GetName().c_str());
	else
		fprintf_s(fp,"�Ǽ�\n");
	resist_ = you.ice_resist;
	resist2_ = you.invisible_view;
	fprintf_s(fp,"�ñ�����: %c %c %c      ������: %c           ź��: " ,resist_>=1?'+':(resist_<=-1?'-':'.'),resist_>=2?'+':(resist_<=-2?'-':'.'),resist_>=3?'+':(resist_<=-3?'-':'.'),resist2_>=1?'+':(resist2_<=-1?'-':'.'));
	if(you.throw_weapon)
		fprintf_s(fp,"%c) %s\n",you.throw_weapon->id,you.throw_weapon->GetName().c_str());
	else
		fprintf_s(fp,"����\n");
	
	resist_ = you.elec_resist;
	resist2_ = you.power_keep;
	fprintf_s(fp,"��������: %c %c %c      �Ŀ�����: %c           ����: " ,resist_>=1?'+':(resist_<=-1?'-':'.'),resist_>=2?'+':(resist_<=-2?'-':'.'),resist_>=3?'+':(resist_<=-3?'-':'.'),resist2_>=1?'+':(resist2_<=-1?'-':'.'));
	if(you.equipment[ET_ARMOR])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_ARMOR]->id,you.equipment[ET_ARMOR]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");

	
	resist_ = you.poison_resist;
	fprintf_s(fp,"������  : %c                                ����: ",resist_>=1?'+':(resist_<=-1?'-':'.'));
	if(you.equipment[ET_SHIELD])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_SHIELD]->id,you.equipment[ET_SHIELD]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");	
/*
	fprintf_s(fp,"                                           �Ӹ�: ");
	if(you.equipment[ET_HELMET])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_HELMET]->id,you.equipment[ET_HELMET]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");

	fprintf_s(fp,"                                           ����: ");
	if(you.equipment[ET_CLOAK])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_CLOAK]->id,you.equipment[ET_CLOAK]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");

	fprintf_s(fp,"                                           ��  : ");
	if(you.equipment[ET_GLOVE])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_GLOVE]->id,you.equipment[ET_GLOVE]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");

	fprintf_s(fp,"                                           ��  : ");
	if(you.equipment[ET_BOOTS])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_BOOTS]->id,you.equipment[ET_BOOTS]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");*/

	/*fprintf_s(fp,"                                           �����  : ");
	if(you.equipment[ET_NECK])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_NECK]->id,you.equipment[ET_NECK]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");	*/	

	fprintf_s(fp,"                                           �޹���  : ");
	if(you.equipment[ET_LEFT])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_LEFT]->id,you.equipment[ET_LEFT]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");

	fprintf_s(fp,"                                           ��������: ");      
	if(you.equipment[ET_RIGHT])
		fprintf_s(fp,"%c) %s\n",you.equipment[ET_RIGHT]->id,you.equipment[ET_RIGHT]->GetName().c_str());
	else
		fprintf_s(fp,"����\n");


	fprintf_s(fp,"\n\n����� %s�� �ִ�.\n",CurrentLevelString());

	fprintf_s(fp,"\n\n\n<�κ��丮>\n"/*,you.item_weight,you.max_item_weight*/);

	
	list<item>::iterator first,end;
	first = you.item_list.begin();
	end = you.item_list.end();

	for(item_type_simple i = ITMS_FIRST ;i != ITMS_LAST ; i=(item_type_simple)(i+1))
	{
		bool exist = false;
		list<item>::iterator it;
		for(it = first; it!=end;it++)
		{
			if((*it).isSimpleType(i))
			{
				int equip = you.isequip(it);
				if(!exist)
				{
					fprintf_s(fp,"\n%s\n",GetItemTypeSting(i));
					exist = true;
				}
				fprintf_s(fp,"  %c - %s",(*it).id,(*it).GetName().c_str());
				if(equip)
					fprintf_s(fp,"%s",(equip==1?"(����)":(equip==2?"(�޼�)":"(������)")));
				fprintf_s(fp,"\n");
			}
		}
	}

	fprintf_s(fp,"\n\n\n<��ų>\n\n");

	int skt = 0;
	while(skt < SKT_MAX)
	{
		if(you.skill[skt].level)
			fprintf_s(fp,"  %4s %3d (%d%%)\n",skill_string((skill_type)skt),you.skill[skt].level,GetSkillPercent(you.skill[skt]));
		skt++;
	}


	fprintf_s(fp,"\n\n\n����ϰ� �ִ� �ֹ���\n");
	if(you.currentSpellNum)
		fprintf_s(fp,"\n%-34s %-20s","�����̸�","����");
	for(int i=0;i<52;i++)
	{
		if(you.MemorizeSpell[i])
		{
			spell_list spell_ = (spell_list)you.MemorizeSpell[i];
			fprintf_s(fp,"\n%c - %-30s %-20s",i<26?'a'+i:'A'+(i-26),SpellString(spell_),GetSpellSchoolString(spell_).c_str());
		}
	}
	if(you.currentSpellNum)
		fprintf_s(fp,"\n\n����� %d���� ������ ���� ������ %d�� ���� ������ ���Ҵ�.\n",you.currentSpellNum,you.remainSpellPoiont);
	else
		fprintf_s(fp,"\n����� ������ ���� ���� �ʴ�.\n",you.currentSpellNum,you.remainSpellPoiont);



	
	fprintf_s(fp,"\n\n\n");


	if(!DisplayManager.text_log.text_list.empty())
	{
		list<text_dummy*>::iterator it;
		it = DisplayManager.text_log.text_list.end();
		it--;
		int view_length = DisplayManager.log_length;
		int i = 15;
		while(i)
		{
			if(it == DisplayManager.text_log.text_list.begin())
				break;
			it--;
			if((*it)->enter)
			{
				i--;
				if(i<=0)
				{
					it++;
					break;
				}
			}
		}
		float x = 0, y = 0;
		for(i = 0;i < view_length && it != DisplayManager.text_log.text_list.end();it++)
		{			
			
			fprintf_s(fp,"%s", (*it)->text.c_str());
			if((*it)->enter)
			{
				fprintf_s(fp,"\n", (*it)->text.c_str());
			}
		}
	}


	fprintf_s(fp,"\n\n\n");
	fprintf_s(fp,"%8s|%-18s|%s\n","��","���","����");

	for(list<note_dummy>::iterator it = save_note.note_list.begin(); it != save_note.note_list.end(); it++)
	{
		fprintf_s(fp,"%8d|%-18s|%s\n",it->turn,it->place.c_str(),it->text.c_str());
	}
	fprintf_s(fp,"\n\n\n");
	
	fprintf_s(fp,"%-26s","  ");
	for(int i=0;i<9;i++)
		fprintf_s(fp,"�� %2d-%2d",1+i*3,3+i*3);
	fprintf_s(fp,"��  �հ�\n");



	dump_action_type type_ = DACT_NONE;
	for(auto it = you.action_vector.begin(); it != you.action_vector.end(); it++)
	{
		int total_ = 0;
		if(it->type != type_)
		{
			type_ = it->type;

			fprintf_s(fp,"%-4s----------------------",GetDumpActionString(type_));
			for(int i=0;i<9;i++)
				fprintf_s(fp,"��------");
			fprintf_s(fp,"��������\n");
		}

		fprintf_s(fp,"%26s",it->name.c_str());
		for(int i=0;i<9;i++)
		{
			int add_ = it->num[0+i*3]+it->num[1+i*3]+it->num[2+i*3];
			fprintf_s(fp,"��%6d",add_);
			total_ += add_;
		}

		fprintf_s(fp,"��%6d\n",total_);
	}





	fclose(fp);
	if(type == 1 && !wiz_list.wizard_mode)
		sendScore(sql_,filename);
	return true;
}
const char* GetDumpActionString(dump_action_type type_)
{
	switch(type_)
	{
	case DACT_MELEE:
		return "����";
	case DACT_SHOOT:
		return "ź��";
	case DACT_SPELL:
		return "����";
	case DACT_INVOKE:
		return "�Ǵ�";
	case DACT_EVOKE:
		return "�ߵ�";
	case DACT_USE:
		return "�Ҹ�";
	default:
		return "��Ÿ";
	}

}
