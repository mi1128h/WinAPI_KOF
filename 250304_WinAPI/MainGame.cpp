#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "RoundManager.h"
#include "CommonFunction.h"
#include "Image.h"
#include "AnimCharacter.h"
#include "AnimBackground.h"

/*
	실습1. 이오리 집에 보내기
	실습2. 배경 바꾸기 (킹오파 애니메이션 배경)
*/

void MainGame::Init()
{
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y))) {
		MessageBox(g_hWnd, L"backBuffer 생성 실패", L"경고", MB_OK);
	}
	iori = new AnimCharacter();
	iori->Init();

	background = new AnimBackground();
	background->Init();

	KeyManager* km = KeyManager::GetInstance();
	km->Init();

#ifdef TANKGAME
	tank = new Tank();
	tank->Init();

	roundManager = new RoundManager();
	roundManager->Init();
#endif
}

void MainGame::Release()
{
	if (iori) {
		iori->Release();
		delete iori;
		iori = NULL;
	}
	if (background) {
		background->Release();
		delete iori;
		iori = NULL;
	}

	if (backBuffer) {
		backBuffer->Release();
		delete backBuffer;
		backBuffer = NULL;
	}

	KeyManager* km = KeyManager::GetInstance();
	if (km) km->Release();

#ifdef TANKGAME
	if (tank) {
		tank->Release();
		delete tank;
	}
	for (auto e : enemies) {
		if (e) delete e;
	}
	Enemy::ReleaseBullets();

	if (roundManager) delete roundManager;
#endif
}

void MainGame::Update()
{
	if (iori) iori->Update();
	if (background) background->Update();

#ifdef TANKGAME
	if (roundManager) {
		if (roundManager->IsGameOver()) return;
	}
	if (tank) tank->Update();

	int deadNum{};
	for (auto e : enemies) {
		if (e) {
			e->Update();
			if (e->IsDead()) deadNum++;
			else {
				tank->CheckCollideEnemy(e);
			}
		}
	}
	nDeadEnemies = deadNum;

	Enemy::UpdateBullets();
	if (tank) Enemy::CheckBulletsCollision(tank);

	SetGuidedBulletsTarget();

	roundManager->CheckGameOver(tank->GetHp());

	if (nDeadEnemies == enemies.size() and !roundManager->canCreateEnemy()) {
		roundManager->setIsClear(true);
	}

	bool newRound = false;
	if (!roundManager->IsGameClear()) {
		newRound = roundManager->IsNewRound();
	}

	if (newRound) {
		tank->Init();
	}

	if (roundManager->IsGameClear()) {
		tank->Skill(SkillType::Confetti);
	}
#endif
}

void MainGame::Render(HDC hdc)
{
	if (!backBuffer) return;
	// 백버퍼에 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();
	BitBlt(hBackBufferDC, 0, 0, WINSIZE_X, WINSIZE_Y, hdc, 0, 0, WHITENESS);

	if (background) {
		background->Render(hBackBufferDC);
	}
	if (iori) {
		iori->Render(hBackBufferDC);
	}

#ifdef TANKGAME
	if (roundManager)
		if (roundManager->IsGameOver()) return;
	wsprintf(szText, L"Mouse X: %d, Y: %d", mousePosX, mousePosY);
	TextOut(hBackBufferDC, 20, 160, szText, wcslen(szText));

	if (tank) tank->Render(hBackBufferDC);
	for (auto e : enemies)
		if (e) e->Render(hBackBufferDC);
	Enemy::RenderBullets(hBackBufferDC);

	RenderInfo(hBackBufferDC);
#endif

	// 백버퍼에 있는 내용을 메인 hdc에 복사
	backBuffer->Render(hdc);
}

void MainGame::RenderInfo(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	if (roundManager) {
		wsprintf(szText, L"Round: %d", roundManager->getCurrentRound());
		TextOut(hdc, 20, 20, szText, wcslen(szText));

		HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, L"Arial");
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		if (roundManager->IsGameClear()) {
			wsprintf(szText, L"Clear");
			TextOut(hdc, WINSIZE_X / 2 - wcslen(szText) / 2 * 25, WINSIZE_Y / 2 - 25, szText, wcslen(szText));
		}
		else if (roundManager->IsGameOver()) {
			wsprintf(szText, L"Game Over");
			TextOut(hdc, WINSIZE_X / 2 - wcslen(szText) / 2 * 25, WINSIZE_Y / 2 - 25, szText, wcslen(szText));
		}

		if (roundManager->IsGameClear() or roundManager->IsGameOver())
		{
			wsprintf(szText, L"Press enter to restart");
			TextOut(hdc, WINSIZE_X / 2 - wcslen(szText) / 2 * 25 + 50, WINSIZE_Y / 2 + 100, szText, wcslen(szText));
			wsprintf(szText, L"Press esc to quit");
			TextOut(hdc, WINSIZE_X / 2 - wcslen(szText) / 2 * 25 + 30, WINSIZE_Y / 2 + 150, szText, wcslen(szText));
		}

		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
	}

	// y 180~
	if (roundManager)
		if (!roundManager->IsGameOver())
			tank->RenderInfo(hdc);
}

void MainGame::CreateEnemy()
{
	if (!tank) return;
	if (!roundManager) return;
	if (roundManager->IsGameOver()) return;
	if (!roundManager->canCreateEnemy()) return;

	float hp = roundManager->getEnemyHp();
	int maxBulletNum = roundManager->getBulletNum();
	float enemySpeed = roundManager->getEnemySpeed();
	float enemySize = roundManager->getEnemySize();
	int fireSpeed = roundManager->getFireInterval();
	float bulletSpeed = roundManager->getBulletSpeed();

	if (nDeadEnemies > 0) {
		for (int i = 0; i < enemies.size(); ++i) {
			if (enemies[i]->IsDead()) {
				enemies[i]->Init(tank);
				enemies[i]->SetValuesByRound(hp, maxBulletNum, enemySpeed, enemySize, fireSpeed, bulletSpeed);
				nDeadEnemies--;
				break;
			}
		}
	}
	else {
		Enemy* enemy = new Enemy;
		enemy->Init(tank);
		enemy->SetValuesByRound(hp, maxBulletNum, enemySpeed, enemySize, fireSpeed, bulletSpeed);
		enemies.push_back(enemy);
	}

	roundManager->IncEnemyCnt();
}

void MainGame::SetGuidedBulletsTarget()
{
	if (!tank) return;
	tank->SetBulletsTarget(enemies);
}

void MainGame::RestartGame()
{
	tank->Init();
	for (auto e : enemies)
	{
		e->Init(tank);
	}
	Enemy::InitLoadedBullets();
	roundManager->Init();
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 100, NULL);
#ifdef TANKGAME
		hTimer2 = (HANDLE)SetTimer(hWnd, 1, 3000, NULL);
#endif
		break;
	case WM_TIMER:
		switch (wParam) {
		case 0:
			Update();
			break;
#ifdef TANKGAME
		case 1:
			CreateEnemy();
			break;
#endif
		}

		InvalidateRect(g_hWnd, NULL, FALSE);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		//case 'a': case 'A':
		//	iori->SetDelta(-10, 0);
		//	break;
		//case 'd': case 'D':
		//	iori->SetDelta(10, 0);
		//	break;
		//case 'w': case 'W':
		//	iori->SetDelta(0, -10);
		//	break;
		//case 's': case 'S':
		//	iori->SetDelta(0, 10);
		//	break;
		}
#ifdef TANKGAME
		switch (wParam) {
		case VK_ESCAPE:
			if (roundManager->IsGameOver() or roundManager->IsGameClear())
			{
				KillTimer(hWnd, 0);
				KillTimer(hWnd, 1);
				Release();
				PostQuitMessage(0);
			}
			break;
		case 'a': case 'A':
			tank->RotateBarrel(5);
			break;
		case 'd': case 'D':
			tank->RotateBarrel(-5);
			break;
		case VK_SPACE:
			tank->Skill(SkillType::Basic);
			break;
		case 'r': case 'R':
			tank->Skill(SkillType::Bomb);
			break;
		case 'e': case 'E':
			tank->Skill(SkillType::Bounce);
			break;
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
			tank->ProccessMoveInput(wParam);
			break;
		case VK_RETURN:
			if (roundManager->IsGameOver() or roundManager->IsGameClear())
			{
				RestartGame();
			}
			break;
		}
#endif
		InvalidateRect(g_hWnd, NULL, FALSE);
		break;

	case WM_KEYUP:
		switch (wParam) {
		case 'a': case 'A':
			iori->SetDelta(0, 0);
			break;
		case 'd': case 'D':
			iori->SetDelta(0, 0);
			break;
		case 'w': case 'W':
			iori->SetDelta(0, 0);
			break;
		case 's': case 'S':
			iori->SetDelta(0, 0);
			break;
		}

		InvalidateRect(g_hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, FALSE);
		break;

	case WM_LBUTTONDOWN:

		InvalidateRect(g_hWnd, NULL, FALSE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
#ifdef TANKGAME
		KillTimer(hWnd, 1);
#endif
		Release();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
