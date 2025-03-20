#include "Kim.h"
#include "Image.h"
#include "CommonFunction.h"

void Kim::Init()
{
	position = { 0,200 };
	speed = 10;
	dx = 0.0f;
	dy = 0.0f;

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/Kim/kim_idle.bmp", 256 * 4, 256, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stance 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/Kim/kim_walk.bmp", 256 * 6, 256, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);

	Image* weakHandImages = new Image();
	if (FAILED(weakHandImages->Init(L"Image/Kim/kim_AAttack.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakhand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakHandImages);

	Image* strongHandImages = new Image();
	if (FAILED(strongHandImages->Init(L"Image/Kim/kim_CAttack.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stronghand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongHandImages);

	Image* weakFootImages = new Image();
	if (FAILED(weakFootImages->Init(L"Image/Kim/kim_BAttack.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakFootImages);

	Image* strongFootImages = new Image();
	if (FAILED(strongFootImages->Init(L"Image/Kim/kim_DAttack.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongFootImages);

	Image* deadImages = new Image();
	if (FAILED(deadImages->Init(L"Image/bluemary_fall.bmp", 256, 256, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_fall 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Dead].push_back(deadImages);

	curState = State::Idle;
	frameIdx = 0;
	flip = true;
}

void Kim::Update()
{
	Move();

	Animate(3);

	ProcessInput();
}


void Kim::Move()
{
	position.x += dx * speed;
	position.y += dy * speed;
	position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);
	if (dx > 0) flip = true;
	if (dx < 0) flip = false;
}
