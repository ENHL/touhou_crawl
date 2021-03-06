

#include "common.h"
#include "map.h"
#include "option_manager.h"

#include <random>
#include <ctime>
#include <iostream>

using namespace std;


extern POINT MousePoint;

extern map_infor map_list;

FILE *fpfpfp = NULL; 
int linelin =0;


std::mt19937 rand_engine;




void test_rand(const char* tt)
{

	char test_test[256], test_test2[256];
	

	if(!fpfpfp)
	{
		fpfpfp = fopen("replay/test_random2.txt","rt"); 


	}
	if(fpfpfp)
		fgets(test_test,256,fpfpfp);
	linelin++;

	FILE *fp;  
	fp = fopen("replay/test_random.txt","at");
	
	fprintf(fp,"|%30s|%ud\n",tt,map_list.random_number);
	
	sprintf(test_test2,"|%30s|%ud\n",tt,map_list.random_number);
	fclose(fp);



	if(strcmp(test_test,test_test2))
	{
			linelin+=2;
			
			linelin--;
			linelin--;

	}
}

void rand_seed(unsigned int seed_)
{
	rand_engine.seed((unsigned long)(seed_));

}

int LoopSelect(int min, int max, int cur)
{
	if(min	> max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	else if(min == max)
		return min;

	while(!(min <= cur && cur <= max))
	{
		if(cur < min)
			cur+= max-min+1;
		else
			cur-= max-min+1;
	}
	return cur;
}

int CutSelect(int min, int max, int cur)
{
	if(min	> max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	else if(min == max)
		return min;

	return ((cur>max)?max:((cur<min)?min:cur));

}
float rand_float(float min, float max)
{
	//char temp_str[64];
	//sprintf_s(temp_str,64,"rand_float(%f,%f)",min,max);
	//test_rand(temp_str);


	if(min == max)
		return min;

	if(min > max)
	{
		float temp = min;
		min = max;
		max = temp;
	}
	//min = (float)(random_number % (int)((max - min)*100 + 1)) /100 + min;
	//random_number = (((random_number*214013L + 2531011L)>>16)&0x7fff);
	rand_seed(map_list.random_number);
	int rand_ = abs((int)rand_engine());
	min = (float)(rand_ % (int)((max - min)*100 + 1)) /100 + min;
	map_list.random_number = rand_;
	
	//min = (float)(map_list.random_number % (int)((max - min)*100 + 1)) /100 + min;

	return min;
}

int rand_int(int min, int max)
{
	//char temp_str[64];
	//sprintf_s(temp_str,64,"rand_int(%d,%d)",min,max);
	//test_rand(temp_str);



	if(min == max)
		return min;

	if(min > max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	//min = (random_number % (max - min+1)) + min;
	
	rand_seed(map_list.random_number);
	int rand_ = rand_engine();
	min = (rand_engine() % (max - min+1)) + min;
	map_list.random_number = rand_;
	//map_list.random_number = (((map_list.random_number*214013L + 2531011L)>>16)&0x7fff);

	return min;
}

float GetPositionToAngle(float start_x, float start_y, float target_x, float target_y)
{
	return atan2(target_y - start_y, target_x - start_x) * 180 / D3DX_PI;

}

float GetPositionToAngle2(float start_x, float start_y, float target_x, float target_y)
{
	return atan2(target_y - start_y, target_x - start_x);

}

float GetBaseAngle(float angle)
{
	while(angle <= 0 || angle > 360)
	{
		if(angle <= 0)
			angle += 360;
		if(angle > 360)
			angle -= 360;
	}
	return angle;
}
int GetPosToDirec(const coord_def &start, const coord_def &target)
{
	coord_def c = target-start;
	if(c.abs()<=2)
	{
		switch((c.x+1)*10+c.y+1)
		{
		case 00:
			return 7;
		case 10:
			return 0;
		case 20:
			return 1;
		case 01:
			return 6;
		case 11:
			return 0;
		case 21:
			return 2;
		case 02:
			return 5;
		case 12:
			return 4;
		case 22:
			return 3;
		}
	}
	int angle = (int) GetPositionToAngle(start.x,start.y,target.x,target.y);
	angle = (angle+360)%360;
	return GetAngleToDirec(angle);
}
coord_def GetDirecToPos(int pos_)
{
	switch((pos_+8)%8)
	{
	case 7:
		return coord_def(-1,-1);
	case 0:
		return coord_def(0,-1);
	case 1:
		return coord_def(1,-1);
	case 6:
		return coord_def(-1,0);
	case 2:
		return coord_def(1,0);
	case 5:
		return coord_def(-1,1);
	case 4:
		return coord_def(0,1);
	case 3:
		return coord_def(1,1);
	}
	return coord_def(0,0);
}
int GetAngleToDirec(int angle)
{
	if(angle>=22 && angle <67)
		return 3;
	else if(angle>=67 && angle < 112)
		return 4;
	else if(angle>=112 && angle < 157)
		return 5;
	else if(angle>=157 && angle < 202)
		return 6;
	else if(angle>=202 && angle < 247)
		return 7;
	else if(angle>=247 && angle < 292)
		return 0;
	else if(angle>=292 && angle < 337)
		return 1;
	else
		return 2;
}

float GetPositionGap(float start_x, float start_y, float target_x, float target_y)
{
	return sqrt((target_x - start_x)*(target_x - start_x)+ (target_y - start_y)*(target_y - start_y));

}

float GetMaxX()
{
	return (float)option_mg.getWidth();
}

float GetMaxY()
{
	return (float)option_mg.getHeight();
}

float GetCenterX()
{
	return (float)option_mg.getWidth()/2;
}

float GetCenterY()
{
	return (float)option_mg.getHeight()/2;
}

/*float round(float x)
{
   return ((x>0) ? floor(x+.5f) : ceil(x-.5f));
}*/
float round_down(float x)
{
   return ((x>0) ? floor(x+0.25f) : ceil(x-0.75f));
}
float round_up(float x)
{
   return ((x>0) ? floor(x+0.75f) : ceil(x-0.25f));
}
float ceil_up(float x)
{
   return ((x>0) ? floor(x+0.999f) : ceil(x-0.001f));
}
char asctonum(char a)
{
	return (a>='a'&&a<='z')?(a-'a'):((a>='A'&&a<='Z')?(a-'A'+26):0);
}

int randA(int x)
{
	if(x>0)
		return rand_int(0,x);
	else
		return 0;
}

int randA_1(int x)
{
	if(x>1)
		return rand_int(1,x);
	else
		return 1;
}


bool randB(int x, int point)
{
	return (randA(x) <= point);
}

int randC(int dice, int x)
{
	int a=0;
	for(int i=0;i<dice;i++)
		a += randA_1(x);
	return a;
}


int distan_coord(const coord_def& a, const coord_def& b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);

}