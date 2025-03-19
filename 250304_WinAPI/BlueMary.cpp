#include "BlueMary.h"
#include "Image.h"
#include "CommonFunction.h"

void BlueMary::Init()
{
	position = { 0,0 };
	speed = 10;
	dx = 0.0f;
	dy = 0.0f;

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/BlueMary/bluemary_stance.bmp", 840, 123, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stance 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/BlueMary/bluemary_walk.bmp", 560, 107, 10, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);

	Image* weakHandImages = new Image();
	if (FAILED(weakHandImages->Init(L"Image/BlueMary/bluemary_weakhand.bmp", 340, 113, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakhand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakHandImages);

	Image* strongHandImages = new Image();
	if (FAILED(strongHandImages->Init(L"Image/BlueMary/bluemary_stronghand.bmp", 3168, 113, 22, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stronghand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongHandImages);

	Image* weakFootImages = new Image();
	if (FAILED(weakFootImages->Init(L"Image/BlueMary/bluemary_weakfoot.bmp", 891, 112, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakFootImages);
	
	Image* strongFootImages = new Image();
	if (FAILED(strongFootImages->Init(L"Image/BlueMary/bluemary_strongfoot.bmp", 1548, 115, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongFootImages);
	
	Image* deadImages = new Image();
	if (FAILED(deadImages->Init(L"Image/BlueMary/bluemary_fall.bmp", 4000, 128, 20, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_fall 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Dead].push_back(deadImages);

	curState = State::Idle;
	frameIdx = 0;
	flip = false;
}
