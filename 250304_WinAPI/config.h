#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <random>
#include <bitset>

#include "KeyManager.h"

using namespace std;

// 컴파일러에서 해당 코드를 뒤에 정의된 코드로 변경한다
#define WINSIZE_X 1080
#define WINSIZE_Y 500

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
// extern 변수나 함수가 다른 파일에 정의되어 있다는 사실을 알리는 키워드

#define TORADIAN(degree) 3.141592f / 180.0f * degree
#define TODEGREE(radian) 180.0f / 3.141592f * radian

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

extern random_device rd;
extern default_random_engine dre;
extern uniform_int_distribution<int> uid_0_10;
extern uniform_int_distribution<int> uid_200_255;
extern uniform_int_distribution<int> uid_0_255;
extern uniform_int_distribution<int> uid_1_2;
extern uniform_int_distribution<int> uid_0_WINSIZEX;

#pragma comment(lib, "msimg32.lib")