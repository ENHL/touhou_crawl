//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: const.cpp
//
// ����: const����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "const.h"
#include "unit.h"

const char *tribe_type_string[TRI_MAX]=
{
	"�ΰ�",
	"����",
	"����",
	"ī���ٱ�",
	"����ٱ�",
	"ı��",
	"���ڸ�Ÿ",
	"����ǻ���",
	"����𰡹�",
	"����",
	"�ݿ�",
	"����",
	"������",
	"�䱫"
};
const bool tribe_string_back[TRI_MAX]=
{
	true,
	false,
	true,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	true,
	false,
	false
};


const char *job_type_string[JOB_MAX]=
{
	"����",
	"������",
	"����",
	"������",
	"������",
	"������",
	"������",
	"ȭ������",
	"�ñ����",
	"��������",
	"������",
	////"������",
	"��ȯ����",
	//"������",
	//"�������",
	"���ݼ���",
	"�ɸ�����",
	"���",
	"���ŵ�",
	"�ϻ���",
	"���",
	"���̵�",
	"�����",
	"������"
};

const bool job_string_back[JOB_MAX]=
{
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false
};


extern const char *dungeon_tile_tribe_type_string[]=
{
	"�˼�����",
	"����",
	"����",
	"����",
	"",
	"",//5
	"",
	"",
	"",
	"",
	"",//10
	"",
	"",
	"",
	"",
	"������",//15
	"�������� ���",
	"�ö󰡴� ���",
	"��� �������� ���� ���",
	"�Ȱ�ȣ���� ���� ���",
	"�䱫�� ������ ���� ���",
	"ȫ�������� ���� ���",
	"���������� ���� ���",
	"���ϽǷ� ���� ���",
	"�̱��� �׸��� ���� ��",
	"���������� ���� ���",
	"������ ���� ����",	
	"���� ������ ���� ���",
	"���±�� ���ϴ� ��",
	"���� ����� ���� ��Ż",
	"���� ���÷� ���� ��",
	"����� ���� ��Ż",
	"������ �Ż��� ���",
	"�Ա��� ���ư��� ���",
	"��Ű����Ű�� ���� ����",
	"������ ��û� ����",
	"ī������ �л� ����",
	"�������� �̻����� ����",
	"�̳븮���� ǳ�� ����",
	"�̸��� �Ƿ� ����",
	"��Ű�� ���� ����",
	"������� ���³��� ����",
	"�������� ��ǳ ����",
	"������ ��� ����",
	"��ī���� ��Ű�� ����",
	"���̸��� ����",
	"�������� �䱫���� ����",
	"���丮�� ��3�Ǵ� ����",
	"�ٽ��� �伮 ����",
	"",



	"����",//50
	"����",
	"������",
	"å��",
	"�����ȴ볪��",
	"ö��",
	"������",
	"����",
	"����",
	"������",
};

const char *state_string[] = 
{
	"�ƻ�",
	"�ƻ�����",
	"�����",
	"���",
	"", //�� �κ��� ǥ�õ����ʴ´�.
	"��θ�",
	"����",
	"����"
};


const D3DCOLOR CL_normal = D3DCOLOR_RGBA(255, 255, 255, 255);
const D3DCOLOR CL_bad = D3DCOLOR_RGBA(100, 100, 100, 255);
const D3DCOLOR CL_verybad = D3DCOLOR_RGBA(50, 50, 50, 255);
const D3DCOLOR CL_none = D3DCOLOR_RGBA(0, 0, 0, 255);
const D3DCOLOR CL_help = D3DCOLOR_RGBA(125, 200, 255, 255);
const D3DCOLOR CL_good = D3DCOLOR_RGBA(0, 255, 0, 255);
const D3DCOLOR CL_dark_good = D3DCOLOR_RGBA(0, 200, 0, 255);
const D3DCOLOR CL_blue = D3DCOLOR_RGBA(0, 50, 255, 255);
const D3DCOLOR CL_white_blue = D3DCOLOR_RGBA(100, 100, 255, 255);
const D3DCOLOR CL_tensi = D3DCOLOR_RGBA(185, 122, 87, 255);
const D3DCOLOR CL_alchemy = D3DCOLOR_RGBA(255, 128, 39, 255);
const D3DCOLOR CL_green = D3DCOLOR_RGBA(0, 200, 0, 255);
const D3DCOLOR CL_yuigi = D3DCOLOR_RGBA(215, 215, 255, 255);
const D3DCOLOR CL_hina = D3DCOLOR_RGBA(0, 200, 0, 255);
const D3DCOLOR CL_warning = D3DCOLOR_RGBA(255, 255, 0, 255); 
const D3DCOLOR CL_small_danger = D3DCOLOR_RGBA(255, 125, 125, 255); 
const D3DCOLOR CL_danger = D3DCOLOR_RGBA(255, 0, 0, 255); 
const D3DCOLOR CL_STAT = D3DCOLOR_XRGB(200,200,200);
const D3DCOLOR CL_speak = D3DCOLOR_RGBA(255, 255, 255, 255);
const D3DCOLOR CL_magic = D3DCOLOR_RGBA(255, 0, 255, 255);
const D3DCOLOR CL_white_puple = D3DCOLOR_RGBA(255, 128, 255, 255);
const D3DCOLOR CL_yuyuko = D3DCOLOR_RGBA(255, 200, 255, 255);
const D3DCOLOR CL_yukari = D3DCOLOR_RGBA(255, 128, 255, 255);
const D3DCOLOR CL_swako = D3DCOLOR_RGBA(125, 200, 255, 255);
const D3DCOLOR CL_autumn = D3DCOLOR_RGBA(255, 128, 39, 255);


const name_infor string_that("�װ�",true);
const name_infor string_something("����",false);

const char *item_weapon_string = "����";
const char *item_throw_string = "ź��";
const char *item_armor_string = "��";
const char *item_potion_string = "����";
const char *item_food_string = "����";
const char *item_scroll_string = "�η縶��";
const char *item_spell_string = "����ī��";
const char *item_jewelry_string = "��ű�";
const char *item_book_string = "å";
const char *item_miscellaneous_string = "�ߵ�";
const char *item_goal_string = "�߿�";

const int level_up_value[] = {
	10, 
	30,		//20	2
	70,		//40	3
	140,	//70	4
	260,	//120	5
	460,	//200	6
	800,	//340	7
	1400,	//600	8
	2500,	//1100	9
	3700,	//2200	10
	7700,	//4000	11
	15700,	//8000	12
	30000,	//14300	13
	50000,	//20000	14
	75000,	//25000	15
	106000,	//31000	16
	143000,	//37000	17
	186000,	//43000	18
	235000,	//49000	19
	290000,	//55000	20
	351000,	//61000	21
	418000,	//67000	22
	491000,	//73000	23
	570000,	//79000	24
	655000,	//85000	25
	746000,	//91000	26
	-1 //��
};
