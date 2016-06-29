
#include "d3dUtility.h"
#include "environment.h"
#include "display.h"
#include "key.h"
#include "save.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"
#include "map.h"
#include "dump.h"
#include "god.h"
#include "throw.h"
#include "skill_use.h"
#include "note.h"
#include "tribe.h"
#include "network.h"


extern bool saveexit;

extern HANDLE mutx;


extern const char *version_string;
typedef struct menu_input
{
	int input;
	int output;
	string text;
	bool infor;
	bool (*f)(int); 
	int value;
	menu_input(int input_, int output_, string text_, bool infor_, bool (*f_)(int), int value_)
		:input(input_), output(output_), text(text_), infor(infor_),f(f_),value(value_){}
}menu_input;

class menu
{
	int id; //아이디
	string text;

	list<menu_input> input_list;
	
public:
	menu::menu(int id_, string text_):id(id_),text(text_){}

	
	void input_puls(int input_, int output_, string text_, bool infor_, bool (*f_)(int), int value_)
	{
		input_list.push_back(menu_input(input_, output_, text_, infor_, f_, value_));
	}
	int GetId(){return id;};

	void View()
	{
		WaitForSingleObject(mutx, INFINITE);
		SetText() = text;
		ReleaseMutex(mutx);
	}

	int Check(int input_, bool double_)
	{		
		for(list<menu_input>::iterator it = input_list.begin(); it != input_list.end(); it++)
		{			
			if((*it).input == input_)
			{
				if(double_)
				{
					if((*it).f && (*it).f((*it).value))
						return -2;
					return (*it).output;
				}
				if((*it).text.length() > 0)
				{
					WaitForSingleObject(mutx, INFINITE);
					SetText() += (*it).text;
					ReleaseMutex(mutx);
					if((*it).infor)
					{
						return -1;
					}
					else
					{						
						Sleep(300);
						if((*it).f && (*it).f((*it).value))
							return -2;
						return (*it).output;
					}
				}
				else
				{
					if((*it).f && (*it).f((*it).value))
						return -2;
					return (*it).output;
				}
			}
		}
		return -1;
	}
};
class menu_manager
{


	list<menu*> menu_list; 

	
public:
	menu_manager::~menu_manager()
	{
		for(list<menu*>::iterator it = menu_list.begin(); it != menu_list.end(); it++)
			delete(*it);
	}


	void menu_puls(int id_, string text_)
	{
		menu_list.push_back(new menu(id_,text_));
	}


	void menu_input_puls(int id_,int input_, int output_, string text_, bool infor_, bool (*f_)(int), int value_)
	{
		for(list<menu*>::iterator it = menu_list.begin(); it != menu_list.end(); it++)
		{
			if((*it)->GetId() == id_)
			{
				(*it)->input_puls(input_, output_, text_, infor_, f_, value_);
				return;
			}
		}
	}

	void loop(int first_id)
	{
		int current_id = first_id;

		while(current_id != -2)
		{
			for(list<menu*>::iterator it = menu_list.begin(); it != menu_list.end(); it++)
			{
				if((*it)->GetId() == current_id)
				{
					int prev_input_ = -1;						
					int output_ = -1;
					(*it)->View();
					while(1)
					{
						int input_ = waitkeyinput();
						(*it)->View();
						if(input_ == VK_RETURN && prev_input_ != -1)
							output_= (*it)->Check(prev_input_, true);
						else
							output_= (*it)->Check(input_, prev_input_ == input_);
						if(output_ != -1)
						{
							break;
						}
						prev_input_ = input_;
					}
					current_id = output_;
					break;					
				}
			}
		}
	}

};


bool checkSavefile(int value_)
{
	if(load_data(save_file.c_str()))
	{		
		saveexit = true;
		return true;
	}
	return false;
}

bool tutorials(int value_)
{
	map_list.tutorial = GM_TUTORIAL;
	you.image = &img_play_sanae;
	you.char_name.name = "사나에";
	you.tribe = TRI_HUMAN;
	you.job = JOB_SHAMAN;
	SetTribe(you.tribe);
	you.CalcuHP();
	env[current_level].EnterMap(0,deque<monster*>());	
	printlog("카나코는 말했다 : 환영한다, 사나에! 이번 튜토리얼은 내가 담당하지.",true,false,false,CL_warning);
	printlog("카나코는 말했다 : 지나간 말은 컨트롤+P로 로그를 확인하고 궁금한건 ?를 눌러.",true,false,false,CL_warning);
	printlog("카나코는 말했다 : 일단 h j k l나 방향키로 움직일 수 있어. 대소문자에 조심해.",true,false,false,CL_warning);
	return true;
}


bool tutorial2(int value_)
{
	map_list.tutorial = GM_TUTORIAL2;
	you.image = &img_play_sanae;
	you.char_name.name = "사나에";
	you.tribe = TRI_HUMAN;
	you.job = JOB_SHAMAN;
	SetTribe(you.tribe);
	you.CalcuHP();
	env[current_level].EnterMap(0,deque<monster*>());	
	printlog("안녕하세요. Dungeon Crawl Stone Soup (이하 돌죽) 팬게임 동방크롤입니다.",true,false,false,CL_warning);
	printlog("여기에선 돌죽 경험자분을 위한 튜토리얼입니다.",true,false,false,CL_warning);
	return true;
}


bool sprint1s(int value_)
{
	map_list.tutorial = GM_SPRINT1_AREANA;
	you.image = &img_play_sanae;
	you.char_name.name = "사나에";
	you.tribe = TRI_HUMAN;
	you.job = JOB_SHAMAN;
	SetTribe(you.tribe);
	you.CalcuHP();
	env[current_level].EnterMap(0,deque<monster*>());	
	
	item_infor t;
	item *it;
	it = env[current_level].MakeItem(you.position,makeitem(ITM_RING,1,&t,RGT_SEE_INVISIBLE));	
	it->Identify();
	you.additem(it,false);
	you.equip('a',ET_LEFT,false);
	env[current_level].DeleteItem(it);

	printlog("아레나에 온걸 환영한다! 승리할 것 같은 팀의 방향에 서있어라!",true,false,false,CL_help);
	printlog("만약 승자를 맞추게되면 레벨이 1 오른다. 틀리면 게임 오버! 기회는 3번...",true,false,false,CL_help);
	return true;
}

bool select_named(int value_)
{
	switch( value_ )
	{
	case 0:						
	default:
		you.tribe = TRI_HUMAN;
		you.job = JOB_SHAMAN;
		you.char_name.name = "레이무";
		you.char_name.name_type = false;
		you.image = &img_play_reimu;
		break;
	case 1:
		you.tribe = TRI_HUMAN;
		you.job = JOB_WIZARD;
		you.char_name.name = "마리사";
		you.char_name.name_type = false;
		you.image = &img_play_marisa;
		break;
	case 2:
		you.tribe = TRI_HUMAN;
		you.job = JOB_SHAMAN;
		you.char_name.name = "사나에";
		you.char_name.name_type = false;
		you.image = &img_play_sanae;
		break;
	case 3:
		you.tribe = TRI_WOLFTENGU;
		you.job = JOB_WARRIOR;
		you.char_name.name = "모미지";
		you.char_name.name_type = false;
		you.image = &img_play_momizi;
		break;
	case 4:
		you.tribe = TRI_YOKAI;
		you.job = JOB_ASSASSIN;
		you.char_name.name = "코이시";
		you.char_name.name_type = false;
		you.image = &img_named_koishi;
		break;
	case 5:
		you.tribe = TRI_HUMAN;
		you.job = JOB_MONK;
		you.char_name.name = "모코우";
		you.char_name.name_type = false;
		you.image = &img_play_mokou[0];
		break;
	}						
	WaitForSingleObject(mutx, INFINITE);
	SetText() += "\n\n\nKill Them All!\n";
	ReleaseMutex(mutx);
	Sleep(300);
	return true;
}
bool select_char(int value_)
{
	you.tribe = (tribe_type)(value_);
	return false;
}
bool select_job(int value_)
{
	you.job = (job_type)(value_);
	you.image = &img_play_normal;
	you.char_name.name = "";
	return true;
}

void start_mainmenu()
{
	menu_manager m_mgr;
	string temp;
	
	temp = "메인 게임\n\n";
	temp += "a - 게임시작\n";
	temp += "b - 튜토리얼(초심자)\n";
	temp += "c - 튜토리얼(돌죽경험자용, 임시)\n";	
	temp += "\n\n미니 게임\n\n";
	temp += "d - 아레나";
	m_mgr.menu_puls(0,temp);
	m_mgr.menu_input_puls(0,'a',1,"",false,checkSavefile,0);
	m_mgr.menu_input_puls(0,'b',0,"",false,tutorials,0);
	m_mgr.menu_input_puls(0,'c',0,"",false,tutorial2,0);
	m_mgr.menu_input_puls(0,'d',0,"",false,sprint1s,0);
	

	temp = "무슨 모드로 시작할거야?\n\n\n";
	temp += "a - 동방 캐릭터로 시작하기 (EASY)\n\n";
	temp += "b - 직접 캐릭터 생성하기 (NORMAL)\n\n";
	m_mgr.menu_puls(1,temp);
	m_mgr.menu_input_puls(1,'a',2,"제일 좋은 것을 부탁해.\n",false,NULL,0);
	m_mgr.menu_input_puls(1,'b',3,"괜찮다. 문제없어.\n",false,NULL,0);
	m_mgr.menu_input_puls(1,VK_ESCAPE,0,"",false,NULL,0);

	
	temp = "캐릭터를 선택합니다. (모든 동방 캐릭터는 레벨3부터 시작합니다)\n\n\n\n";
	temp += "a - 인간 무녀 레이무             e - 요괴 암살자 코이시\n\n";
	temp += "b - 인간 마법사 마리사           f - 인간 격투가 모코우\n\n";
	temp += "c - 인간 무녀 사나에\n\n";
	temp += "d - 백랑텐구 전사 모미지\n\n";	
	temp += "\n\n";	
	m_mgr.menu_puls(2,temp);
	temp = " : 안티패턴 초 유도형. 비겁한 호밍무녀로 모든 적을 섬멸하자!\n";
	temp += " 적성보너스) 탄막적성 +3, 회피적성 +3\n";
	temp += " 보너스) 리본, 24개의 호밍아뮬렛, 신은 믿고 시작하지않는다.\n\n";
	temp += " 초보자팁) f로 부적을 발사할 수 있습니다. 꼭 근접하기전에 부적을 먼저 던집시다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(2,'a',2,temp,true,select_named,0);
	temp = " : 무한관통 & 상시공격형. 탄막은 파워! 보이자마자 죽이자!\n";
	temp += " 적성보너스) 주문시전적성 +2, 파괴마법적성 +3, 회피적성 +1\n";
	temp += " 보너스) +2,+2 빗자루, 영력의 반지, 파괴의 마법책\n\n";
	temp += " 초보자팁) z키로 마법을 쓰고 M키로 마법을 배웁니다. 항상 5키로 마나를 가득 채우고 다닙시다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(2,'b',2,temp,true,select_named,1);
	temp = " : 고위력 & 광범위 작렬형. 스와코님의 말씀대로!\n";
	temp += " 적성보너스) 전투적성 +2, 회피적성 +1, 발동적성 +3\n";
	temp += " 보너스)  대지의 스펠카드(9), 대기의 스펠카드(9), 스와코를 믿고 시작한다.\n\n";
	temp += " 초보자팁) V로 스펠카드가 사용가능합니다. 대지의 스펠카드는 벽에 맞춰서 폭발데미지를 줍시다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(2,'c',2,temp,true,select_named,2);
	temp = " : 자동탐색 & 자동공격형. O와 TAB이 당신을 지켜줄지어니\n";
	temp += " 적성보너스) 장검적성 +1\n";
	temp += " 보너스) +2,+2 언월도, +2 철방패, +2 중간 중갑옷, 상처치료물약 2개, 힘물약 2개, 투명감지 반지\n\n";	
	temp += " 초보자팁) tab은 자동공격, o는 자동탐색으로 편하게 진행 가능합니다. 위기엔 q로 포션을 마시세요.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(2,'d',2,temp,true,select_named,3);
	temp = " : 본포! 당신의 뒤에 있어요. 무의식의 힘으로 모두 암살해라!\n";
	temp += " 적성보너스) 단검적성 +2, 정신마법정석 +2\n";
	temp += " 보너스) 영구투명특성, 파워보존특성\n\n";
	temp += " 초보자팁) 전투중이 아닐땐 항상 투명이 된 상태입니다. 조심하세요! 전투중에는 투명이 풀립니다.\n";
	temp += " 자고있는 상대를 찌르면 암습과 단검스킬에 비례해서 치명적인 큰 데미지가 들어갑니다.\n";	
	temp += " x를 누른 상태에서 몬스터위에 커서를 두고 v를 누르면 정보가 뜹니다. 투명보기가 있는지 확인하세요!\n\n\n";	
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(2,'e',2,temp,true,select_named,4);
	temp = " : 격열! 인간 인페르노. 죽어도 살아나서 돌파하라!\n";
	temp += " 적성보너스) 전투적성 +2, 화염마법정석 +2\n";
	temp += " 보너스) 2번까지 부활가능(9레벨, 18레벨에 다다르면 삭제)\n\n";
	temp += " 초보자팁) 죽어도 2번에 한해서 부활이 가능합니다. 부활할때 체력과 영력이 회복되고 폭발합니다.\n";
	temp += " 죽지않고 9레벨, 18레벨에 다다르면 부활능력이 1개씩 사라집니다. 그러니 죽는 것에 두려워하지마세요!\n\n\n";	
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(2,'f',2,temp,true,select_named,5);
	m_mgr.menu_input_puls(2,VK_ESCAPE,1,"",false,NULL,0);

	
	temp = "종족을 선택합니다.\n\n\n";
	for(int i=0;i<TRI_MAX-1;i++)
	{
		char tempchar[64];
		sprintf_s(tempchar,"%c - %s",'a'+i,tribe_type_string[i]);
		int remain_num_ = 23-strlen(tempchar);
		temp += tempchar;
		if(i%2 ==0)
		{
			for(int j=0;j<remain_num_;j++)
				temp += " ";
		}
		if(i%2 == 1 || i == TRI_MAX-2)
		{
			temp += "\n";
		}
	}
	temp += "\n\n\n";
	m_mgr.menu_puls(3,temp);
	temp = "인간: 평범한 스탯과 평범한 적성. 레벨업이 빠르다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'a',4,temp,true,select_char,0);
	temp = "마법사: 종족으로서의 마법사. 근접전투에 약하고 마법을 잘 다룬다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'b',4,temp,true,select_char,1);
	temp = "요정: 원소마법을 잘다루지만 매우 연약하고 몸집이 작아서 갑옷을 입지 못한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'c',4,temp,true,select_char,2);
	temp = "카라스텐구: 비행이 가능. 괜찮은 전투능력과 좋은 대기마법 적성을 가졌다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'d',4,temp,true,select_char,3);
	temp = "백랑텐구: 높은 근접 전투 적성을 가졌다. 마법은 잘 못 다룬다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'e',4,temp,true,select_char,4);
	temp = "캇파: 높은 창스킬 숙련도를 가지고있으며 수영이 가능하다.\n";
	temp += "불과 대지마법을 제외한 괜찮은 마법 적성을 가졌다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'f',4,temp,true,select_char,5);
	temp = "츠구모가미: 미구현이야!\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'g',4,temp,true,select_char,6);
	temp = "오니: 높은 전투력을 가지고있으나 무기와 마법은 잘 다루지 못한다.\n";
	temp += "몸집이 커서 갑옷을 못입지만 체력이 많고 뿔이 달려서 추가데미지를 준다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'h',4,temp,true,select_char,7);
	temp = "반요: 미구현이야!\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'i',4,temp,true,select_char,8);
	temp = "망령: 냉기저항과 독저항을 들고 시작하고 높은 은신치를 가졌다.\n";
	temp += "대신에 낮은 전투력과 신발을 낄 수 없게 된다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'j',4,temp,true,select_char,9);
	temp = "뱀파이어: 미구현이야!\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(3,'k',4,temp,true,select_char,10);
	m_mgr.menu_input_puls(3,VK_ESCAPE,2,"",false,NULL,0);

	
	temp = "직업을 선택합니다.\n\n\n";
	for(int i=0;i<JOB_MAX;i++)
	{
		char tempchar[64];
		sprintf_s(tempchar,"%c - %s",'a'+i,job_type_string[i]);
		int remain_num_ = 23-strlen(tempchar);
		temp += tempchar;
		if(i%2 ==0)
		{
			for(int j=0;j<remain_num_;j++)
				temp += " ";
		}
		if(i%2 == 1 || i == JOB_MAX-1)
		{
			temp += "\n";
		}
	}
	temp += "\n\n\n";
	m_mgr.menu_puls(4,temp);
	temp = "전사: 전형적인 근접 전투를 선호하는 중갑 전사\n";
	temp += "선택한 무기와 무거운 방패, 갑옷을 끼고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'a',5,temp,true,select_job,0);
	temp = "마법사: 다양한 상황에서 응용할 수 있는 마법을 골고루 사용한다.\n";
	temp += "초보 마법사의 책을 들고 마법의 탄막을 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'b',5,temp,true,select_job,1);
	temp = "무녀: 카나코의 무녀로 카나코의 힘을 사용하여 전투하는 근접전투 직업이다.\n";
	temp += "무기로는 고헤이(둔기)를 들며 무녀복과 카나코를 믿고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'c',5,temp,true,select_job,2);
	temp = "검투사: 원거리와 근접을 골고루 챙기는 하이브리드 회피형전사.\n";
	temp += "선택한 무기와 몇개의 탄막, 그리고 작은 방패를 들고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'d',5,temp,true,select_job,3);
	temp = "격투가: 맨손격투에 재능이 있는 격투가.\n";
	temp += "맨손격투스킬을 높게 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'e',5,temp,true,select_job,4);
	temp = "마전사: 마법과 근접전투를 둘다 챙기는 버프에 능한 마법전사.\n";
	temp += "선택한 무기와 초보 마전사의 책과 베일링을 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'f',5,temp,true,select_job,5);
	temp = "광전사: 극단적인 스탯으로 매우 공격적인 장비를 들고 시작한다.\n";
	temp = "도끼와 로브를끼고있으며 힘물약2개를 들고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'g',5,temp,true,select_job,6);
	temp = "화염술사: 화염을 다루는 화염마법을 배우고 시작하는 원소마법사.\n";
	temp += "초보 화염술사의 책을 들고 불꽃을 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'h',5,temp,true,select_job,7);
	temp = "냉기술사: 냉기를 다루는 냉기마법을 배우고 시작하는 원소마법사.\n";
	temp += "초보 냉기술사의 책을 들고 냉기를 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'i',5,temp,true,select_job,8);
	temp = "대지술사: 대지를 다루는 대지마법을 배우고 시작하는 원소마법사.\n";
	temp += "초보 대지술사의 책을 들고 돌주먹을 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'j',5,temp,true,select_job,9);
	temp = "대기술사: 대기와 전기를 다루는 대기마법을 배우고 시작하는 원소마법사.\n";
	temp += "초보 대기술사의 책을 들고 전격을 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'k',5,temp,true,select_job,10);
	temp = "소환술사: 소환수를 다루는 소환마법을 배우고 시작하는 마법사.\n";
	temp += "초보 소환술사의 책을 들고 모옥 소환을 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'l',5,temp,true,select_job,11);
	temp = "전이술사: 탄막과 전이마법을 사용하는 마법사.\n";
	temp += "전이의 마법책과 몇개의 탄막을 들고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'m',5,temp,true,select_job,12);
	temp = "연금술사: 독과 연금술을 사용하는 마법사 겸 연금술사.\n";
	temp += "초보 연금술사의 책을 들고 독침을 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'n',5,temp,true,select_job,13);
	temp = "심리학자: 상대를 조종하는 심리마법을 배우는 디버프에 능한 마법사.\n";
	temp += "초보 심리학자의 책을 들고 최면을 배우고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'o',5,temp,true,select_job,14);
	temp = "사신: 직업을 상징하는 거대한 낫을 들고 시작하는 무서운 존재들.\n";
	temp += "저주받은 +3 낫과 로브를 끼고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'p',5,temp,true,select_job,15);
	temp = "광신도: 특정 신에 광적인 믿음을 가지고 있는 신자들.\n";
	temp += "텐시 또는 유카리를 믿고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'q',5,temp,true,select_job,16);
	temp = "암살자: 은신술과 암살의 대가들로 적을 비겁하게 기습한다.\n";
	temp += "단검과 독침, 높은 은신치를 가지고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'r',5,temp,true,select_job,17);
	temp = "농부: 우리들이 밥을 먹을 수 있도록 농사를 지으시는 고마우신 분들.\n";
	temp += "선택한 무기와 3개의 빵, 미노리코를 믿고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'s',5,temp,true,select_job,18);
	temp = "메이드: 단검정도 던지는건 메이드의 기본 소양 아닌가요?\n";
	temp += "빗자루와 4개의 투척용 나이프와 메이드의 복, 그리고 메이드의 기본소양을 들고 시작한다.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'t',5,temp,true,select_job,19);
	temp = "실종자: 우연히 환상향에 흘러들어가버린 우리들이다?\n";
	temp += "미구현. 하지마세요.\n\n\n";
	temp += "같은 키를 한번 더 누르거나 엔터를 쳐서 진행한다.\n";
	m_mgr.menu_input_puls(4,'u',5,temp,true,select_job,20);
	m_mgr.menu_input_puls(4,VK_ESCAPE,3,"",false,NULL,0);




	m_mgr.loop(0);
}

