#include "Kim.h"
#include "Image.h"
#include "CommonFunction.h"

void Kim::Init()
{
	position = { 0,0 };
	speed = 300;
	dx = 0.0f;
	dy = 0.0f;
	size = 1.0f;
	hp = 10.0f;
	accumTime = 0.0f;
	offset = -15;

	isSuccessHit = false;
	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/Kim/kim_stance.bmp", 256 * 4, 256, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stance 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);
	animTime[State::Idle] = 0.5f;

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/Kim/kim_walk.bmp", 256 * 6, 256, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);
	animTime[State::Walk] = 0.5f;
	
	Image* backWalkImages = new Image();
	if (FAILED(backWalkImages->Init(L"Image/Kim/kim_backwalk.bmp", 256 * 6, 256, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::BackWalk].push_back(backWalkImages);
	animTime[State::BackWalk] = 0.5f;

	Image* weakHandImages = new Image();
	if (FAILED(weakHandImages->Init(L"Image/Kim/kim_weakhand.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakhand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakHandImages);
	animTime[State::WeakHand] = 0.3f;

	Image* strongHandImages = new Image();
	if (FAILED(strongHandImages->Init(L"Image/Kim/kim_stronghand.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stronghand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongHandImages);
	animTime[State::StrongHand] = 0.5f;

	Image* weakFootImages = new Image();
	if (FAILED(weakFootImages->Init(L"Image/Kim/kim_weakfoot.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakFootImages);
	animTime[State::WeakFoot] = 0.5f;

	Image* strongFootImages = new Image();
	if (FAILED(strongFootImages->Init(L"Image/Kim/kim_strongfoot.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongFootImages);
	animTime[State::StrongFoot] = 0.5f;

	Image* weakDamageImages = new Image();
	if (FAILED(weakDamageImages->Init(L"Image/Kim/kim_weakdamage.bmp", 256 * 2, 256, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakDamaged].push_back(weakDamageImages);
	animTime[State::WeakDamaged] = 0.3f;

	Image* StrongDamageImages = new Image();
	if (FAILED(StrongDamageImages->Init(L"Image/Kim/kim_strongdamage.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongDamaged].push_back(StrongDamageImages);
	animTime[State::StrongDamaged] = 0.4f;

	
	curState = State::Idle;
	frameIdx = 0;
	defaultFlip = flip = true;
}



void Kim::Action()
{
	hurtBox = GetRect(position.x - 60 * size, position.y - 210 * size , 120 * size, 210 * size);

	switch (curState)
	{
	case WeakHand:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 1)
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 170 * size, 110 * size, 30 * size);
			}
			else
			{
				hitBox = GetRect(position.x - 110 * size, position.y - 170 * size, 110 * size, 30 * size);
			}
		}
		
		break;
	case StrongHand:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 2)
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 140 * size, 140 * size, 30 * size);
			}
			else
			{
				hitBox = GetRect(position.x - 140 * size, position.y - 140 * size, 140 * size, 30 * size);
			}
		}
		
		break;
	case WeakFoot:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 2)
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 155 * size, 120 * size, 40 * size);
			}
			else
			{
				hitBox = GetRect(position.x - 120 * size, position.y - 155 * size, 120 * size, 40 * size);
			}
		}
		
		break;
	case StrongFoot:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 1)
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 250 * size, 100 * size, 150 * size);
			}
			else
			{
				hitBox = GetRect(position.x - 100 * size, position.y - 250 * size, 100 * size, 150 * size);
			}
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


