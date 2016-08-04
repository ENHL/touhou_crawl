//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: enum.h
//
// 내용: enum관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ENUM_H__
#define  __ENUM_H__


enum game_mode
{
	GM_NORMAL=0,
	GM_TUTORIAL,
	GM_TUTORIAL2,
	GM_SPRINT1_AREANA
};


enum dungeon_level
{
	MAX_YOUKAI_MOUNTAIN_LEVEL=3,
	MAX_MISTY_LAKE_LEVEL=4,
	MAX_SCARLET_LEVEL=3,
	MAX_DUNGEUN_LEVEL = 14,

	MAX_SCARLET_LIBRARY_LEVEL=0,
	MAX_SCARLET_UNDER_LEVEL=0,
	MAX_BAMBOO_LEVEL=0,
	MAX_EIENTEI_LEVEL=0,
	MAX_SUBTERRANEAN_LEVEL=6,

	MAX_YUKKURI_LEVEL=4,
	MAX_DEPTH_LEVEL=4,
	MAX_DREAM_LEVEL=0,
	MAX_MOON_LEVEL=0,
	MAX_PANDEMONIUM_LEVEL=3,
	MAX_HAKUREI_LEVEL=4,


	TEMPLE_LEVEL = MAX_DUNGEUN_LEVEL+1,

	MISTY_LAKE_LEVEL,
	MISTY_LAKE_LAST_LEVEL = MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL,

	YOUKAI_MOUNTAIN_LEVEL,
	YOUKAI_MOUNTAIN_LAST_LEVEL = YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL,

	SCARLET_LEVEL,
	SCARLET_LEVEL_LAST_LEVEL = SCARLET_LEVEL+MAX_SCARLET_LEVEL,	

	SCARLET_LIBRARY_LEVEL,
	SCARLET_LIBRARY_LEVEL_LAST_LEVEL = SCARLET_LIBRARY_LEVEL+MAX_SCARLET_LIBRARY_LEVEL,	
	
	SCARLET_UNDER_LEVEL,
	SCARLET_UNDER_LEVEL_LAST_LEVEL = SCARLET_UNDER_LEVEL+MAX_SCARLET_UNDER_LEVEL,	
	
	BAMBOO_LEVEL,
	BAMBOO_LEVEL_LAST_LEVEL = BAMBOO_LEVEL+MAX_BAMBOO_LEVEL,	

	EIENTEI_LEVEL,
	EIENTEI_LEVEL_LAST_LEVEL = EIENTEI_LEVEL+MAX_EIENTEI_LEVEL,	

	YUKKURI_LEVEL,
	YUKKURI_LAST_LEVEL = YUKKURI_LEVEL+MAX_YUKKURI_LEVEL,

	DEPTH_LEVEL,
	DEPTH_LAST_LEVEL = DEPTH_LEVEL + MAX_DEPTH_LEVEL,
	
	DREAM_LEVEL,
	DREAM_LAST_LEVEL = DREAM_LEVEL + MAX_DREAM_LEVEL,
	
	MOON_LEVEL,
	MOON_LAST_LEVEL = MOON_LEVEL + MAX_MOON_LEVEL,
		
	SUBTERRANEAN_LEVEL,
	SUBTERRANEAN_LEVEL_LAST_LEVEL = SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL,	

	PANDEMONIUM_LEVEL,
	PANDEMONIUM_LAST_LEVEL = PANDEMONIUM_LEVEL + MAX_PANDEMONIUM_LEVEL,

	HAKUREI_LEVEL,
	HAKUREI_LAST_LEVEL = HAKUREI_LEVEL + MAX_HAKUREI_LEVEL,
	MAXLEVEL

};


//출력타입
enum display_type
{
	DT_TEXT=0,
	DT_SKILL,
	DT_STATE,
	DT_GAME,
	DT_ITEM,
	DT_LOG,
	DT_SPELL,
	DT_SKILL_USE,
	DT_SUB_TEXT,
	DT_PROPERTY
};

//스탯
enum stat_type
{
	STAT_STR=0,
	STAT_DEX,
	STAT_INT
};
enum resist_type
{
	RST_POISON = 0,
	RST_FIRE,
	RST_ICE,
	RST_ELEC,
	RST_TYPE_MAX,
	RST_CONFUSE = RST_TYPE_MAX,
	RST_INVISIBLE,
	RST_POWER,
	RST_MAX
};
//아이템목록보기 타입
enum item_view_type
{
	IVT_INFOR,
	IVT_DISCARD,
	IVT_PICK,
	IVT_SELECT,
	IVT_EQ_WEAPON,
	IVT_EQ_ARMOR,
	IVT_UEQ_ARMOR,
	IVT_FOOD,
	IVT_POTION,
	IVT_SCROLL,	
	IVT_EQ_JEWELRY,
	IVT_UEQ_JEWELRY,
	IVT_UNIDEN,
	IVT_THROW,
	IVT_ARMOR,
	IVT_ARMOR_ENCHANT,
	IVT_SPELLCARD,
	IVT_EVOKE,
	IVT_CURSE_ENCHANT
};


//한칸 이동을 위한 상수들
enum short_move
{
	MV_BACK=-1,
	MV_NONE,
	MV_FRONT
};


//길찾기 타입
enum search_type
{
	ST_NORMAL=0,
	ST_SEARCH,
	ST_MONSTER_NORMAL,
	ST_MAP
};


//enum hunger_type
//{
//	HT_STARVING=0,
//	HT_NEARSTARVING,
//	HT_VERYHUNGRY,
//	HT_HUNGRY,
//	HT_NORMAL,
//	HT_FULL,
//	HT_VERYFULL,
//	HT_ENGORGED
//};

//interupt
enum interupt_type //아래로갈수록 인터럽트 우선순위가 증가한다.
{
	IT_NONE = 0,
	IT_HP_RECOVER,
	IT_MP_RECOVER,
	IT_ITEM_PICKUP,
	//IT_HUNGRY,
	IT_MAP_FIND,
	IT_STAT,
	IT_POISON,
	IT_TELE,
	IT_SMOKE,
	IT_MAP_DANGER,
	IT_DAMAGE,
	IT_EVENT
};



//반올림,올림,버림등(경로계산위함)
enum round_type
{
	RT_BEGIN=0,
	RT_FLOOR=0,
	RT_ROUND_DOWN,
	RT_ROUND,
	RT_ROUND_UP,
	RT_CEIL,
	RT_END
};

//던전타일종류
enum dungeon_tile_type //요거 추가했을때 시야에 걸리도록하려면 player.cpp의 resetLOS()에 추가하자
{
	DG_NONE = 0,
    DG_FLOOR,
    DG_FLOOR2,
    DG_GRASS,
    DG_FLOOR_END = DG_GRASS,
	DG_FLOOR_OBJECT = 15,
	DG_OPEN_DOOR = DG_FLOOR_OBJECT, //오브젝트는 바닥+덮어쓰기 식일때
	DG_DOWN_STAIR,
	DG_UP_STAIR,
	DG_SUB_STAIR_FIRST,
	DG_TEMPLE_STAIR = DG_SUB_STAIR_FIRST,
	DG_MISTY_LAKE_STAIR,
	DG_YOUKAI_MOUNTAIN_STAIR,
	DG_SCARLET_STAIR,	
	DG_SCARLET_L_STAIR,
	DG_SCARLET_U_STAIR,
	DG_BAMBOO_STAIR,
	DG_EIENTEI_STAIR,
	DG_SUBTERRANEAN_STAIR,	
	DG_YUKKURI_STAIR,
	DG_DEPTH_STAIR,
	DG_DREAM_STAIR,
	DG_MOON_STAIR,
	DG_PANDEMONIUM_STAIR,
	DG_HAKUREI_STAIR,
	DG_SUB_STAIR_MAX,
	DG_RETURN_STAIR = DG_SUB_STAIR_MAX,
	DG_TEMPLE_FIRST,
	DG_TEMPLE_SHIKIEIKI = DG_TEMPLE_FIRST,
	DG_TEMPLE_BYAKUREN,
	DG_TEMPLE_KANAKO,
	DG_TEMPLE_SUWAKO,
	DG_TEMPLE_MINORIKO,
	DG_TEMPLE_MIMA,
	DG_TEMPLE_SHINKI,
	DG_TEMPLE_YUUGI,
	DG_TEMPLE_SHIZUHA,
	DG_TEMPLE_HINA,
	DG_TEMPLE_YUKARI,
	DG_TEMPLE_EIRIN,
	DG_TEMPLE_YUYUKO,
	DG_TEMPLE_SATORI,
	DG_TEMPLE_TENSI,
	DG_TEMPLE_LAST = DG_TEMPLE_TENSI,
	DG_NONE_MOVE = 50,
	DG_WALL = 50,
	DG_STONE_WALL,
	DG_RED_WALL,
	DG_BOOK_WALL,
	DG_BAMBOO_WALL,
	DG_WALL_END = DG_BAMBOO_WALL,
	DG_METAL_WALL,
	DG_CLOSE_DOOR,
	DG_GLASS,
	DG_STATUE,
	DG_SEA,
	DG_OBJECT_END = DG_SEA,
    MAX_NUM_DG
};

enum dot_tile_type
{
	DOT_FLOOR = 0,
	DOT_WALL,
	DOT_MONSTER,
	DOT_PLAYER,
	DOT_UP,
	DOT_DOWN,
	DOT_ITEM,
	DOT_DOOR,
	DOT_TEMPLE,	
	DOT_SEA
};


enum shadow_type
{
	SWT_MONSTER,
	SWT_ITEM
};

enum smoke_type
{
	SMT_NORMAL = 0,
	SMT_FOG,
	SMT_FIRE,
	SMT_COLD,
	SMT_ELEC,
	SMT_DARK,
	SMT_POISON,
	SMT_CONFUSE,
	SMT_SLOW,
	SMT_TWIST,
	SMT_WHIRLWIND,
	SMT_CURSE,
	SMT_BLIZZARD,
	SMT_MAX
};

enum event_type
{
	EVT_ABOVE=0, //위에 올라서다.
	EVT_SIGHT, //시야에 들어오다.
	EVT_APPROACH_SMALL, //근처에 도착했다. (밀착시)
	EVT_APPROACH_MIDDLE, //근처에 도착했다. (적당히)
	EVT_COUNT, //턴
	EVT_ALWAYS, //항상
	EVT_MAX
};

enum parent_type
{
	PRT_PLAYER,
	PRT_ENEMY,
	PRT_NEUTRAL,
	PRT_ALLY,
	PRT_MAX
};


enum monster_enemy_type
{
	MET_ALL,
	MET_ENEMY,
	MET_ALLY
};


//던전타일의 플래그
enum dungeon_tile_flag
{
	FLAG_INSIGHT = 1<<0, //현재 눈에 보임
    FLAG_EXPLORE = 1<<1, //탐험된 지역
    FLAG_LIGHT = 1<<2, //경로빛(빔같은걸로)
    FLAG_SMOKE = 1<<3, //연기가 있다.
    FLAG_SIGHT_SMOKE = 1<<4, //시야를 가리는 연기
    FLAG_SILENCE = 1<<5, //사일런스범위?
    FLAG_DANGER = 1<<6, //자동탐색을 방해하는 요인이 있는가?
    FLAG_NO_MONSTER = 1<<7, //몬스터리젠금지
    FLAG_NO_ITEM = 1<<8, //아이템리젠금지
    FLAG_MAPPING = 1<<9, //매핑된 지역
    FLAG_NO_STAIR = 1<<10, //계단금지
    FLAG_VIOLET = 1<<11 //필드 바이올렛
};


//던전 사이즈
enum dungeon_size
{
	DG_MAX_Y = 70,
	DG_MAX_X = 80
};

//종족
enum tribe_type
{//인간,마법사,요정,카라스텐구,백랑텐구,캇파,네코마타,반요,츠구모가미,흡혈귀,오니,사신, 달토끼, 천인, 용궁의사자, 유령, 망령, 소령
	TRI_FIRST = 0,
	TRI_HUMAN = 0,
	TRI_WIZARD,
	TRI_FAIRY,
	TRI_CROWTENGU,
	TRI_WOLFTENGU,
	TRI_KAPPA,
	TRI_NECOMATA,
	TRI_OARFISH,
	TRI_CHEUKUMOGAMI,
	TRI_ONI,
	TRI_HALFYOKAI,
	TRI_WRAITH,
	TRI_VAMPIRE,
	TRI_YOKAI, //네임드용이니깐 항상뒤에
	TRI_MAX
};

enum job_type
{
	JOB_FIRST = 0,
	JOB_WARRIOR = 0,
	JOB_WIZARD,
	JOB_SHAMAN,
	JOB_GLADIATOR,
	JOB_MONK,
	JOB_CRUSADER,
	JOB_BERSERKER,
	JOB_FIRE_WIZARD,
	JOB_COLD_WIZARD,
	JOB_EARTH_WIZARD,
	JOB_AIR_WIZARD,
	//JOB_WATER_WIZARD,
	JOB_SUMMON_WIZARD,
	//JOB_POISON_WIZARD,
	//JOB_ELECTRIC_WIZARD,
	JOB_ALCHEMIST,
	JOB_PSYCHOLOGIST,
	JOB_REAPER,
	JOB_FANATIC,
	JOB_ASSASSIN,
	JOB_FARMER,
	JOB_MADE,
	JOB_ENGINEER,
	JOB_MISSING,
	JOB_MAX
};

//몬스터
enum monster_index
{
	MON_REIMUYUKKURI = 0,
	MON_EVENT_REIMUYUKKURI,
	MON_RAT,
	MON_FAIRY_GREEN,
	MON_FAIRY_BLUE,
	MON_FAIRY_RED,
	MON_MOOK,
	MON_EVENT_MOOK,
	MON_CROW,
	MON_CRANE,
	MON_SPIDER,
	MON_SNAKE,
	MON_KATPA,
	MON_KATPA_GUN,
	MON_FAIRY_GREEN_WARRIOR,
	MON_FAIRY_BLUE_MAGICIAN,
	MON_FAIRY_RED_COMMANDER,
	MON_RUMIA,
	MON_MISTIA,
	MON_WRIGGLE,
	MON_CIRNO,
	MON_MEDICINE,
	MON_DIEFAIRY,
	MON_HUMAM_WOMAN,
	MON_HUMAM_MAN,
	MON_HUMAM_YINYANG,
	MON_HUMAM_PRIEST,
	MON_HUMAM_SAMURI,
	MON_FIREFLY,
	MON_BUTTERFLY,
	MON_GHOST,
	MON_BAKEKASA,
	MON_GREEN_MOOK,
	MON_ORANGE_MOOK,
	MON_GRAY_MOOK,
	MON_FROG,
	MON_BLACK_CAT,
	MON_ORANGE_CAT,
	MON_WHITE_CAT,
	MON_CROW_TENGU,
	MON_ONI,
	MON_KISUME,
	MON_CHEN,
	MON_KOGASA,
	MON_SUNNY,
	MON_LUNAR,
	MON_STAR,
	MON_MARISAYUKKURI,
	MON_AYAYUKKURI,
	MON_REMILIAYUKKURI,
	MON_ALICEYUKKURI,
	MON_YOUMUYUKKURI,
	MON_YAMABIKO,
	MON_KATPA_SPEAR,
	MON_KATPA_WATER_WIZARD,
	MON_YAMABUSH_TENGU,
	MON_HANATACA_TENGU,
	MON_BLUE_ONI,
	MON_MUSHROOM,
	MON_KYOUKO,
	MON_FORTUNE_TELLER,
	MON_WOLF_TENGU,
	MON_MOMIZI,
	MON_AYA,
	MON_TEST_KATPA,
	
	MON_WAKASAGI,
	MON_YAMAME,
	MON_NAZRIN,
	MON_DAUZING,
	MON_YOSIKA,
	MON_SEKIBANKI,
	MON_SEKIBANKI_BODY,
	MON_SEKIBANKI_HEAD,
	MON_NITORI,
	MON_KEGERO,
	MON_PARSI,
	MON_BENBEN,
	MON_YATHASI,
	MON_ORIN,
	MON_ORIN_CAT,
	MON_ZOMBIE_FAIRY,
	MON_ICHIRIN,
	MON_UNZAN,
	MON_UNZAN_PUNCH,
	MON_PACHU,
	MON_MAGIC_BOOK,
	MON_HOBGOBRIN,
	MON_HOBGOBRIN_MAID,
	MON_HOBGOBRIN_LIBRARIAN,
	MON_HOBGOBRIN_TEMP,
	MON_MAID_FAIRY,
	MON_CHUPARCABRA,
	MON_KOAKUMA,
	MON_MEIRIN,
	MON_SAKUYA,
	MON_REMILIA,
	MON_EAGLE,
	MON_TIGER,
	MON_RAIJUU,
	MON_DRAGON_BABY,
	MON_KASEN,
	MON_YAMAWARO_NINJA,
	MON_YAMAWARO_WAWRRIOR,
	MON_YAMAWARO_FLAG,
	MON_ONBASIRA,
	MON_RED_UFO,
	MON_GREEN_UFO,
	MON_BLUE_UFO,
	MON_KOISHI, //보이지않는공포
	MON_NUE,
	MON_SANPEI_FIGHTER,
	MON_VAMPIER_BAT,
	MON_DEAGAMA,
	MON_RABBIT,
	MON_YOKAI_RABBIT,
	MON_NAMAZ,
	MON_HELL_CROW,
	MON_RACCON,
	MON_LANTERN_YOUKAI,
	MON_YINYAN, //음양옥
	//마계파티 (유니크가 아니다..)
	MON_YUUGENMAGAN, //유겐마간(전기)
	MON_ELIS, //엘리스(흡혈)
	MON_SARIEL,//사리엘(미정)
	MON_SARA, //사라(미정)
	MON_LUIZE, //루이즈(미정)
	MON_YUKI, //유키(화염)
	MON_MAI, //마이(얼음)
	MON_YUMEKO, //유메코(검)
	MON_MAGICAL_STAR, //매지컬 스타 (웃음)
	MON_GOLEM, //골렘
	MON_EVIL_EYE, //이블아이
	MON_LITTLE_IMP, //마족 자코
	MON_ENSLAVE_GHOST,
	MON_SCHEMA_EYE,
	MON_FLAN,
	MON_FLAN_BUNSIN,
	MON_RABIT_BOMB,
	MON_RABIT_SPEAR,
	MON_RABIT_SUPPORT,
	MON_RABIT_MAGIC,
	MON_TEWI,
	MON_CLOWNPIECE,
	MON_DOREMI,
	MON_FAIRY_HERO,
	MON_FAIRY_SOCERER,
	MON_FAIRY_SUN_FLOWER,
	MON_MOON_RABIT_SUPPORT,
	MON_MOON_RABIT_ATTACK,
	MON_MOON_RABIT_ELITE,
	MON_MAC,
	MON_NIGHTMARE,
	MON_LUNATIC,
	MON_HAUNT,
	MON_FIRE_CAR,
	MON_HELL_SPIDER,
	MON_BLOOD_HAUNT,
	MON_HELL_HOUND,
	MON_DESIRE,
	MON_FLOWER_TANK,
	MON_EVIL_EYE_TANK,
	MON_SNOW_GIRL,
	MON_LETTY,
	MON_YORIHIME,
	MON_TOYOHIME,
	MON_UTSUHO,
	MON_SUIKA,
	MON_REIMU,
	MON_ALICE,
	MON_SEIRAN,
	MON_RINGO,
	MON_UDONGE,
	MON_KAGUYA,
	MON_MOKOU,
	MON_NESI,
	MON_SANGHAI,
	MON_HOURAI,
	MON_FAKE_SANGHAI,
	MON_FAKE_HOURAI,
	MON_TOKIKO,
	MON_MAX,
	MON_MAX_IN_FLOOR = 256
};

enum skill_type //고치면 skill.cpp의 스킬스트링부분추가. player.cpp에서 itemtoskill도 추가
{
	SKT_ERROR = -1,
	SKT_FIGHT = 0,
	SKT_UNWEAPON,
	SKT_SHORTBLADE,
	SKT_LONGBLADE,
	SKT_MACE,
	SKT_AXE,
	SKT_SPEAR,
	//SKT_BOW,
	SKT_TANMAC,
	SKT_DODGE,
	SKT_STEALTH,
	SKT_ARMOUR,
	SKT_SHIELD,
	//SKT_BACKSTAB,
	//SKT_TRAP,
	SKT_SPELLCASTING,
	SKT_FIRE,
	SKT_COLD,
	SKT_EARTH,
	SKT_AIR,
	SKT_CONJURE,
	SKT_ALCHEMY,
	SKT_MENTAL,
	SKT_SUMMON,
	SKT_TRANS,
	SKT_EVOCATE,
	SKT_MAX
};

enum item_type //추가시 env의 isSimpleType 살필것+item_type_simple도 추가하기+ const 스트링도 추가하고+GetItemTypeSting도 추가해야함
{ //GetItemInfor도 추가하자 
	ITM_WEAPON_FIRST = 0,
	ITM_WEAPON_SHORTBLADE=0,
	ITM_WEAPON_LONGBLADE,
	ITM_WEAPON_MACE,
	ITM_WEAPON_AXE,
	ITM_WEAPON_SPEAR,
	ITM_WEAPON_CLOSE = ITM_WEAPON_SPEAR,
	//ITM_WEAPON_BOW,
	ITM_WEAPON_LAST,

	ITM_THROW_FIRST,
	ITM_THROW_TANMAC = ITM_THROW_FIRST,
	ITM_THROW_LAST,

	ITM_ARMOR_FIRST,
	ITM_ARMOR_BODY_FIRST = ITM_ARMOR_FIRST,
	ITM_ARMOR_BODY_ARMOUR_0 = ITM_ARMOR_BODY_FIRST,
	ITM_ARMOR_BODY_ARMOUR_1,
	ITM_ARMOR_BODY_ARMOUR_2,
	ITM_ARMOR_BODY_ARMOUR_3,
	ITM_ARMOR_BODY_LAST,
	ITM_ARMOR_SHIELD = ITM_ARMOR_BODY_LAST,
	ITM_ARMOR_HEAD,
	ITM_ARMOR_CLOAK,
	ITM_ARMOR_GLOVE,
	ITM_ARMOR_BOOT,
	ITM_ARMOR_LAST,

	ITM_POTION,

	ITM_FOOD,

	ITM_SCROLL,

	ITM_SPELL,

	ITM_JEWELRY_FIRST,
	ITM_SPELLCARD = ITM_JEWELRY_FIRST,
	ITM_RING,
	ITM_JEWELRY_LAST,

	ITM_BOOK_FIRST,
	ITM_BOOK,
	ITM_MENUAL,
	ITM_BOOK_LAST,

	ITM_MISCELLANEOUS,
	ITM_GOAL,
	ITM_ORB,
	ITM_SATORI,
	ITM_LAST
};





enum item_type_simple
{
	ITMS_FIRST,
	ITMS_WEAPON = ITMS_FIRST,
	ITMS_THROW,
	ITMS_ARMOR,
	ITMS_POTION,
	ITMS_FOOD,
	ITMS_SCROLL,
	ITMS_SPELL,
	ITMS_JEWELRY,
	ITMS_BOOK,
	ITMS_MISCELLANEOUS,
	ITMS_GOAL,
	ITMS_OTHER,
	ITMS_LAST
};

//장착타입
enum equip_type
{
	ET_FIRST,
	ET_WEAPON = ET_FIRST,
	ET_THROW,
	ET_ARMOR,
	ET_SHIELD,
	ET_HELMET,
	ET_CLOAK,
	ET_GLOVE,
	ET_BOOTS,
	ET_ARMOR_END,
	ET_JEWELRY = ET_ARMOR_END,
	ET_NECK = ET_JEWELRY,
	ET_LEFT,
	ET_RIGHT,
	ET_JEWELRY_END,
	ET_LAST = ET_JEWELRY_END
};


enum potion_type
{
	PT_WATER = 0,
	PT_HEAL,
	PT_POISON,
	PT_HEAL_WOUND,
	PT_MIGHT,
	PT_HASTE,
	PT_CONFUSE,
	PT_SLOW,
	PT_PARALYSIS,
	PT_CLEVER,
	PT_AGILITY,
	PT_MAGIC,
	PT_LEVETATION,
	PT_POWER,
	PT_DOWN_STAT,
	PT_RECOVER_STAT,
	PT_ALCOHOL,
	PT_MAX
};

enum spellcard_evoke_type
{
	SPC_V_FIRE,
	SPC_V_ICE,
	SPC_V_EARTH,
	SPC_V_AIR,
	SPC_V_INVISIBLE,
	SPC_V_MAX
};




enum ring_type
{
	RGT_STR = 0,
	RGT_DEX,
	RGT_INT,
	RGT_HUNGRY,
	RGT_FULL,
	RGT_TELEPORT,
	RGT_POISON_RESIS,
	RGT_FIRE_RESIS,
	RGT_ICE_RESIS,
	RGT_SEE_INVISIBLE,
	RGT_GRAZE,
	RGT_LEVITATION,
	RGT_INVISIBLE,
	RGT_MANA,
	RGT_MAGACIAN,
	RGT_AC,
	RGT_EV,
	RGT_CONFUSE_RESIS,
	RGT_ELEC_RESIS,
	RGT_MAGIC_RESIS,
	RGT_MAX
};

enum amulet_type
{
	//AMT_AC = 0,
	//AMT_EV,
	//AMT_CONFUSE_RESIS,
	//AMT_INACCURACY,
	//AMT_POWER_KEEP,
	AMT_FIRE=0,
	AMT_COLD,
	AMT_LIGHTNING,
	AMT_INVISIBLE,
	AMT_MAX
};

enum book_list
{
	BOOK_CUSTOM_BOOK=-2,
	BOOK_FIRST=0,
	BOOK_FIRE_BASE=BOOK_FIRST,
	BOOK_COLD_BASE,
	BOOK_POISON_BASE,
	BOOK_WIZARD_BASE,
	BOOK_EARTH_BASE,
	BOOK_AIR_BASE,
	BOOK_SUMMON_BASE,
	BOOK_ALCHMIST_BASE,
	BOOK_PSYCHOLOGIST_BASE,
	BOOK_BRAND_BASE,
	BOOK_MAID_BASE,
	BOOK_SHOCK,
	BOOK_PRACTICE,
	BOOK_SUB,
	BOOK_STALKING,
	BOOK_CLOUD,
	BOOK_CONJURE,
	BOOK_HEX,
	BOOK_DEFENSE,
	BOOK_ENCHANT,
	BOOK_TRANSITION,
	BOOK_TENSI,
	BOOK_TEST_ANNIHILATE,
	BOOK_DEBUF,
	BOOK_MAID_ULTI,
	BOOK_ICE_ULTI,
	BOOK_SUMMON_ULTI,
	BOOK_LAST
};

enum tanmac_type
{
	TMT_BILL = 0,
	TMT_AMULET,
	TMT_POISON_NEEDLE,
	TMT_KIKU_COMPRESSER,
	TMT_MAX
};



enum damage_reason
{
	DR_NONE,
	DR_HITTING,
	DR_POTION,
	DR_POISON,
	DR_QUIT,
	DR_EFFECT,
	DR_ESCAPE,
	DR_HUNGRY,
	DR_MIRROR
};


//서치타입
enum view_type
{
	VT_NORMAL = 0,
	VT_THROW,
	VT_BLINK,
	VT_DEBUF,
	VT_SATORI,
	VT_MAX
};

//공격타입
enum attack_type //추가시 monster와 player의 데미지 메세지(print_no_damage_message같은거)를 고쳐야함. 
{ //찾아보면 또 추가할거 있을듯
	ATT_NONE = -1,
	ATT_NORMAL=0,
	ATT_SPEAR,
	ATT_SMITE,
	ATT_BLOOD,
	ATT_NOISE,
	ATT_FIRE,
	ATT_COLD,
	ATT_ELEC,
	ATT_S_POISON,
	ATT_M_POISON,
	ATT_SICK,
	ATT_CURSE,
	ATT_WEATHER,
	ATT_AUTUMN,
	ATT_CHOAS,
	ATT_VAMP,
	ATT_THROW_NORMAL, //여기부터 그레이즈가 됨
	ATT_THROW_NONE_MASSAGE,
	ATT_THROW_FIRE,
	ATT_THROW_COLD,
	ATT_THROW_WATER,
	ATT_THROW_WEAK_POISON,
	ATT_THROW_MIDDLE_POISON,
	ATT_THROW_STRONG_POISON,
	ATT_THROW_LAST, //사용안함. 그레이즈가 되는 공격들
	ATT_THROW_ELEC, //그레이즈는 안 되는데 가드는 된다.
	ATT_NO_GUARD,//여기부터 폭발형(실드로 가드가 안된다.)
	ATT_CLOUD_FIRE = ATT_NO_GUARD, 
	ATT_CLOUD_COLD,
	ATT_CLOUD_ELEC,
	ATT_CLOUD_NORMAL,
	ATT_CLOUD_CURSE,
	ATT_NORMAL_BLAST, 
	ATT_AC_REDUCE_BLAST, 
	ATT_FIRE_BLAST, 
	ATT_COLD_BLAST, 
	ATT_ELEC_BLAST, 
	ATT_POISON_BLAST,
	ATT_FIRE_PYSICAL_BLAST, 
	ATT_COLD_PYSICAL_BLAST, 
	ATT_THROW_FREEZING,
	ATT_BURST, 
	ATT_VEILING,
	ATT_RUSH, //카나코 돌진?
	ATT_WALL, //벽에 부딪히다.
	ATT_STONE_TRAP, //벽에 부딪히다.
	ATT_NORMAL_HIT,
	ATT_MAX
};

//빔타입
enum beam_type
{
	BMT_NORMAL = 0,
	BMT_PENETRATE,
	BMT_WALL, //벽에 부딪히는 빔
	BMT_MAX
};

//몬스터상태
enum monster_state
{
	MS_ERROR=0,
	MS_NORMAL,
	MS_SLEEP,
	MS_ATACK,
	MS_REST,
	MS_FOLLOW
};

enum monster_state_simple //표시용 상태
{
	MSS_NONE=0,
	MSS_SLEEP,
	MSS_WANDERING,
	MSS_NO_NOTICE,
	MSS_CONFUSE,
	MSS_POISON,
	MSS_SCARY,
	MSS_MIGHT,
	MSS_HASTE,
	MSS_SLOW,
	MSS_SMOKE_ABOVE,
	MSS_SUMMON,
	MSS_FROZEN,
	MSS_ALLY,
	MSS_ELEC,
	MSS_PARALYSE,
	MSS_GLOW,
	MSS_GRAZE,
	MSS_SILENCE,
	MSS_SICK,
	MSS_VEILING,
	MSS_INVISIVLE,
	MSS_TELE,
	MSS_MUTE,
	MSS_CATCH,
	MSS_GHOST,
	MSS_FEAR,
	MSS_MIND_READING,
	MSS_LUNATIC,
	MSS_COMMUNICATION,
	MSS_MAX
};

enum attack_weapon_type
{
	AWT_NONE=0,
	AWT_UNARMOUR,
	AWT_SHORTBLADE,
	AWT_LONGBLADE,
	AWT_MACE,
	AWT_AXE,
	AWT_SPEAR
};

//몬스터 상태전이를 일으키는 입력
enum monster_state_input
{
	MSI_NORMAL=0, //일반 상태(사용안함?)
	MSI_FOUND, //플레이어를 발견
	MSI_LOST,//플레이어를 잃어버림
	MSI_ATACKED, //공격받음
	MSI_NOISE, //소음
	MSI_REST,//휴식
	MSI_WAKE//깸
};

enum monster_speak_type
{
	MST_NORMAL=0,
	MST_FOUND,
	MST_MAGIC,
	MST_CONFUSE
};

enum god_type
{
	GT_ERROR=-2,
	GT_NONE=-1,
	GT_FIRST=0,
	GT_SHIKIEIKI = GT_FIRST,
	GT_BYAKUREN,
	GT_KANAKO,
	GT_SUWAKO,
	GT_MINORIKO,
	GT_MIMA,
	GT_SHINKI,
	GT_YUUGI,
	GT_SHIZUHA,
	GT_HINA,
	GT_YUKARI,
	GT_EIRIN,
	GT_YUYUKO,
	GT_SATORI,
	GT_TENSI,
	GT_LAST
};

enum rune_kind
{
	RUNE_SCARLET,
	RUNE_YOUKAI_MOUNTAIN,
	RUNE_SCARLET_UNDER,
	RUNE_YUKKURI,
	RUNE_EIENTEI,
	RUNE_SUBTERRANEAN,
	RUNE_MOON,
	RUNE_PANDEMONIUM_ICE,
	RUNE_PANDEMONIUM_MAGIC,
	RUNE_PANDEMONIUM_SHINKI,
	RUNE_HAKUREI_ORB,
	RUNE_MAX
};


#endif // __ENUM_H__