#pragma once
#include "GameObject.h"


class Image;
class AnimCharacter;
class AnimBackground;
class Timer;
class Kim;

class MainGame : public GameObject
{
private:
	HDC hdc{};
	PAINTSTRUCT ps{};
	HANDLE hTimer{};
	int mousePosX{}, mousePosY{};
	wchar_t szText[128]{};


    Image* backBuffer;        // 백버퍼 (화면 깜빡임 방지용)
    AnimCharacter* Player1;      // 애니메이션 캐릭터 객체 (샐리)
	AnimCharacter* Player2;
	AnimCharacter* Player3;
	AnimCharacter* Player4;
    AnimBackground* background; // 애니메이션 배경 객체


	Timer* gameTimer;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetPlayerFlip();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

