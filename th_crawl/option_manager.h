//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: option_manager.h
//
// ����: �ɼ� �Ŵ����� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <tchar.h>
#include <atlstr.h>
#include <windows.h> 

#define MAX_STR_SIZE 260

using namespace std;
class optionManager {

	string name;

	int height;
	int width;

private:
	optionManager() {};
public:
	optionManager(string fileName);

	void createNewFile(string fileName);

	int getHeight() { return height; };
	int getWidth() { return width; };


private:
	string TCHARToString(const TCHAR* ptsz);

};


extern optionManager option_mg;




