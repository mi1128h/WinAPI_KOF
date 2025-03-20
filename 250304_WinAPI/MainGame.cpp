#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "AnimCharacter.h"
#include "AnimBackground.h"
#include "BlueMary.h"
#include "SherCharacter.h"
#include "Mai.h"
#include "Kyo.h"
#include "Timer.h"


/*
	�ǽ�1. �̿��� ���� ������
	�ǽ�2. ��� �ٲٱ� (ŷ���� �ִϸ��̼� ���)
*/

void MainGame::Init()
{
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y))) {
		MessageBox(g_hWnd, L"backBuffer ���� ����", L"���", MB_OK);
	}

	Player1 = new SherCharacter();
	Player1->setPlayer_Classification(false);
	Player1->Init();

	Player2 = new Mai();
	Player2->setPlayer_Classification(true);
	Player2->Init();


	background = new AnimBackground();
	background->Init();

	KeyManager* km = KeyManager::GetInstance();
	km->Init();

	gameTimer = new Timer();
	gameTimer->Init();
}

void MainGame::Release()
{
	if (Player1) {
		Player1->Release();
		delete Player1;
		Player1 = NULL;
	}

	if (Player2) {
		Player2->Release();
		delete Player2;
		Player2 = NULL;
	}

	if (background) {
		background->Release();
		delete background;
		background = NULL;
	}

	if (backBuffer) {
		backBuffer->Release();
		delete backBuffer;
		backBuffer = NULL;
	}

	KeyManager* km = KeyManager::GetInstance();
	if (km) km->Release();

	if (gameTimer) delete gameTimer;
}

void MainGame::Update()
{
	float elapsedTime{};
	if (gameTimer) {
		gameTimer->Tick();
		elapsedTime = gameTimer->GetElapsedTime();
	}

	if (iori) iori->Update(elapsedTime);
	if (Player1) Player1->Update();
	if (Player2) Player2->Update();
	if (background) background->Update();
}

void MainGame::Render(HDC hdc)
{
	if (!backBuffer) return;
	// ����ۿ� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();
	BitBlt(hBackBufferDC, 0, 0, WINSIZE_X, WINSIZE_Y, hdc, 0, 0, WHITENESS);

	if (background) {
		background->Render(hBackBufferDC);
	}

	if (Player1) {
		Player1->Render(hBackBufferDC);
	}

	if (Player2) {
		Player2->Render(hBackBufferDC);
	}

	// ����ۿ� �ִ� ������ ���� hdc�� ����
	backBuffer->Render(hdc);
}




LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 10, NULL);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 0:
			Update();
			break;
		}

		InvalidateRect(g_hWnd, NULL, FALSE);
		break;

#ifdef KEYDOWN

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
#endif // KEYDOWN

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
			Player1->SetDelta(0, 0);
			Player2->SetDelta(0, 0);
			break;
		case 'd': case 'D':
			Player1->SetDelta(0, 0);
			Player2->SetDelta(0, 0);
			break;
		case 'w': case 'W':
			Player1->SetDelta(0, 0);
			Player2->SetDelta(0, 0);
			break;
		case 's': case 'S':
			Player1->SetDelta(0, 0);
			Player2->SetDelta(0, 0);
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

		// test
		wsprintf(szText, L"mouse: %d, %d", mousePosX, mousePosY);
		TextOut(hdc, 0, 0, szText, wcslen(szText));

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);

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
