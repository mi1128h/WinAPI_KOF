#include "Kim.h"
#include "Image.h"
#include "CommonFunction.h"

void Kim::Init()
{
	position = { 0,0 };
	speed = 100;
	dx = 0.0f;
	dy = 0.0f;
	hurtBox = { 0,0,0,0 };
	hitBox = { 10,10,0,0 };
	isSuccessHit = false;
	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/Kim/kim_stance.bmp", 256 * 4, 256, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stance 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);
	animTime[State::Idle] = 1.0f;

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/Kim/kim_walk.bmp", 256 * 6, 256, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);
	animTime[State::Walk] = 1.0f;

	Image* weakHandImages = new Image();
	if (FAILED(weakHandImages->Init(L"Image/Kim/kim_weakhand.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakhand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakHandImages);
	animTime[State::WeakHand] = 1.0f;

	Image* strongHandImages = new Image();
	if (FAILED(strongHandImages->Init(L"Image/Kim/kim_stronghand.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stronghand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongHandImages);
	animTime[State::StrongHand] = 1.0f;

	Image* weakFootImages = new Image();
	if (FAILED(weakFootImages->Init(L"Image/Kim/kim_weakfoot.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakFootImages);
	animTime[State::WeakFoot] = 1.0f;

	Image* strongFootImages = new Image();
	if (FAILED(strongFootImages->Init(L"Image/Kim/kim_strongfoot.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongFootImages);
	animTime[State::StrongFoot] = 1.0f;

	Image* weakDamageImages = new Image();
	if (FAILED(weakDamageImages->Init(L"Image/Kim/kim_weakdamage.bmp", 256 * 2, 256, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakDamaged].push_back(weakDamageImages);
	animTime[State::WeakDamaged] = 1.0f;

	Image* StrongDamageImages = new Image();
	if (FAILED(StrongDamageImages->Init(L"Image/Kim/kim_strongdamage.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongDamaged].push_back(StrongDamageImages);
	animTime[State::StrongDamaged] = 1.0f;

	/*Image* deadImages = new Image();
	if (FAILED(deadImages->Init(L"Image/bluemary_fall.bmp", 256, 256, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_fall 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Dead].push_back(deadImages);*/

	curState = State::Idle;
	frameIdx = 0;
	defaultFlip = flip = true;
}


void Kim::Move(float elapsedTime)
{
	position.x += dx * speed * elapsedTime;
	position.y += dy * speed * elapsedTime;
	position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);
	if (dx > 0) flip = true;
	if (dx < 0) flip = false;
}

void Kim::Action()
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


