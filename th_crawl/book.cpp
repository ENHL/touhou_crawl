//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: book.cpp
//
// ����: å ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "book.h"
#include "skill_use.h"

book_infor static_book_list[BOOK_LAST]=
{
	book_infor("�ʺ� ȭ�������� ����å",true,BOOK_FIRE_BASE,300,SPL_BURN,SPL_FLAME,SPL_FIRE_WALL,SPL_FIRE_BALL,SPL_FIRE_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� �ñ������ ����å",true,BOOK_COLD_BASE,300,SPL_FROZEN,SPL_FROST,SPL_FREEZE,SPL_ICE_CLOUD,SPL_ICE_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� �������� ����å",true,BOOK_POISON_BASE,300,SPL_STING,SPL_CURE_POISON,SPL_POISON_SKIN,SPL_CONFUSE_CLOUD,SPL_VENOM_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� �������� ����å",true,BOOK_WIZARD_BASE,300,SPL_MAGIC_TANMAC,SPL_BLINK,SPL_DIAMOND_HARDNESS,SPL_SUMMON_OPTION,SPL_CONFUSE_CLOUD,SPL_FIRE_WALL,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� ���������� ����å",true,BOOK_EARTH_BASE,30,SPL_STONE_PUNCH,SPL_STONE_ARROW,SPL_STONE_TRAP,SPL_STONE_UPLIFT,SPL_KANAME_DRILL,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� �������� ����å",true,BOOK_AIR_BASE,300,SPL_SHOCK,SPL_LEVITATION, SPL_TWIST,SPL_DISCHARGE,SPL_CHAIN_LIGHTNING,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� ��ȯ������ ����å",true,BOOK_SUMMON_BASE,300,SPL_SUMMON_MOOK,SPL_SUMMON_OPTION,SPL_SUMMON_BIRD,SPL_SUMMON_GOLEM,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� ���ݼ����� ����å",true,BOOK_ALCHMIST_BASE,300,SPL_STING,SPL_SUMMON_GOLEM,SPL_VENOM_BOLT,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� �ɸ������� ����å",true,BOOK_PSYCHOLOGIST_BASE,300,SPL_HYPNOSIS, SPL_MIND_BENDING, SPL_MUTE, SPL_SELF_INJURY, SPL_CHARM,SPL_NONE ,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� ���������� ����å",true,BOOK_BRAND_BASE,400,SPL_VEILING,SPL_DIAMOND_HARDNESS,SPL_POISON_SKIN,SPL_SILENCE,SPL_HASTE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("���̵��� �⺻�Ҿ�",true,BOOK_MAID_BASE,400,SPL_BLINK,SPL_SUMMON_OPTION,SPL_KNIFE_COLLECT,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("������ ����å",true,BOOK_SHOCK,500,SPL_SHOCK,SPL_LEVITATION,SPL_DISCHARGE,SPL_CHAIN_LIGHTNING,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("���� ������ ����å",true,BOOK_PRACTICE,450,SPL_BURN,SPL_FROZEN,SPL_VEILING,SPL_STONE_PUNCH,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("������ ����å",true,BOOK_SUB,450,SPL_DIAMOND_HARDNESS,SPL_BLINK,SPL_MIND_BENDING,SPL_SUMMON_BIRD,SPL_STONE_TRAP,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ϻ����� ����å",true,BOOK_STALKING,600,SPL_STING,SPL_CONFUSE,SPL_CONFUSE_CLOUD,SPL_INVISIBLE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("������ ����å",true,BOOK_CLOUD,700,SPL_TWIST,SPL_FIRE_WALL,SPL_CONFUSE_CLOUD,SPL_POISON_CLOUD,SPL_ICE_CLOUD,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ı��� ����å",true,BOOK_CONJURE,700,SPL_MAGIC_TANMAC,SPL_SUMMON_OPTION,SPL_LASER,SPL_FIRE_BOLT,SPL_ICE_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("��Ȥ�� ����å",true,BOOK_HEX,400,SPL_GLOW,SPL_MUTE,SPL_CONFUSE,SPL_CHARM,SPL_SILENCE,SPL_INVISIBLE,SPL_NONE,SPL_NONE),
	book_infor("����� ����å",true,BOOK_DEFENSE,600,SPL_VEILING,SPL_DIAMOND_HARDNESS,SPL_CURE_POISON,SPL_DISCHARGE,SPL_SILENCE,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("��ȭ �ּ���",false,BOOK_ENCHANT,700,SPL_DIAMOND_HARDNESS,SPL_FIRE_BALL,SPL_SILENCE,SPL_HASTE,SPL_SUMMON_UFO,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("������ ����å",true,BOOK_TRANSITION,500,SPL_BLINK,SPL_TELEPORT_OTHER,SPL_TELEPORT_SELF,SPL_RECALL,SPL_KNIFE_COLLECT,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("�ٽ��� ������",false,BOOK_TENSI,1000,SPL_STONE_UPLIFT,SPL_KANAME_DRILL,SPL_STONE_FORM,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("�̸��� ���μ�",false,BOOK_TEST_ANNIHILATE,1500,SPL_POISON_CLOUD,SPL_CHAIN_LIGHTNING,SPL_FIRE_BOLT,SPL_ICE_BOLT,SPL_KANAME_DRILL,SPL_SPARK,SPL_NONE,SPL_NONE)
};

string random_book_list[RANDOM_BOOK_NUM]=
{
	"���� Ŀ���� å",
	"�Ķ� Ŀ���� å",
	"��� Ŀ���� å",
	"�ʷ� Ŀ���� å",
	"��ȫ Ŀ���� å",
	"��Ȳ Ŀ���� å",
	"���� Ŀ���� å"
};



book_list SchoolToBook(skill_type skill_)
{
	switch(skill_)
	{
	case SKT_ALCHEMY:
		{
			book_list list_[5] = {BOOK_BRAND_BASE,BOOK_SUB,BOOK_DEFENSE,BOOK_ENCHANT,BOOK_ALCHMIST_BASE};
			return list_[randA(4)];
		}
	case SKT_MENTAL:
		{
			book_list list_[3] = {BOOK_STALKING,BOOK_HEX,BOOK_PSYCHOLOGIST_BASE};
			return list_[randA(2)];
		}
	case SKT_CONJURE:
		{
			book_list list_[4] = {BOOK_FIRE_BASE,BOOK_COLD_BASE,BOOK_CLOUD,BOOK_SHOCK};
			return list_[randA(3)];
		}
	case SKT_FIRE:
		{
			book_list list_[1] = {BOOK_FIRE_BASE};
			return list_[randA(0)];
		}
	case SKT_COLD:
		{
			book_list list_[1] = {BOOK_COLD_BASE};
			return list_[randA(0)];
		}
	case SKT_EARTH:
		{
			book_list list_[2] = {BOOK_EARTH_BASE,BOOK_TENSI};
			return list_[randA(0)];			
		}
	case SKT_AIR:
		{
			book_list list_[3] = {BOOK_AIR_BASE,BOOK_DEFENSE,BOOK_CLOUD};
			return list_[randA(2)];
		}
	case SKT_SUMMON:
		{
			book_list list_[1] = {BOOK_SUMMON_BASE};
			return list_[randA(0)];
		}
	//case SKT_POISON:
	//	{
	//		book_list list_[2] = {BOOK_POISON_BASE,BOOK_CLOUD};
	//		return list_[randA(1)];
	//	}
	//case SKT_ELEC:
	//	{
	//		book_list list_[1] = {BOOK_SHOCK};
	//		return list_[randA(0)];
	//	}
	case SKT_TRANS:
		{
			book_list list_[1] = {BOOK_TRANSITION};
			return list_[randA(0)];
		}
	//case SKT_ALCHEMY:
	//case SKT_WATER:
	default:
		{
			return (book_list)randA(BOOK_LAST-1);
		}
	}
} 
