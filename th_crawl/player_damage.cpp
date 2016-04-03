//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: player_damage.cpp
//
// 내용: player의 데미지 처리 함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "player.h"
#include "unit.h"
#include "environment.h"
#include "beam.h"
#include "potion.h"
#include "scroll.h"
#include "smoke.h"
#include "skill.h"
#include "ring.h"
#include "save.h"
#include "key.h"
#include "weapon.h"
#include "alchemy.h"
#include "throw.h"


extern HANDLE mutx;
skill_type itemtoskill(item_type type_);



extern bool wizard_mode;





int players::GetAttack(bool max_)
{
	float base_atk_ = s_str/3.0f+ s_dex/6.0f;
	float max_atk_=0, min_atk_=0;
	skill_type skill_ = SKT_MACE;

	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && equipment[ET_WEAPON]->type <= ITM_WEAPON_CLOSE)
	{
		skill_ = itemtoskill(equipment[ET_WEAPON]->type);
		if(skill_>SKT_ERROR)
		{
			max_atk_ = equipment[ET_WEAPON]->value2*(equipment[ET_WEAPON]->value4/15.0f+skill[skill_].level/20.0f+base_atk_/6.0f);
			min_atk_ = min(equipment[ET_WEAPON]->value2,skill[skill_].level/2);
		}
		else //여기는 버그 처리. 데미지가 없으면 버그임을 알수있음
		{
			max_atk_ = 0;
			min_atk_ = 0; 
		}
	}
	else if(!equipment[ET_WEAPON]) //맨손임
	{
		skill_ = SKT_UNWEAPON;
		max_atk_ = base_atk_+skill[skill_].level;
		min_atk_ = 0;
	}
	else
	{
		max_atk_ = base_atk_;
		min_atk_ = 0;
	}
	if(power<=200)
	{ //파워 200이하에서만 파워에 의한 감소를 받는다.
		max_atk_ *= (min(power,500)*0.001f+0.5f);
		min_atk_ *= (min(power,500)*0.001f+0.5f);
	}
	if(s_might || s_lunatic)
		max_atk_+=randA_1(10);	
	
	if(!equipment[ET_WEAPON] && alchemy_buff == ALCT_STONE_FORM)
		max_atk_+=8;

	max_atk_+=dam_plus;
	if(s_slaying)
	{
		max_atk_+=s_slaying;
	}
	
	if(max_atk_<min_atk_)
		max_atk_ = min_atk_;

	int atk_ = rand_int((int)round(min_atk_),(int)round(max_atk_));

	
	if(alchemy_buff == ALCT_STONE_FIST)
	{
		atk_+=randA_1(10);	
	}

	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->value5)//속성브랜드처리
	{
		atk_ = GetPulsDamage((weapon_brand)equipment[ET_WEAPON]->value5,atk_);
	}
	


	//max_atk_*=(1+(skill[skill_].level+skill[SKT_STEALTH].level)*0.1);
	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type == ITM_WEAPON_SHORTBLADE)
	{ //단검 암습 보너스
		max_atk_+=10;
		max_atk_*=(1+(skill[skill_].level+skill[SKT_STEALTH].level)*0.05f);
	}
	else
		max_atk_*=(1+skill[SKT_STEALTH].level*0.05f);
	
	//	max_atk_*=equipment[ET_WEAPON]->GetStabPercent();


	return max_?max_atk_:atk_;
}


int players::GetHit()
{
	int hit_ = 3+s_dex/2+skill[SKT_FIGHT].level/2;
	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && equipment[ET_WEAPON]->type <= ITM_WEAPON_CLOSE)
	{
		skill_type skill_ = itemtoskill(equipment[ET_WEAPON]->type);
		if(skill_>SKT_ERROR)
		{
			hit_ += equipment[ET_WEAPON]->value1 + equipment[ET_WEAPON]->value3 + skill[skill_].level/3;
		}
		else
		{
			hit_ = -99;
		}
	}
	else if(!equipment[ET_WEAPON])
	{
		hit_ += s_dex/4;
	}
	hit_+=acc_plus;
	if(s_slaying)
	{
		hit_+=s_slaying;
	}
	if(s_knife_collect)
	{
		hit_+=5;
	}


	if(as_penalty > GetPenaltyMinus(1))
	{//만약 방어패널티때문에 명중이 내려갈 경우
		hit_ -= as_penalty-GetPenaltyMinus(1); 
	}
	return hit_;
}
int players::GetAtkDelay()
{
	int delay_ = 6;
	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && equipment[ET_WEAPON]->type <= ITM_WEAPON_CLOSE)
	{
		float real_delay_ = max((equipment[ET_WEAPON]->value8) , 
			(equipment[ET_WEAPON]->value7-you.skill[itemtoskill(equipment[ET_WEAPON]->type)].level/2.0f));
		delay_ = real_delay_+rand_float(0.99f,0.0f);
	}
	else if(equipment[ET_WEAPON])
		delay_ = 10;
		
	return delay_;

}

//int players::GetArmourPanlty()
//{
//	if(equipment[ET_ARMOR])
//	{
//		float panlty = -equipment[ET_ARMOR]->value2;
//		panlty -= skill[SKT_ARMOUR].level/2;
//		if(panlty<0)
//			panlty = 0;
//		return (int)panlty;
//	}
//	else
//		return 0;
//}
//int players::GetShieldPanlty()
//{
//	if(equipment[ET_SHIELD])
//	{
//		float panlty = -equipment[ET_SHIELD]->value2;
//		panlty -= skill[SKT_SHIELD].level/3;
//		return (int)panlty;
//	}
//	else
//		return 0;
//}
int players::ReSetASPanlty()
{
	const item* armor_ = equipment[ET_ARMOR], *shield_ = equipment[ET_SHIELD];
	int prev_panlty_ = as_penalty;
	int panlty_ = 0;
	if(armor_)
	{ //아머의 패널티
		int panlty2_ = -armor_->value2;
		panlty2_ -= skill[SKT_ARMOUR].level/3;
		if(panlty2_ < armor_->value3)
			panlty2_ = armor_->value3;
		panlty_ += panlty2_;
	}	
	if(shield_)
	{
		int panlty2_ = -shield_->value2;
		panlty2_ -= skill[SKT_SHIELD].level/3;
		if(panlty2_ < shield_->value3)
			panlty2_ = shield_->value3;
		panlty_ += panlty2_;
	}
	as_penalty = panlty_;
	EvUpDown(prev_panlty_-as_penalty);
	return panlty_;
}
int players::GetPenaltyMinus(int level_)
{
	switch(level_)
	{
	case 1:
		return 2+you.s_str/6;
	case 2:
		return 3+you.s_str/4;
	case 3:
		return 4+you.s_str/3;
	}

	return 0;
}
int players::GetThrowAttack(const item* it, bool max_)
{
	float base_atk_ = 1+s_str/3.0f+s_dex/6.0f;
	float max_atk_=0, min_atk_=0;
	
	
	if(!(it->type>=ITM_THROW_FIRST && it->type<ITM_THROW_LAST))
	{//이것은 장착무기이다..
		max_atk_ = 1+it->value2*(1+base_atk_/10.0f+skill[SKT_TANMAC].level/15.0f+it->value4/10.0f);
	}
	else
	{
		max_atk_ = 1+it->value2*(1+base_atk_/10.0f+skill[SKT_TANMAC].level/15.0f);
	}

	min_atk_ = min(it->value2/2,skill[SKT_TANMAC].level/4);

	if(power <= 200)
	{
		max_atk_ *= (min(power,500)*0.001f+0.5f);
		min_atk_ *= (min(power,500)*0.001f+0.5f);
	}
	if(s_might || s_lunatic)
		max_atk_+=randA_1(10);
	int atk_ = rand_int((int)round(min_atk_),(int)round(max_atk_));
	return max_?(int)round(max_atk_):atk_;
}


int players::GetThrowHit(const item* it)
{
	int hit_ = 3+s_dex/3;	

	hit_ += it->value1 + it->value3 + skill[SKT_TANMAC].level/2;

	return hit_;
}

attack_weapon_type players::GetAttackType()
{
	if(equipment[ET_WEAPON])
	{
		switch(equipment[ET_WEAPON]->type)
		{	
		case ITM_WEAPON_SHORTBLADE:
			return AWT_SHORTBLADE;
		case ITM_WEAPON_LONGBLADE:
			return AWT_LONGBLADE;
		case ITM_WEAPON_MACE:
			return AWT_MACE;
		case ITM_WEAPON_AXE:
			return AWT_AXE;
		case ITM_WEAPON_SPEAR:
			return AWT_SPEAR;
		default:
			return AWT_NONE;
		}
	}
	return AWT_UNARMOUR;
}





int players::calculate_damage(attack_type type_, int atk, int max_atk)
{	
	int damage_ = atk;
	
	int bonus_damage = 0;
	

	switch(type_)
	{
	case ATT_NORMAL:
	case ATT_NOISE:
	case ATT_SPEAR:
	case ATT_FIRE:
	case ATT_COLD:
	case ATT_S_POISON:
	case ATT_VAMP:
	case ATT_THROW_NORMAL:
	case ATT_CLOUD_NORMAL:
	case ATT_VEILING:
	case ATT_RUSH:
	case ATT_WALL:
	case ATT_NORMAL_HIT:	
	case ATT_NORMAL_BLAST:
	case ATT_FIRE_BLAST:
	case ATT_COLD_BLAST: 
	case ATT_THROW_FIRE:
	case ATT_THROW_FREEZING:
	case ATT_THROW_COLD:
	case ATT_THROW_WATER:
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
	default:
		{//데미지 계산공식
			//최종데미지  :  1d(percent_*damage_) - 0d(ac_dec)
			//percent_:1에서 AC15까지 AC1당 0.010. 15부터 AC30까진 0.01,  AC30후부턴 0.005씩 감소(AC15면 0.85 AC30이면 0.625)
			//ac_dec -> 3, 6, 10, 15, 21, 28, 36, 45, 55에서 1씩 증가
			//는 예전 변수고 지금은 (ac+1)/3이 ac_dec가 된다.
			//최종데미지가 0보다 작으면 0이된다.
			float percent_ = 1.0f;
			int ac_dec=0;
			for(int i = ac; i>0; i--)
				percent_ -= (i<=15?0.008f:(i<=30?0.01f:0.005f));/*
			for(int i = 4, j=3 ; j <= ac ; j+=i++)
				ac_dec++;*/
			ac_dec = (ac+1)/3;
			damage_ = (int)round(damage_*percent_) - randA(ac_dec);
			//damage_ = randA_1((int)round(damage_*percent_)) - randA(ac_dec);
			if(damage_<0)
				damage_ = 0;
		}
		break;
	case ATT_CLOUD_FIRE:
	case ATT_CLOUD_COLD:
	case ATT_ELEC:
	case ATT_THROW_ELEC:
	case ATT_THROW_NONE_MASSAGE:
	case ATT_STONE_TRAP:
	case ATT_SMITE:
	case ATT_BURST:
		break;
	}

	
	switch(type_)
	{
	case ATT_FIRE:
		bonus_damage = damage_/3;
		damage_ -= bonus_damage;
		bonus_damage *= GetFireResist();
		break;
	case ATT_COLD:
		bonus_damage = damage_/3;
		damage_ -= bonus_damage;
		bonus_damage *= GetColdResist();
		break;
	}
	damage_ += bonus_damage;


	switch(type_)
	{
	case ATT_THROW_FIRE:
	case ATT_CLOUD_FIRE:
	case ATT_FIRE_BLAST:
		damage_ *= GetFireResist();
		break;
	case ATT_THROW_COLD:
	case ATT_CLOUD_COLD:
	case ATT_THROW_FREEZING:
	case ATT_COLD_BLAST: 
		damage_ *= GetColdResist();
		break;
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
		damage_ *= GetPoisonResist()>0?0.5:(GetPoisonResist()<0?1.5:1);
		break;
	case ATT_ELEC:
	case ATT_THROW_ELEC:
		damage_ *= GetElecResist();
		break;
	}

	if(alchemy_buff == ALCT_STONE_FORM)
		damage_ /= 0.66f;


	return damage_;

}
void players::print_damage_message(attack_infor &a)
{
	name_infor name_;
	if(a.order)
		name_ = (*a.order->GetName());
	switch(a.type)
	{
	case ATT_NORMAL:
	case ATT_SPEAR:
	case ATT_FIRE:
	case ATT_COLD:
	case ATT_S_POISON:
	case ATT_VAMP:
	case ATT_THROW_NORMAL:
	case ATT_THROW_FIRE:
	case ATT_THROW_COLD:
	case ATT_THROW_WATER:
	case ATT_THROW_ELEC:
	case ATT_THROW_FREEZING:
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
	default:
		if(a.order)
		{
			printarray(false,false,false,a.order->isView()?CL_normal:CL_small_danger,6,name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_is(true),name.name.c_str(),"에게 명중했다.");
		}
		break;
	case ATT_NORMAL_HIT:		
		if(a.order)
		{
			printarray(false,false,false,a.order->isView()?CL_normal:CL_small_danger,6,name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_is(true),name.name.c_str(),"에게 들어갔다.");
		}	
		break;
	case ATT_SMITE:
		if(a.order)
		{
			printarray(false,false,false,CL_normal,4,"무엇인가 ",GetName()->name.c_str(),GetName()->name_to(true),"강타했다.");
		}
		break;
	case ATT_NOISE:
		if(a.order)
		{
			printarray(false,false,false,CL_normal,3,"굉음이 ",GetName()->name.c_str(),"의 달팽이관을 강타했다.");
		}
		break;
	case ATT_CLOUD_FIRE:
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"화염에 휩싸였다.");
		break;
	case ATT_CLOUD_COLD:
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"얼어붙었다.");
		break;
	case ATT_STONE_TRAP:
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"뾰족한 바위를 밟았다.");
		break;
	case ATT_NORMAL_BLAST:
	case ATT_FIRE_BLAST:
	case ATT_COLD_BLAST: 
		if(a.order)
		{
			printarray(false,false,false,CL_normal,4,GetName()->name.c_str(),GetName()->name_is(true),a.name.name.c_str(),"의 폭발에 휘말렸다.");
		}
		break;
	case ATT_BURST:
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"폭발했다.");
		break;
	case ATT_CLOUD_NORMAL:
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"바람에 휩쓸렸다.");
		break;
	case ATT_VEILING:
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"바람 갑옷에 베였다.");
		break;		
	case ATT_RUSH:
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"맞았다.");
		break;
	case ATT_WALL:
		if(a.order)
		{
			printarray(false,false,false,CL_normal,5,GetName()->name.c_str(),GetName()->name_is(true),name_.name.c_str(),name_.name_and(true),"부딪혔다.");
		}
		else
		{
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"벽에 부딪혔다.");
		}
		break;
	case ATT_ELEC:
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"감전되었다.");
		break;
	case ATT_THROW_NONE_MASSAGE:
		break;
	}			

}
void players::print_no_damage_message(attack_infor &a)
{
	if(a.order)
	{
		switch(a.type)
		{
		case ATT_THROW_NONE_MASSAGE:	
		case ATT_CLOUD_FIRE:
		case ATT_CLOUD_COLD:
		case ATT_CLOUD_NORMAL:
		case ATT_ELEC:
		case ATT_VEILING:
		case ATT_RUSH:
		case ATT_WALL:
		case ATT_STONE_TRAP:
			break;
		default:
		case ATT_NORMAL_HIT:	
			printlog("아무런 데미지도 받지 않았다.",true,false,false,CL_normal);
			break;
		}
	}
}
bool players::damage(attack_infor &a, bool perfect_)
{
	int damage_ = calculate_damage(a.type,a.damage,a.max_damage);
	int accuracy_ = a.accuracy;
	float evasion = 0.0f;
	float shield_ = 0.0f;
	bool graze_ = false;
	

	if(s_timestep) //완전 무적이 됨
		return false;

	
	if(s_graze && randA(3) == 0)
	{
		if(a.type >= ATT_THROW_NORMAL && a.type < ATT_THROW_LAST)
			graze_ = true;
	}

	if(s_glow)
		accuracy_+=5; //빛날경우 명중 증가
	if(a.order && a.order->GetMindReading())
	{
		accuracy_/=3; //이 대상은 간파한 상대다.
	}


	{//회피률 계산공식
	//최종회피률 :  edit_ev/(edit_ev+accuracy_)
	//edit_ev:1에서 EV15까지 EV1당 0.8. 15부터 AC30까진 1,  AC30후부턴 1.5씩 증가
	//저회피패널터: 만약 accuracy_>edit_ev일경우 최종회피률에서 edit_ev/accuracy_을 곱한다. 단 0.5가 최소치
	//최종값이 0보다적을 경우 0이 된다.
		float edit_ev=0;
		for(int i = ev; i>0; i--)
			edit_ev += (i<=15?0.8f:(i<=30?1:1.5f));
		evasion = edit_ev/(edit_ev+accuracy_);
		if(accuracy_>edit_ev)
			evasion *= max(0.5f,edit_ev/accuracy_);
		if(evasion<0)
			evasion = 0;
		if(evasion>0.95f)
			evasion = 0.95f;
	}

	if(wizard_mode)
	{		
		char temp[50];
		sprintf_s(temp,50,"a-%d A-%d, H-%d hit-%d%%",a.damage,a.max_damage,a.accuracy,(int)(100-evasion*100));
		printlog(temp,true,false,false,CL_danger);
	}
	you.SetInter(IT_DAMAGE);

	{//실드 공식
     //breaking 기본 30
	 //만약 그레이즈가능한 공격일 경우 5을 뺀다.
     // (SH / breaking+SH)의 확률로 가드!
	 //단 실드가 통하지 않는 공격일경우 최종확률이 0이됨(나중에 넣기)
		float breaking = 45;
		if(a.type >= ATT_THROW_NORMAL && a.type < ATT_THROW_LAST)
			breaking -= 5;
		shield_ = (float)sh/(sh+breaking);
		if(a.type >= ATT_NO_GUARD)
			shield_ = 0;
		//볼트형 가드안되게 하려면 어떻게?
	}


	name_infor name_;
	if(a.order)	
		name_ = (*a.order->GetName());
	if((randA(1000)>=evasion*1000 && !graze_ ) || perfect_)
	{	
		if(randA(1000)>shield_*1000 || perfect_)
		{
			print_damage_message(a);
			if(damage_)
			{
				enterlog();
				a.damage = damage_;
				dead_order = &a;
				HpUpDown(-damage_,DR_HITTING);

				dead_order = NULL;
				if(s_mirror && hp>0 && a.order)
				{
					a.order->HpUpDown(-damage_,DR_MIRROR, this);	
					//a.order->damage(attack_infor(randA_1(s_value_veiling),s_value_veiling,99,NULL,GetParentType(),ATT_VEILING,name_infor("베일링",true)), true);
				}
				if(damage_/3 > 0 && a.type == ATT_VAMP && randA(2) == 0)
				{
					if(a.order)
					{
						a.order->HpUpDown(damage_/3,DR_EFFECT);	
						printarray(true,false,false,CL_normal,4,a.name.name.c_str(),a.name.name_is(),  name_.name.c_str(),"의 체력을 흡수했다.");
			
					}
				}
				if(a.type == ATT_S_POISON && randA(1))
					SetPoison(15+randA(10), 50, false);
				if(a.type == ATT_THROW_WEAK_POISON)
					SetPoison(20+randA(10), 50, false);
				if(a.type == ATT_THROW_MIDDLE_POISON)
					SetPoison(40+randA(15), 100, false);
				if(a.type == ATT_THROW_STRONG_POISON)
					SetPoison(70+randA(20), 150, true);
				if(a.type == ATT_THROW_FREEZING)
				{
					int frozen_ = randA_1(10);
					frozen_*=GetColdResist();
					SetFrozen(frozen_);

				}
				//SkillTraining(SKT_ARMOUR,3);
			}
			else
			{
				print_no_damage_message(a);
				//SkillTraining(SKT_ARMOUR,2);
			}
			if(s_veiling && hp>0)
			{
				if(a.order && a.type >=ATT_NORMAL && a.type < ATT_THROW_NORMAL)
				{
					a.order->damage(attack_infor(randA_1(s_value_veiling),s_value_veiling,99,NULL,GetParentType(),ATT_VEILING,name_infor("베일링",true)), true);
					s_veiling = 0;
					s_value_veiling = 0;
				}
			}
		}
		else
		{
			if(a.order)	
			{
				printarray(true,false,false,a.order->isView()?CL_bad:CL_small_danger,7,name.name.c_str(),name.name_is(true),name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_to(true),"방패로 막았다.");
				//SkillTraining(SKT_SHIELD,1);
			}
		}
	}
	else
	{
		if(a.order)
		{
			if(!graze_)
				printarray(true,false,false,a.order->isView()?CL_bad:CL_small_danger,7,name.name.c_str(),name.name_is(true),name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_to(true),"피했다.");
			else 
				printarray(true,false,false,a.order->isView()?CL_normal:CL_small_danger,7,name.name.c_str(),name.name_is(true),name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_to(true),"그레이즈 했다.");

			//if(GetArmourPanlty()<=2)
			//	SkillTraining(SKT_DODGE,3+GetArmourPanlty());
		}
		if(a.order)
		{
			if(!a.order->isView() && you.auto_pickup)
				auto_pick_onoff();
		}
		return false;
	}
	if(a.order)
	{
		if(!a.order->isView() && you.auto_pickup)
			auto_pick_onoff();
	}
	return true;
}