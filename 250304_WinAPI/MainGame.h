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

    RoundManager* roundManager; // 게임의 라운드를 관리하는 객체

    Image* backBuffer;        // 백버퍼 (화면 깜빡임 방지용)
    AnimCharacter* Player1;      // 애니메이션 캐릭터 객체 (샐리)
	AnimCharacter* Player2;
    AnimBackground* background; // 애니메이션 배경 객체


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

