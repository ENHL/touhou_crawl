//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: tensi.cpp
//
// ����: �ٽ� Ŭ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "tensi.h"
#include "environment.h"
#include "enum.h"
#include "mon_infor.h"
#include "skill_use.h"
#include "beam.h"
#include "god.h"
#include "note.h"
#include "potion.h"
#include "rect.h"
#include "alchemy.h"
#include "weapon.h"


const char* tensi_talk(bool good_, tensi_do_list list_);

int GetHazard()
{
	float total_danger_ = 0; //���赵

	int num_=0; //������� ������ �Ǵ� ���� ��
	vector<monster>::iterator it;
	it = env[current_level].mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != env[current_level].mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && env[current_level].isInSight(it->position)/* (*it).isYourShight()*/)
		{
			float danger_ = 0;
			if((*it).flag & M_FLAG_UNHARM)
			{ //������ ���̴�.

			}				
			else if((*it).isUserAlly())
			{ //�Ʊ��̴�. 

			}
			else
			{ //���̴�.
				danger_ = 10;
				if((*it).level > you.level)
					danger_ = 800+((*it).level - you.level)*300; //�ڽź��� ������ ������ ���赵 800����
				else if( you.level - (*it).level <= 6)
					danger_ = 500+70*((*it).level - you.level); //�ణ ���ϴ�
				//�������� ���� �ǹ̾��� ���� ���赵 1�� �ش�.

				int min_ = 0;
				if((*it).level>=10)//������ 10�̻��̸� �پ��� Ư���ɷ¶����� �������Ե� �ణ�� ������ �ش�.
					min_ = 100; //�ּ� ����ġ 100
				if((*it).level>=13)
					min_ = 200;
				if((*it).level>=15)
					min_ = 300;
				if((*it).level>=20)
					min_ = 500;

				
				
				danger_ = max(danger_,min_);

				if(!you.isSightnonblocked(it->position))
					danger_ = 1;
				//��� �����ִ�.
				
				int distant_ = pow((float)abs(it->position.x-you.position.x),2)+pow((float)abs(it->position.y-you.position.y),2);
				bool melee_ = true;//�� ���� �������̴�.
				bool smite_ = false;//�� ���� ���� ���θ����־ �������̴�.

				if(!(*it).s_mute || env[current_level].isSilence(it->position))
				{
					for(auto it2 = it->spell_lists.begin();it2!= it->spell_lists.end(); it2++)
					{
						int length_ = SpellLength((spell_list)it2->num);
						if(!length_ || !(distant_ > length_*length_))
						{
							if(SpellFlagCheck((spell_list)it2->num,S_FLAG_RANGE_ATTACK))
							{
								melee_ = false; //���Ÿ� ���̴�.
							}		
							//if(SpellFlagCheck((spell_list)it2->num,S_FLAG_RANGE_ATTACK)|| SpellFlagCheck((spell_list)it2->num,S_FLAG_DEBUF))
							//{
							//	//�Ÿ��� �־����־ ��ſ��� ������ �� ���ɼ��� ����
							//}
							//������� ���������� ������ ���� �ʴ´�.
							if(SpellFlagCheck((spell_list)it2->num,S_FLAG_SUMMON) || SpellFlagCheck((spell_list)it2->num,S_FLAG_SMITE))
							{
								//��ȯ�� ������Ʈ
								melee_ = false; //���Ÿ� ���̴�.
								smite_ = true;
								break;
							}
						}

					}
				}
				else if(!it->spell_lists.empty())
					danger_ *= 0.5f;
					

				if(melee_)
				{ //�и����� �Ÿ��� ���� ���� 
					float mul_ = 1.2f-0.075f*max(abs(you.position.x-it->position.x),abs(you.position.y-it->position.y));
					//���� �ָ� ������ 0.6f ������ 1.2��
					danger_*=mul_;
				}
				
				if(!smite_)
				{
					beam_iterator beam(it->position,you.position);
				
					for(beam.init();!beam.end();beam++)
					{
						unit *temp = env[current_level].isMonsterPos((*beam).x,(*beam).y);
						if(temp)
						{			
							if(temp->isLive() && !temp->isEnemyMonster(&(*it)) && !temp->isPassedBullet(&(*it)))
							{
								danger_*=0.5f;
								break;
								//������������ ���赵�� ���� �پ���.
							}
						}
					}
				}
				else
					danger_*=1.5f; //������Ʈ���� ��ü�� ���赵�� ����.

				if((*it).s_confuse || (*it).s_paralyse || (*it).s_fear) //ȥ�� ���� ������ ���� ���赵�� ����������.
					danger_ *= 0.05f;
				if((*it).s_slow)
					danger_ *= 0.5f;
				if((*it).s_haste)
					danger_ *= 1.5f;
				if((*it).s_invisible && !you.s_invisible)
					danger_ *= 1.5f;
				if((*it).s_might)
					danger_ *= 1.5f;
				if((*it).state.GetState() != MS_ATACK)
					danger_ *= 0.2f; //������ �ƴϴ�.

				danger_ *=  0.5f+0.5f*((float)(*it).hp)/(*it).max_hp;

				
				if((*it).flag & M_FLAG_UNIQUE)
					danger_*=2.0f; //���ӵ�� ������

				num_++;
			}

			total_danger_ += danger_;
		}
	}

	if(you.s_paralyse)
		total_danger_ *= 5;
	
	if(you.s_confuse || you.s_lunatic)
		total_danger_ *= 3;

	if(you.s_slow)
		total_danger_ *= 2;
	
	if(you.s_haste)
		total_danger_ *= 0.7f;
	if(you.s_might || you.s_clever || you.s_dex)
		total_danger_ *= 0.7f;

	if(((float)you.hp)/you.max_hp <= 0.5f) //ü���� ��������
		total_danger_ *=  3.0f-2.0f*((float)you.hp)/you.max_hp;
	
	if(you.max_mp>=5 && ((float)you.mp)/you.max_mp <= 0.5f) //������ ��������
		total_danger_ *=  3.0f-2.0f*((float)you.hp)/you.max_hp;


	if(you.s_the_world)
		total_danger_ *= 0.1f;

	return (int)total_danger_;
}


void tensi_potion(bool good_)
{
	potion_type good_list_[6] = {PT_MIGHT,PT_HASTE,PT_HEAL_WOUND, PT_CLEVER,PT_AGILITY,PT_RECOVER_STAT};
	potion_type bad_list_[5] = {PT_POISON, PT_CONFUSE, PT_SLOW, PT_DOWN_STAT,PT_ALCOHOL};

	potion_type you_drink_ = PT_WATER;
	
	if(good_)
		you_drink_ = good_list_[randA(5)];
	else		
		you_drink_ = bad_list_[randA(4)];


	drinkpotion(you_drink_);
}







void tensi_summon(int good_)
{

	vector<int> summon_vector;


	if(you.level<=5)
	{
		summon_vector.push_back(MON_MOOK);
		summon_vector.push_back(MON_CROW);
		summon_vector.push_back(MON_SNAKE);
		summon_vector.push_back(MON_SPIDER);
		summon_vector.push_back(MON_FIREFLY);
	}
	else if(you.level<=10)
	{
		summon_vector.push_back(MON_SNAKE);
		summon_vector.push_back(MON_CRANE);
		summon_vector.push_back(MON_BAKEKASA);
		summon_vector.push_back(MON_FROG);
	}
	else if(you.level<=14)
	{
		summon_vector.push_back(MON_FROG);
		summon_vector.push_back(MON_BLACK_CAT);
		summon_vector.push_back(MON_EAGLE);
		summon_vector.push_back(MON_YAMABIKO);
	}
	else if(you.level<=16)
	{
		summon_vector.push_back(MON_TIGER);
		summon_vector.push_back(MON_RAIJUU);
		summon_vector.push_back(MON_EAGLE);
		summon_vector.push_back(MON_AYAYUKKURI);
	}
	else if(you.level<=20)
	{
		summon_vector.push_back(MON_AYAYUKKURI);
		summon_vector.push_back(MON_REMILIAYUKKURI);
		summon_vector.push_back(MON_RED_UFO);
		summon_vector.push_back(MON_GREEN_UFO);
		summon_vector.push_back(MON_ONI);
	}
	else if(you.level<=24)
	{
		summon_vector.push_back(MON_DRAGON_BABY);
		summon_vector.push_back(MON_YOUMUYUKKURI);
		summon_vector.push_back(MON_NAMAZ);
		summon_vector.push_back(MON_FLOWER_TANK);
		summon_vector.push_back(MON_ONI);
	}
	else
	{
		summon_vector.push_back(MON_DRAGON_BABY);
		summon_vector.push_back(MON_YOUMUYUKKURI);
		summon_vector.push_back(MON_NAMAZ);
		summon_vector.push_back(MON_FLOWER_TANK);
		summon_vector.push_back(MON_ONI);
	}


	if(!summon_vector.empty())
	{
		dif_rect_iterator rit(you.position,2);
		int i = randC(abs(good_),3); 
		for(;!rit.end() && i> 0;rit++)
		{
			if(summon_check(coord_def(rit->x,rit->y), you.position, false, false))
			{
				int flag_=M_FLAG_SUMMON;
				if(good_>0)
					flag_ |= M_FLAG_ALLY;
				int id_ = summon_vector[randA(summon_vector.size()-1)] ;

				summon_info s_(you.GetMapId(),SKD_OTHER,GetSummonMaxNumber(SPL_NONE));
				if (monster* mon_ = env[current_level].AddMonster_Summon(id_, flag_, (*rit), s_, rand_int(100, 200)))
				{

					mon_->CheckSightNewTarget();

				}
				i--;
			}
		}
	}
}

void tensi_kaname(int good_)
{
	for (int i = rand_int(1 + 2 * abs(good_), 1 + 3 * abs(good_));  i> 0; i--)
	{
		int flag_ = M_FLAG_SUMMON;
		if (good_>0)
			flag_ |= M_FLAG_ALLY;
		int id_ = MON_KANAME;

		if (monster* mon_ = BaseSummon(MON_KANAME, rand_int(60, 100), false, true, 4, good_>0?&you:NULL, you.position, SKD_OTHER, -1))
		{
			int fanalty_ = randA(randA(you.level));
			mon_->LevelUpdown(you.level - fanalty_);
			if (mon_->level<7)
				mon_->spell_lists.push_back(spell(SPL_MON_TANMAC_SMALL, 50));
			else if (mon_->level<15)
				mon_->spell_lists.push_back(spell(SPL_MON_TANMAC_MIDDLE, 25));
			else
				mon_->spell_lists.push_back(spell(SPL_MON_TANMAC_MIDDLE, 50));
			mon_->CheckSightNewTarget();
		}
	}

}

void tensi_tele(bool good_)
{
	int max_monster_ = good_?99:0;
	coord_def final(0,0);
	for(int i = 0; i < 20; i++)
	{
		int monster_ = 0;
		coord_def c_;
		while(1)
		{
			int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			if(env[current_level].isMove(x_,y_) && !env[current_level].isMonsterPos(x_,y_))
			{
				c_ = coord_def(x_,y_);
				break;
			}
		}
		

		vector<monster>::iterator it;
		it = env[current_level].mon_vector.begin();
		for(int i=0;i<MON_MAX_IN_FLOOR && it != env[current_level].mon_vector.end() ;i++,it++)
		{
			if((*it).isLive() && !(*it).isUserAlly() && (*it).isMonsterSight(c_) )
			{					
				monster_++;
			}
		}
		if(good_ && monster_<max_monster_)
		{
			max_monster_=monster_;
			final = c_;
			if(monster_ == 0)
				break;
		}
		else if(!good_ && monster_>max_monster_)
		{			
			max_monster_=monster_;
			final = c_;
		}
	}
	if(env[current_level].isMove(final.x,final.y) && !env[current_level].isMonsterPos(final.x,final.y))
	{
		env[current_level].MakeSmoke(you.position, img_fog_normal, SMT_NORMAL, 4, 0, &you);
		you.SetXY(final);
	}
	else
	{
		if(wiz_list.wizard_mode == 1)
			printlog("�ٽ� �ڷ���Ʈ ����",true,false,false,CL_tensi);
		you.Teleport();
	}
}


void tensi_earthquake(int good_)
{
	for(int i=-8;i<=8;i++)
	{
		for(int j=-8;j<=8;j++)
		{
			coord_def pos = coord_def(i,j)+you.position;
			if(env[current_level].isInSight(pos) && env[current_level].dgtile[pos.x][pos.y].isBreakable())
			{
				if(randA(1)==0)
					env[current_level].dgtile[pos.x][pos.y].tile = DG_FLOOR;
			}
		}
	}//���� �ı��Ѵ�.

	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(it->isLive() && env[current_level].isInSight(it->position))
		{
			int att_ = randC(6,10+you.level/3);
			int m_att_ = 6*(10+you.level/3);
			if(it->isFly())
			{
				att_/=2;
				m_att_/=2;
			}
			attack_infor temp_att(att_,m_att_,99,&you,you.GetParentType(),ATT_NORMAL_BLAST,name_infor("����",true));
			it->damage(temp_att, true);
		}
	}//��� ���Ϳ��� �������� ��

	env[current_level].MakeNoise(you.position,30,NULL); //�Ŵ��� ������ �����. �ٽô� �ƹ��� ������ ������ ���⵵ ����!

}
void tensi_munyum(int good_)
{
	you.SetAlchemyBuff(ALCT_STONE_FORM,rand_int(100,200));
	//�ٽ��� ���乫�� ������ ���!
}
void tensi_burst(int good_)
{
	int num_ = 0;
	for(auto it = env[current_level].mon_vector.begin();; it++)
	{
		coord_def pos_;
		bool is_live = true;
		bool is_ally = true;

		if( it == env[current_level].mon_vector.end())
		{
			if(num_ && good_>0)
			{
				Sleep(300);
				env[current_level].ClearEffect();
				break;
			}
			else
			{
				pos_ = you.position; //������ �����ϰ�� �÷��̾���� �۾��� �� �ִ�.

			}

		}
		else
		{
			pos_ = it->position;			
			is_live = it->isLive();
			is_ally = it->isUserAlly();
		}



		if(is_live && env[current_level].isInSight(pos_))
		{
			if(good_<0 || (!is_ally && distan_coord(pos_,you.position) > 4))
			{//�Ʊ��� ������ �ִ� ���� ���������ʾ�. ���� �ٽ��� ����� �������� ������!
				vector<coord_def> vt_;
				{
					rect_iterator rit(pos_,1,1);
					for(;!rit.end();rit++)
					{
						if(env[current_level].isMove(rit->x,rit->y))
						{
							env[current_level].MakeEffect(*rit,&img_blast[randA(5)],false);
							vt_.push_back(*rit);
						}
					}
				}
				for(auto it2 = vt_.begin();it2 != vt_.end();it2++)
				{
					if(env[current_level].isMove(it2->x,it2->y))
					{
						if(unit* hit_ = env[current_level].isMonsterPos(it2->x,it2->y))
						{
							
							int att_ = randC(3,8+you.level/3);
							int m_att_ = 3*(8+you.level/3);

							if(hit_->isplayer())
							{ //�÷��̾�� ���� ����������
								if(att_ >= hit_->GetHp())
									att_ = hit_->GetHp()-1;
							}
							attack_infor temp_att(att_,m_att_,99,&you,you.GetParentType(),ATT_NORMAL_BLAST,name_infor("�ٽ�",false));
							hit_->damage(temp_att, true);
						}
					}
				}
				Sleep(100);
				num_++;
			}
		}
		if( it == env[current_level].mon_vector.end())
		{
			Sleep(300);
			env[current_level].ClearEffect();
			break;
		}
	}//��� ���Ϳ��� �������� ��
	
	
	env[current_level].MakeNoise(you.position,16,NULL); //����� ������ �����.

}


void tensi_weapon(int doing_)
{
	if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
	{
		printarray(true,false,false,CL_tensi,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"����� ����� �վ������´�.");
		you.equipment[ET_WEAPON]->value5 = WB_WEATHER;
		you.equipment[ET_WEAPON]->value6 = (70+randA(50))*(doing_>0?doing_*2:1);
	}
	else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_WEATHER && you.equipment[ET_WEAPON]->value6>0)
	{
		printarray(true,false,false,CL_tensi,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"���� ����� ���� �������.");
		you.equipment[ET_WEAPON]->value6 += (90+randA(50))*(doing_>0?doing_:1);
	}
	else
	{
		printlog("�׷��� �ƹ��ϵ� �Ͼ�� �ʾҴ�.",true,false,false,CL_normal);
	}
}

void tensi_action()
{
	if(wiz_list.wizard_mode == 1)
	{
		char temp[256];

		sprintf_s(temp,256,"[��:%d �ټ�:%d]",you.turn, you.CheckTension());
	
		printlog(temp,false,false,false,CL_tensi);
		
	}

	int doing_ = 0;
	tensi_do_list action_ = TENSI_NOTHING;

	if(you.CheckTension() < randA(100) || you.GetPunish(GT_TENSI))
	{

		int rand_ = randA(99);

		if(rand_>44+(you.GetPunish(GT_TENSI)?50:0))
		{
			action_ = TENSI_NOTHING;
		}
		else
		{
			switch(randA(5)){
			case 0:doing_ = -1; action_ =  TENSI_POTION; break;
			case 1:doing_ = rand_int(-1,-2); action_ =  TENSI_SUMMON; break;
			case 2:doing_ = -1; action_ =  TENSI_TELE; break;
			case 3:doing_ = -1; action_ =  TENSI_EARTHQUAKE; break;
			case 4:doing_ = -1; action_ =  TENSI_BURST; break;
			case 5:doing_ = -1; action_ = TENSI_KANAME; break;
			}
		}
	}
	else
	{
		if(100+randA(5000)<randA(you.CheckTension()))
		{ //�ٽ��� ���ټ� ����!			
			switch(randA(5)){
			case 0:doing_ = 1; action_ =  TENSI_EARTHQUAKE; break;
			case 1:doing_ = 2; action_ =  TENSI_SUMMON; break;
			case 2:doing_ = 1; action_ =  TENSI_MUNYUM; break;
			case 3:doing_ = 1; action_ =  TENSI_TELE; break; //�ٽô� ������ �����ϱ⶧���� ������ ���� �Ⱦ���.
			case 4:doing_ = 3; action_ =  TENSI_WEAPON; break;
			case 5:doing_ = 2; action_ = TENSI_KANAME; break;
			}
		}
		else if(randA(500)<randA(you.CheckTension()))
		{ //�׷����� ������
			
			switch(randA(4)){
			case 0:doing_ = 1; action_ =  TENSI_POTION; break;
			case 1:doing_ = 1; action_ =  TENSI_SUMMON; break;
			case 2:doing_ = 1; action_ =  TENSI_BURST; break;
			case 3:doing_ = 2; action_ =  TENSI_WEAPON; break;
			case 4:doing_ = 1; action_ = TENSI_KANAME; break;
			}
		}
		else if(randA(100)<randA(you.CheckTension()))
		{ //������
			switch(randA(2)){
			case 0:doing_ = 1; action_ =  TENSI_POTION; break;
			case 1:doing_ = 1; action_ =  TENSI_BURST; break;
			case 2:doing_ = 1; action_ =  TENSI_WEAPON; break;
			}
		}
		else
		{ //���� ������
			switch(randA(4)){
			case 0:doing_ = -1; action_ =  TENSI_POTION; break;
			case 1:doing_ = -1; action_ =  TENSI_SUMMON; break;
			case 2:doing_ = -1; action_ =  TENSI_TELE; break;
			case 3:doing_ = -1; action_ =  TENSI_BURST; break;
			case 4:doing_ = rand_int(-2,-1); action_ = TENSI_KANAME; break;
			}
		}

	}
	
	

	printlog(tensi_talk(doing_>0, action_),true,false,false,CL_tensi);
	switch(action_)
	{
	case TENSI_NOTHING:
		if(wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp,256,"�ٽ�: �ƹ��ϵ�����. �ټ� %d", you.CheckTension());
			AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		}
		break;
	case TENSI_POTION:
		if(wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp,256,"�ٽ�: ����. �ټ� %d �ൿ %d", you.CheckTension(), doing_);
			AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		}
		tensi_potion(doing_>0);
		break;
	case TENSI_SUMMON:
		if(wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp,256,"�ٽ�: ��ȯ. �ټ� %d �ൿ %d", you.CheckTension(), doing_);
			AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		}
		tensi_summon(doing_);
		break;
	case TENSI_TELE:
		if(wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp,256,"�ٽ�: �ڷ���Ʈ. �ټ� %d �ൿ %d", you.CheckTension(), doing_);
			AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		}
		tensi_tele(doing_);
		break;
	case TENSI_EARTHQUAKE:
		if(wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp,256,"�ٽ�: ����. �ټ� %d �ൿ %d", you.CheckTension(), doing_);
			AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		}
		tensi_earthquake(doing_);
		break;
	case TENSI_MUNYUM:
		if(wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp,256,"�ٽ�: ���乫��. �ټ� %d �ൿ %d", you.CheckTension(), doing_);
			AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		}
		tensi_munyum(doing_);
		break;
	case TENSI_BURST:
		if(wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp,256,"�ٽ�: ����. �ټ� %d �ൿ %d", you.CheckTension(), doing_);
			AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		}
		tensi_burst(doing_);
		break;
	case TENSI_WEAPON:
		if(wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp,256,"�ٽ�: ����ǰ�. �ټ� %d �ൿ %d", you.CheckTension(), doing_);
			AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		}
		tensi_weapon(doing_);
		break;
	case TENSI_KANAME:
		if (wiz_list.wizard_mode == 1)
		{
			char temp[256];
			sprintf_s(temp, 256, "�ٽ�: ī���޼�. �ټ� %d �ൿ %d", you.CheckTension(), doing_);
			AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		}
		tensi_kaname(doing_);
		break;
	}
}



attack_type GetWeatherType(unit* unit_, int damage_, int &bonus_damage_)
{
	int type_ = randA_1((int)WTL_MAX);
	if(randA(2)==0)
		type_ = WTL_NONE;
	switch(type_)
	{
	case WTL_FIRE:
		bonus_damage_ +=  unit_->GetFireResist()*(damage_/3);
		type_ = ATT_FIRE;
		break;
	case WTL_COLD:
		bonus_damage_ += unit_->GetColdResist()*damage_/3;
		type_ = ATT_COLD;
		break;
	case WTL_EARTH:
		bonus_damage_ += 9;
		type_ = ATT_NORMAL;
		break;
	case WTL_AIR:
		bonus_damage_ += unit_->GetElecResist()*damage_/3;
		type_ = ATT_ELEC;
		break;
	case WTL_POISON:
		type_ = ATT_S_POISON;
		break;
	case WTL_CHOAS:
		type_ = ATT_CHOAS;
		break;
	default:
		type_ = ATT_NORMAL;
		break;
	}
	return (attack_type)type_;
}


int GetChoas(unit* unit_, int damage_)
{	
	switch(randA(5))
	{
	case 0://WTL_CONFUSE,
		unit_->SetConfuse(5+randA(10));
		break;
	case 1://WTL_MUTE,
		unit_->SetMute(5+randA(10));
		break;
	case 2://WTL_GLOW,
		unit_->SetGlow(5+randA(10));
		break;
	case 3://WTL_TELE,
		unit_->SetTele(rand_int(3,6));
		break;
	case 4://WTL_SICK,
		unit_->SetSick(20+randA(30));
		break;
	case 5://WTL_PARA,
		unit_->SetParalyse(2+randA(5));
		break;
	}
	return 0;
}

const char* tensi_talk(bool good_, tensi_do_list list_)
{
	static char temp[256];
	if(list_ != TENSI_NOTHING && randA(2))
	{//������
		if(good_)
		{
			switch(randA(12))
			{
			case 0:
				return "�ٽð� ��ſ��� ȣ������ �ü��� �־���.";
			case 1:
				return "�ٽ��� ���� ��ſ��� ��Ҵ�.";
			case 2:
				return "�ٽ�: �����̳�!";
			case 3:
				return "�ٽ�: �����ٰ�!";
			case 4:
				return "����� �ٽ��� ���� �Ҹ��� �����.";
			case 5:
				return "�ٽð� ��������� �ü��� ���ߴ�.";
			case 6:
				return "�ٽ��� �ڼ��Ҹ��� �����.";
			case 7:
				return "��� �ֺ��� ��� ���� ����� �����°��� ������.";
			case 8:
				return "�ٽ�: �� �� ��̰� ����!";
			case 9:
				return "�ٽ�: ���� �� �� �� ����?";
			case 10:
				return "�ٽ�: ����!";
			case 11:
				return "�ٽ��� ������ ���� �޾Ҵ�.";
			case 12:
				return "�ٽô� ��������ϰ� ����� ������ �ٶ󺸰��ִ�.";
			}
		}
		else
		{
			switch(randA(14))
			{
			case 0:
				return "�ٽ��� ����� �ü��� ��������.";
			case 1:
				return "�ٽð� ���� �����ߴ�.";
			case 2:
				return "�ٽð� ����� ������ �����ϴٰ� �����ߴ�.";
			case 3:
				return "�ٽ�: �̷��� ���?";
			case 4:
				return "�ٽ�: �� �� �����ְ� ���ٰ�!";
			case 5:
				return "�ٽ�: �ʹ� ��ȭ���� �ʾ�?";
			case 6:
				return "�ٽ��� �峭�� ������ �����.";
			case 7:
				return "�ٽð� ��ſ��� �÷��� �ַ��ϰ� �ִ�.";
			case 8:
				return "�ٽ�: ������ �ͺ��� ����?";
			case 9:
				return "�ٽ�: �� ȭ�� ����!";
			case 10:
				return "�ٽ�: ������ ������ ������ �������� ����!";
			case 11:
				return "�ٽ�: �ǹ���!";
			case 12:
				return "�ٽ�: �������ݾ�!";
			case 13:
				return "�ٽ�: �ʹ� ���Ѱ� �ƴϾ�?";
			case 14:
				return "�ٽ�: �����Ѱ� �� �����̾�!";
			}
		}

	}
	else 
	{
		switch(list_)
		{
		case TENSI_NOTHING:
			switch(randA(20))
			{
			case 0:
				return "���� ���� ����ͼ� ����� �Ӹ��� �¾Ҵ�.";
			case 1:
				return "���ڱ� �ٴ��� �����ߴ�.";
			case 2:
				return "�ٽ�: ���� �̾߱� ���� ������?";
			case 3:
				return "�ٽ�: �����ϴ� ������ ����?";
			case 4:
				return "�ٽ�: õ��� �ʹ� �ɽ���!";
			case 5:
				return "�ٽ�: �� �� ����ϰ� �ൿ����!";
			case 6:
				return "�ٽ�: �� ����ִ°� ���� �;�!";
			case 7:
				return "�ٽ�: ���� �� �� ��հ� ���� �� �ִµ�";
			case 8:
				return "�ٽ�: �����ϰ� �ϸ� ����?";
			case 9:
				return "�߿� ��ī�ο� ������ Ƣ��� �Ѿ������߰�, �������� �����Ҹ��� ��ȴ�.";
			case 10:
				return "����� �ٷ� ���� ��ī�ο� �伮�� ��������. \"�Ʊ���!\"";
			case 11:
				return "�ٽ�: �� ������ �������� �ٶ󺸰��ִ°� �� ���̾�!";
			case 12:
				return "�ٽ�: �ٷ� ������������? �� �� ��ƿ �� ����?";
			case 13:
				return "�ٽ�: ��������, ��� ������ ����� ���� ������?";
			case 14:
				sprintf_s(temp,256,"�ٽ�: ������ ���Ѻ��� ���̴� %s�� �׾���Ⱦ�.",mondata[randA(MON_MAX-1)].name.name.c_str());
				return temp;
			case 15:
				{
					int rand_name_ = randA(MON_MAX-1);
					sprintf_s(temp,256,"�ٽ�: %s%s �� �̷��� %s�ɱ�? ",mondata[rand_name_].name.name.c_str(),mondata[rand_name_].name.name_is(),randA(1)?"������":"�Ϳ���");
					return temp;
				}
			case 16:
				return "�ٽ�: ���ݸ� ��ٷ�, ��¦ ��Ƽ�� �غ��ϰ� �����ϱ�!";
			case 17:
				return "����� �̸��� ���׸� ���� ����� �ε�����.";
			case 18:
				return "�ٽ�: ��մ� �̾߱�� ����!";
			case 19:
				return "�ٽô� ����� �񸮱� ���� ��ȹ�� ����� �ִ�.";
			case 20:
				return "�ٽô� �����ѵ� ��ǰ�� �ߴ�.";
			}	
		case TENSI_POTION:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return "�ٽð� ��ſ��� ���ο� ���� �־���.";
				case 1:
					return "�ٽ�: �񸶸����ʾ�?";
				case 2:
					return "�ٽ�: �̰ɷ� �� �� �ο�!";
				case 3:
					return "�ٽ�: ���� �� ��̰� ���� �� ����?";
				case 4:
					return "����� �ٽð� ������ ������ �޾Ҵ�.";
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return "�ٽ��� �����Ҹ��� ����� �Ӹ��� ��ȴ�.";
				case 1:
					return "�ٽ�: �츮�� â�� �������� �߰��� �����̾�!";
				case 2:
					return "�ٽ�: ���̾�!";
				case 3:
					return "�ٽ�: �ʸ� ���� ���� Ư�� �帵ũ��!";
				case 4:
					return "����� �ٽÿ��� ������ ������ ����������.";
				}
			}
		case TENSI_SUMMON:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return "�ٽð� ��ſ��� ���Ḧ �����־���.";
				case 1:
					return "�ٽ�: ģ���� �ʿ���?";
				case 2:
					return "�ٽ�: �������̾�!";
				case 3:
					return "�ٽ�: �̰Ÿ� ����ġ�� �ʾƵ� �ǰ���?";
				case 4:
					return "�ٽð� ����� �ֺ��� ��ȣ���� ��ȯ���� ��ȯ�ߴ�.";
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return "�ٽð� ��ſ��� �������� ��ȯ���� �������´�.";
				case 1:
					return "�ٽ�: �ο��������Ÿ�... ���� �ο���Ұž�!";
				case 2:
					return "�ٽ�: �󸶳� ���������� ���� �;�!";
				case 3:
					return "�ٽ�: �ʹ� ���������� �ƴϾ�?";
				case 4:
					return "�ٽ��� ����� �ü��� ������.";
				}
			}	
		case TENSI_TELE:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return "�ٽð� ����� ������ ��������.";
				case 1:
					return "�ٽ�: ���⺸�� �����Ұž�!";
				case 2:
					return "�ٽ�: �Ѽ� �����°� �?";
				case 3:
					return "�ٽ�: ���� ���ڸ��� ã�Ƴ¾�!";
				case 4:
					return "����� ������ �ϱ׷����� �ִ� �� ������.";
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return "�ٽð� ����� �� �ٸ� ������ �������´�.";
				case 1:
					return "�ٽ�: �� ������ ���� ��Ҿ�!";
				case 2:
					return "�ٽ�: �� �� ��մ� ���� �˷��ٰ�!";
				case 3:
					return "�ٽ�: �����ϳ�, ��ȭ�� �ຼ��?";
				case 4:
					return "����� �þ߰� ���ε��� ������ �޾Ҵ�.";
				}
			}	
		case TENSI_EARTHQUAKE:
			switch(randA(4))
			{
			case 0:
				return "����� ������ �������� ������ �޾Ҵ�.";
			case 1:
				return "�ٽ�: ��������!";
			case 2:
				return "�ٽ�: ī ũ����!";
			case 3:
				return "�ٽ�: �����̴�!";
			case 4:
				return "������ ������ �Ͼ��!";
			}
		case TENSI_MUNYUM:
			switch(randA(4))
			{
			case 0:
				return "����� ���� ���� �ܴ������� ���� ������.";
			case 1:
				return "�ٽ�: �� ������ �Ծ��?";
			case 2:
				return "�ٽ�: õ���� ���̾�!";
			case 3:
				return "�ٽ�: ���� �´� �͵� �� ���ðž�!";
			case 4:
				return "�ٽð� ��ſ��� ���乫���� ���� �־���.";
			}
		case TENSI_BURST:
			switch(randA(2))
			{
			case 0:
				return "�ٽ�: ��!";
			case 1:
				return "�ٽ�: �ָ����� �ʰ� ������!";
			case 2:
				return "�ٽ�: �̰� ���?";
			}
		case TENSI_WEAPON:
			switch(randA(6))
			{
			case 0:
				return "����� �տ� ���� ����� ���̱� �����ߴ�.";
			case 1:
				return "�ٽ�: ���Ⱑ ��ǰ���ݾ�?";
			case 2:
				return "�ٽ�: ���ݸ� �����ִ°ž�!";
			case 3:
				return "�ٽ�: ���� �������Ե� ����������?";
			case 4:
				return "�ٽ�: ���� �����ִ°Ŵϱ� �������� ��������!";
			case 5:
				return "�ٽ�: �� ���������?";
			case 6:
				return "�ٽ�: ��Ű�� ������ ȥ���ϱ�...";
			}
		case TENSI_KANAME:
			if (good_)
			{
				switch (randA(5))
				{
				case 0:
					return "�ٽô� ��ſ��� �������� �����־���.";
				case 1:
					return "�ٽ�: �̰� �ִٸ� ������ �ʰ���?";
				case 2:
					return "�ٽ�: ���� �Ϳ��� �ϴ� �ֵ��̾�!";
				case 3:
					return "�ٽ�: �ֿϿ� ���̶��� ���þ�?";
				case 4:
					return "�ٽ�: ������ �ٷ���!";
				case 5:
					return "�ٽ�: ī���� �ǳ�!";
				}
			}
			else {
				switch (randA(5))
				{
				case 0:
					return "�ٽ�: �ű⼭ �־����°� �����ž�";
				case 1:
					return "�ٽ�: �� ħ���� ���þ�?";
				case 2:
					return "�ٽ�: �� ���� ����� �����ʾ�... ��� ������!";
				case 3:
					return "�ٽ�: ���⼭ ��ư� �� ������ �����غ��߰ھ�!";
				case 4:
					return "�ٽ�: �̹��� ���� ���� ����ī���ε�, ���� �� ���ٷ�?";
				case 5:
					return "�ٽ�: ��ݿ����� �غ���������? ���� �ʰ� ǥ���̾�!";
				}
			}

		}

	}
	return "�ٽô� �ȵ鸮�� ��Ҹ��� �ұٰŷȴ�.";

}