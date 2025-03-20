#include "BlueMary.h"
#include "Image.h"
#include "CommonFunction.h"

void BlueMary::Init()
{
	position = { 100,200 };
	speed = 100;
	dx = 0.0f;
	dy = 0.0f;
	hp = 10.0f;
	accumTime = 0.0f;

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/BlueMary/bluemary_stance.bmp", 200 * 12, 200, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stance 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);
	animTime[State::Idle] = 1.0f;

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/BlueMary/bluemary_walk.bmp", 200 * 10, 200, 10, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);
	animTime[State::Walk] = 1.0f;

	Image* weakHandImages = new Image();
	if (FAILED(weakHandImages->Init(L"Image/BlueMary/bluemary_weakhand.bmp", 200 * 4, 200, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakhand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakHandImages);
	animTime[State::WeakHand] = 0.3f;

	Image* strongHandImages = new Image();
	if (FAILED(strongHandImages->Init(L"Image/BlueMary/bluemary_stronghand.bmp", 200 * 22, 200, 22, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stronghand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongHandImages);
	animTime[State::StrongHand] = 1.0f;

	Image* weakFootImages = new Image();
	if (FAILED(weakFootImages->Init(L"Image/BlueMary/bluemary_weakfoot.bmp", 200 * 9, 200, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakFootImages);
	animTime[State::WeakFoot] = 0.7f;

	Image* strongFootImages = new Image();
	if (FAILED(strongFootImages->Init(L"Image/BlueMary/bluemary_strongfoot.bmp", 200 * 12, 200, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongFootImages);
	animTime[State::StrongFoot] = 1.0f;

	Image* deadImages = new Image();
	if (FAILED(deadImages->Init(L"Image/BlueMary/bluemary_fall.bmp", 200 * 20, 200, 20, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_fall 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Dead].push_back(deadImages);
	animTime[State::Dead] = 1.0f;

	curState = State::Idle;
	frameIdx = 0;
	flip = false;
	offset = 15;
}
void BlueMary::Action()
{
	hurtBox = GetRect(position.x + 70, position.y + 52, 112, 208);

	switch (curState)
	{
	case WeakHand:
		if (isSuccessHit == false)
		{
			hitBox = GetRect(position.x + 140, position.y + 62, 100, 50);
		}
		else
		{
			hitBox = GetRect(0, 0, 0, 0);
		}
		break;
	case StrongHand:
		if (isSuccessHit == false)
		{
			hitBox = GetRect(position.x + 140, position.y + 104, 105, 50);
		}
		else
		{
			hitBox = GetRect(0, 0, 0, 0);
		}
		break;
	case WeakFoot:
		if (isSuccessHit == false)
		{
			hitBox = GetRect(position.x + 140, position.y + 104, 110, 50);
		}
		else
		{
			hitBox = GetRect(0, 0, 0, 0);
		}
		break;
	case StrongFoot:
		if (isSuccessHit == false)
		{
			hitBox = GetRect(position.x + 140, position.y + 10, 100, 100);
		}
		else
		{
			hitBox = GetRect(0, 0, 0, 0);
		}
		break;
	case WeakDamaged:
		break;
	case StrongDamaged:
		break;
	default:
		hitBox = GetRect(0, 0, 0, 0);
		isSuccessHit = false;
		break;
	}
}