#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "AnimCharacter.h"
#include "AnimBackground.h"
#include "Kyo.h"
#include "Timer.h"



void MainGame::Init()
{
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y))) {
		MessageBox(g_hWnd, L"backBuffer 생성 실패", L"경고", MB_OK);
	}
	iori = new Kyo();
	iori->Init();

	background = new AnimBackground();
	background->Init();

	KeyManager* km = KeyManager::GetInstance();
	km->Init();

	gameTimer = new Timer();
	gameTimer->Init();
	UIManager* ui = UIManager::GetInstance();
	ui->Init();

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

}

void MainGame::Update()
{

	float elapsedTime{};
	if (gameTimer) {
		gameTimer->Tick();
		elapsedTime = gameTimer->GetElapsedTime();
	}

	if (iori) iori->Update(elapsedTime);
	if (background) background->Update(elapsedTime);


	UIManager* ui = UIManager::GetInstance();
	if (ui) ui->Update(iori, iori);

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

	UIManager* ui = UIManager::GetInstance();
	if(ui) ui->Render(hBackBufferDC);

	// 백버퍼에 있는 내용을 메인 hdc에 복사
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

	case WM_KEYDOWN:

		InvalidateRect(g_hWnd, NULL, FALSE);
		break;

	case WM_KEYUP:

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
