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
	book_infor("�ʺ� ���ݼ����� ����å",true,BOOK_ALCHMIST_BASE,300,SPL_STONE_PUNCH,SPL_DIAMOND_HARDNESS,SPL_POISON_SKIN,SPL_SUMMON_GOLEM,SPL_VENOM_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� �ɸ������� ����å",true,BOOK_PSYCHOLOGIST_BASE,300,SPL_HYPNOSIS, SPL_MIND_BENDING, SPL_MUTE, SPL_SELF_INJURY, SPL_CHARM,SPL_NONE ,SPL_NONE,SPL_NONE),
	book_infor("�ʺ� ���������� ����å",true,BOOK_BRAND_BASE,400,SPL_VEILING,SPL_DIAMOND_HARDNESS,SPL_POISON_SKIN,SPL_SILENCE,SPL_HASTE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("���̵��� �⺻�Ҿ�",true,BOOK_MAID_BASE,400,SPL_BLINK,SPL_SUMMON_OPTION,SPL_KNIFE_COLLECT,SPL_TIME_PARADOX,SPL_PRIVATE_SQ,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("������ ����å",true,BOOK_SHOCK,500,SPL_SHOCK,SPL_LEVITATION,SPL_DISCHARGE,SPL_CHAIN_LIGHTNING,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("���� ������ ����å",true,BOOK_PRACTICE,450,SPL_BURN,SPL_FROZEN,SPL_VEILING,SPL_STONE_PUNCH,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("������ ����å",true,BOOK_SUB,450,SPL_DRAW_POWER,SPL_DIAMOND_HARDNESS,SPL_BLINK,SPL_MIND_BENDING,SPL_SUMMON_BIRD,SPL_STONE_TRAP,SPL_NONE,SPL_NONE),
	book_infor("�ϻ����� ����å",true,BOOK_STALKING,600,SPL_STING,SPL_CONFUSE,SPL_CONFUSE_CLOUD,SPL_INVISIBLE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("������ ����å",true,BOOK_CLOUD,700,SPL_TWIST,SPL_FIRE_WALL,SPL_CONFUSE_CLOUD,SPL_POISON_CLOUD,SPL_ICE_CLOUD,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ı��� ����å",true,BOOK_CONJURE,700,SPL_MAGIC_TANMAC,SPL_SUMMON_OPTION,SPL_LASER,SPL_FIRE_BOLT,SPL_ICE_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("��Ȥ�� ����å",true,BOOK_HEX,400,SPL_GLOW,SPL_MUTE,SPL_CONFUSE,SPL_CHARM,SPL_SILENCE,SPL_INVISIBLE,SPL_NONE,SPL_NONE),
	book_infor("����� ����å",true,BOOK_DEFENSE,600,SPL_VEILING,SPL_DIAMOND_HARDNESS,SPL_CURE_POISON,SPL_DISCHARGE,SPL_SILENCE,SPL_FIELD_VIOLET,SPL_NONE,SPL_NONE),	
	book_infor("��ȭ �ּ���",false,BOOK_ENCHANT,700,SPL_DRAW_POWER,SPL_DIAMOND_HARDNESS,SPL_FIRE_BALL,SPL_SILENCE,SPL_HASTE,SPL_SUMMON_UFO,SPL_NONE,SPL_NONE),
	book_infor("������ ����å",true,BOOK_TRANSITION,500,SPL_DRAW_POWER,SPL_BLINK,SPL_TELEPORT_OTHER,SPL_TELEPORT_SELF,SPL_RECALL,SPL_KNIFE_COLLECT,SPL_NONE,SPL_NONE),	
	book_infor("�ٽ��� ������",false,BOOK_TENSI,1000,SPL_STONE_UPLIFT,SPL_KANAME_DRILL,SPL_STONE_FORM,SPL_SUMMON_NAMAZ,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("�̸��� ���μ�",false,BOOK_TEST_ANNIHILATE,1500,SPL_LUMINUS_STRIKE,SPL_SPARK,SPL_FIRE_STORM,SPL_PERFERT_FREEZE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("���� ������",true,BOOK_DEBUF,1500,SPL_ANIMAL_CHANGE,SPL_PRIVATE_SQ,SPL_INVISIBLE,SPL_FIELD_VIOLET,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("���̵� ������",false,BOOK_MAID_ULTI,1500,SPL_PRIVATE_SQ,SPL_CONTROLED_BLINK,SPL_THE_WORLD,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�������� ������",false,BOOK_ICE_ULTI,1500,SPL_PRIVATE_SQ,SPL_ICE_BOLT,SPL_ICE_CLOUD,SPL_BLIZZARD,SPL_PERFERT_FREEZE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("�ٸ����� ������",false,BOOK_SUMMON_ULTI,1500,SPL_SUMMON_UFO,SPL_SUMMON_NAMAZ,SPL_DOLLS_WAR,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE)
	
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





const char* GetBookInfor(book_list book_)
{
	switch(book_)
	{
	default:
	case BOOK_CUSTOM_BOOK:
		return "�پ��� ������ ��� �ִ� å.\n�̸��ִ� å�� �ƴ� �� ������ ��︸�� ������ �־�δ�.\n";
	case BOOK_FIRE_BASE:
		return "ȭ���� ���� �������� ������ ��� �ִ� å\nȭ�������� �Թ��ϰ� ���� ��ſ��� ��õ\n";
	case BOOK_COLD_BASE:
		return "�ñ⿡ ���� �������� ������ ��� �ִ� å\n�ñ⸶���� �Թ��ϰ� ���� ��ſ��� ��õ\n";
	case BOOK_POISON_BASE:
		return "���� ���� �������� ������ ��� �ִ� å\n�������� �Թ��ϰ� ���� ��ſ��� ��õ\n";
	case BOOK_WIZARD_BASE:
		return "�پ��ϰ� ������ ���� ������ �������� ��� �ִ� å\n������ ������ ������ ������.\n";
	case BOOK_EARTH_BASE:
		return "������ ���� �������� ������ ��� �ִ� å\n���������� �Թ��ϰ� ���� ��ſ��� ��õ\n";
	case BOOK_AIR_BASE:
		return "��⿡ ���� �������� ������ ��� �ִ� å\n��⸶���� �Թ��ϰ� ���� ��ſ��� ��õ\n";
	case BOOK_SUMMON_BASE:
		return "��ȯ�� ���� �������� ������ ��� �ִ� å\n��ȯ������ �Թ��ϰ� ���� ��ſ��� ��õ\n";
	case BOOK_ALCHMIST_BASE:
		return "���ݼ��� ����ġ�� å\n������ ���ؼ� ������ ���ݼ��� �����غ� �� �ִ� �� ����.\n";
	case BOOK_PSYCHOLOGIST_BASE:
		return "������ �����ϴ� �������� ������ ��� �ִ� å\n�ɸ������� �Թ��ϰ� ���� ��ſ��� ��õ\n";
	case BOOK_BRAND_BASE:
		return "�ʺ� �����縦 ���� ������� ����å\n����鿡�� ������ ������� ������ �Ǿ��ִ�.\n";
	case BOOK_MAID_BASE:
		return "���̵���� �⺻������ �������� �Ҿ��̶�� �����ִ�. ȫ�������� �������̴�.\n���̵��� ���� �ְ� ���ϴ�.\n";
	case BOOK_SHOCK:
		return "�پ��� ���⸶���� �����ִ� ����å\n�����⸸�ص� ¥��¥���ϴ�.\n";
	case BOOK_PRACTICE:
		return "������ ���ҿ����� �� �� �ְ� �Ǿ��ִ� ����å\n������ ���丮���� ���� ���ٰ�!\n";
	case BOOK_SUB:
		return "�پ��� ���������� �����ִ� ����å.\n������ �Թ��� ���ƺ��δ�.\n";
	case BOOK_STALKING:
		return "�����ϻ��ڸ� �޲ٴ� ������� ���� ����å\n������ ������ ���ڶ��δ�.\n";
	case BOOK_CLOUD:
		return "������ ����� ���Ͽ찡 �����ִ� ����å\n���� å�� �����غ��δ�.\n";
	case BOOK_CONJURE:
		return "������ �ı��� ���� ������ �����ִ� å\nź���� �Ŀ�!\n";
	case BOOK_HEX:
		return "���Ÿ����迭�� ������ �����ִ� å\n�䱫���� ���Ű��ݿ� ���ϴٰ�� �Ѵ�.\n";
	case BOOK_DEFENSE:
		return "�پ��� ��� �ֹ��� ����ִ� å\n��Ƴ��� ���� ���� �߿��ϴ�.\n";
	case BOOK_ENCHANT:
		return "�ٽ� ������ �����ִ� ����å\n����� ���õ� ������� �̲��� �ش�.\n";
	case BOOK_TRANSITION:
		return "���̿� ���õ� ������ �����ִ� ����å\n�ð����� �ٷ�� �Ϳ� ū ������ ������.\n";
	case BOOK_TENSI:
		return "�ҷ�õ�� �ٽð� ���� ������ ����å\n�����Ұ��� �׳����� �׳��� ������ �ٷ�� ����� ��︸�ϴ�.\n";
	case BOOK_TEST_ANNIHILATE:
		return "�̸��� ���� �ñ��� �ı�����\n��� �ı����簡 �޲ٰ��ִ� �� å�̴�.\n";
	case BOOK_DEBUF:
		return "�������迡 ����ִ� ���丮�� ���� ������ �����ϴ� ��\n���� å���� ������ ������ �ִ� ���� �����̴�.\n";
	case BOOK_MAID_ULTI:
		return "ȫ������ ���̵����� ������ ���̵带 �淯���� ���� ������ٴ� �� å�̴�.\nȫ������ ������̿ܿ� ������ ���̵尡 �����Ӵ��� �ƹ��� å�� �������� ���߱⿡ �����θ� ������ å�̴�.\n���� �Ӹ��� �ƴ϶� û���ϴ� ��, �����ϴ� ������ �η����� �����ִ�.\n";
	case BOOK_ICE_ULTI:
		return "ȣ���� ����ִ� �� ���� ������ ���� �ڽ��� �ְ��� �����ϱ����� ���� å�̴�.\nå�� �׸�åó�� �׸��� �Բ� ���ұ����� �۾��� ������ �Ǿ��ִ�.\n������ �߻������� ����Ǿ��ֱ⿡ ������ �����ϱ� ��ƴ�. �����Ϸ��� ���� ���ط��� �־�ߵɰͰ���.\n";
	case BOOK_SUMMON_ULTI:
		return "������ ���� ����ִ� �������簡 ���� ���ٴϴ� å�̶�� �Ѵ�.\n�����ϰ� �����ϰ� ����Ǿ��ִ� ���� ������ �ٷ�� ���� ��ȯ������ ������ �� ���� �� ����.\n�����Ե� ����ٷ�� ��, ��븦 �����ϴ� ���� �����ִ�. �� �κ��� ����ô����.\n";
	}
}

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
			book_list list_[4] = {BOOK_STALKING,BOOK_HEX,BOOK_PSYCHOLOGIST_BASE,BOOK_DEBUF};
			return list_[randA(3)];
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
			book_list list_[2] = {BOOK_COLD_BASE,BOOK_ICE_ULTI};
			return list_[randA(1)];
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
			book_list list_[2] = {BOOK_SUMMON_BASE,BOOK_SUMMON_ULTI};
			return list_[randA(1)];
		}
	case SKT_TRANS:
		{
			book_list list_[2] = {BOOK_TRANSITION,BOOK_MAID_ULTI};
			return list_[randA(1)];
		}
	default:
		{
			return (book_list)randA(BOOK_LAST-1);
		}
	}
} 
