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
    Kim* Player1;      // �ִϸ��̼� ĳ���� ��ü (����)
	Kim* Player2;
    AnimBackground* background; // �ִϸ��̼� ��� ��ü


	Timer* gameTimer;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void RenderInfo(HDC hdc);

	void CreateEnemy();
	void SetGuidedBulletsTarget();
	void RestartGame();
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

