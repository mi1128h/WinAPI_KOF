#pragma once
#include "GameObject.h"

class Tank;
class Enemy;
class RoundManager;
class Image;
class AnimCharacter;
class AnimBackground;
class Timer;
class MainGame : public GameObject
{
private:
	HDC hdc{};
	PAINTSTRUCT ps{};
	HANDLE hTimer{}, hTimer2;
	int mousePosX{}, mousePosY{};
	wchar_t szText[128]{};

	Tank* tank;
	vector<Enemy*> enemies;
	int nDeadEnemies;

    RoundManager* roundManager; // ������ ���带 �����ϴ� ��ü

    Image* backBuffer;        // ����� (ȭ�� ������ ������)
    AnimCharacter* Player1;      // �ִϸ��̼� ĳ���� ��ü (����)
	AnimCharacter* Player2;
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

