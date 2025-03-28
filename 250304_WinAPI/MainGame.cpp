#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "AnimCharacter.h"
#include "AnimBackground.h"
#include "BlueMary.h"
#include "Kim.h"
#include "SherCharacter.h"
#include "Mai.h"

#include "Kyo.h"
#include "Timer.h"


void MainGame::Init()
{
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y))) {
		MessageBox(g_hWnd, L"backBuffer ?�성 ?�패", L"경고", MB_OK);

	}

	Player1 = new Kyo();
	Player1->SetPlayerClassification(true);
	Player1->Init();
	Player1->SetStartPos();


	Player2 = new Mai();
	Player2->SetPlayerClassification(false);
	Player2->Init();
	Player2->SetStartPos();

	Player3 = new Kim();
	Player3->SetPlayerClassification(true);
	Player3->Init();
	Player3->SetStartPos();


	Player4 = new BlueMary();
	Player4->SetPlayerClassification(false);
	Player4->Init();
	Player4->SetStartPos();


	background = new AnimBackground();
	background->Init();

	KeyManager* km = KeyManager::GetInstance();
	km->Init();


	gameTimer = new Timer();
	gameTimer->Init();

	UIManager* ui = UIManager::GetInstance();
	ui->Init();
	CollisionManager* cm = CollisionManager::GetInstance();
	cm->Init();


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
	UIManager* ui = UIManager::GetInstance();
	if (ui) ui->Release();

	CollisionManager* cm = CollisionManager::GetInstance();
	if (cm) cm->Release();
}

void MainGame::Update()
{
	float elapsedTime{};
	if (gameTimer) {
		gameTimer->Tick();
		elapsedTime = gameTimer->GetElapsedTime();
	}

	UIManager* ui = UIManager::GetInstance();
	if (ui) ui->Update(Player1, Player2, elapsedTime);

	CollisionManager* cm = CollisionManager::GetInstance();
	cm->CheckHit(Player1, Player2);
	cm->CheckHit(Player2, Player1);

	if (Player1 and Player2) SetPlayerFlip();

	if (Player1) Player1->Update(elapsedTime);
	if (Player2) Player2->Update(elapsedTime);
	if (background) background->Update(elapsedTime);

	if (Player1->IsDeadDone()) {
		Player1 = Player3;
	}
	if (Player2->IsDeadDone()) {
		Player2 = Player4;
	}

}

void MainGame::Render(HDC hdc)
{
	if (!backBuffer) return;

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

	UIManager* ui = UIManager::GetInstance();
	if(ui) ui->Render(hBackBufferDC);


	backBuffer->Render(hdc);
}

void MainGame::SetPlayerFlip()
{
	if (!Player1 or !Player2) return;

	FPOINT pos1 = Player1->GetPos();
	FPOINT pos2 = Player2->GetPos();

	if (pos1.x < pos2.x) {
		Player1->LookRight(true);
		Player2->LookRight(false);
	}
	else if (pos1.x > pos2.x) {
		Player1->LookRight(false);
		Player2->LookRight(true);
	}
	// if(pos1.x == pos2.x) keep flip val
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


	case WM_KEYUP:

		switch (wParam) {
		case 'v': case 'V':
			// test DeadAnim
			Player2->SetState(State::Dead);
			break;
		case 'a': case 'A':

			break;
		case 'd': case 'D':

			break;
		case 'w': case 'W':

			break;
		case VK_SPACE:
			UIManager * ui = UIManager::GetInstance();
			ui->SetDrawFirstScreen(false);
			break;
		}
		InvalidateRect(g_hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		break;

	case WM_LBUTTONDOWN:

		break;

	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		Render(hdc);

		// test

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
