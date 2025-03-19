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
	if (FAILED(idleImages->Init(L"Image/bluemary_stance.bmp", 840, 123, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stance ���� �ε忡 ����", L"���", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/bluemary_walk.bmp", 560, 107, 10, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk ���� �ε忡 ����", L"���", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);

	Image* weakHandImages = new Image();
	if (FAILED(weakHandImages->Init(L"Image/bluemary_weakhand.bmp", 340, 102, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakhand ���� �ε忡 ����", L"���", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakHandImages);

	Image* strongHandImages = new Image();
	if (FAILED(strongHandImages->Init(L"Image/bluemary_stronghand.bmp", 3168, 106, 22, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stronghand ���� �ε忡 ����", L"���", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongHandImages);

	Image* weakFootImages = new Image();
	if (FAILED(weakFootImages->Init(L"Image/bluemary_weakfoot.bmp", 891, 106, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakfoot ���� �ε忡 ����", L"���", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakFootImages);
	
	Image* strongFootImages = new Image();
	if (FAILED(strongFootImages->Init(L"Image/bluemary_strongfoot.bmp", 1548, 115, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot ���� �ε忡 ����", L"���", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongFootImages);
	
	Image* deadImages = new Image();
	if (FAILED(deadImages->Init(L"Image/bluemary_fall.bmp", 1548, 115, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_fall ���� �ε忡 ����", L"���", MB_OK);
	}
	vImages[State::Dead].push_back(deadImages);

	curState = State::Idle;
	frameIdx = 0;
	flip = false;

	Image* img = vImages[State::Idle][0];
	size[0] = img->GetWidth() / img->GetSpritesNumX();
	size[1] = img->GetHeight() / img->GetSpritesNumY();
}
