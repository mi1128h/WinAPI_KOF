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


    Image* backBuffer;        // ����� (ȭ�� ������ ������)
    AnimCharacter* Player1;      // �ִϸ��̼� ĳ���� ��ü (����)
	AnimCharacter* Player2;
	AnimCharacter* Player3;
	AnimCharacter* Player4;
    AnimBackground* background; // �ִϸ��̼� ��� ��ü


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

