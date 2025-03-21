#include "BlueMary.h"
#include "Image.h"
#include "CommonFunction.h"

void BlueMary::Init()
{
	position = { 100,200 };
	speed = 300;
	dx = 0.0f;
	dy = 0.0f;
	size = 2.0f;
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

	Image* backWalkImages = new Image();
	if (FAILED(backWalkImages->Init(L"Image/BlueMary/bluemary_backwalk.bmp", 200 * 6, 200, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_backwalk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::BackWalk].push_back(backWalkImages);
	animTime[State::BackWalk] = 1.0f;

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
	animTime[State::StrongFoot] = 0.8;

	Image* weakDamageImages = new Image();
	if (FAILED(weakDamageImages->Init(L"Image/BlueMary/bluemary_attacked.bmp", 200 * 2, 200, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_attacked 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakDamaged].push_back(weakDamageImages);
	animTime[State::WeakDamaged] = 0.3f;

	Image* StrongDamageImages = new Image();
	if (FAILED(StrongDamageImages->Init(L"Image/BlueMary/bluemary_attacked.bmp", 200 * 2, 200, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_attacked 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongDamaged].push_back(StrongDamageImages);
	animTime[State::StrongDamaged] = 0.5f;
	
	Image* DefendImages = new Image();
	if (FAILED(DefendImages->Init(L"Image/BlueMary/blumary_block.bmp", 200 * 1, 200, 1, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"blumary_block 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Defend].push_back(DefendImages);
	animTime[State::Defend] = 0.5f;
	
	
	Image* SkillImages = new Image();
	if (FAILED(SkillImages->Init(L"Image/BlueMary/bluemary_skill.bmp", 390*53, 200, 53, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_skill 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Skill].push_back(SkillImages);
	animTime[State::Skill] = 2.0f;

	Image* deadImages = new Image();
	if (FAILED(deadImages->Init(L"Image/BlueMary/bluemary_fall2.bmp", 200 * 12, 200, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_fall2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Dead].push_back(deadImages);
	animTime[State::Dead] = 1.0f;

	curState = State::Idle;
	frameIdx = 0;
	defaultFlip = flip = false;
	offset = 0;
}
void BlueMary::Action()
{
	hurtBox = GetRect(position.x - 32*size, position.y - 108*size, 64*size, 108*size);

	switch (curState)
	{
	case WeakHand:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 2)
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 88 * size, 50 * size, 30 * size);
			}
			else
			{
				hitBox = GetRect(position.x - 50 * size, position.y - 88 * size, 50 * size, 30 * size);
			}
		}

		break;
	case StrongHand:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 9 || frameIdx == 10 || frameIdx == 11 || frameIdx == 12 || frameIdx == 13)
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 88 * size, 105 * size, 50 * size);
			}
			else
			{
				hitBox = GetRect(position.x - 105 * size, position.y - 88 * size, 105 * size, 50 * size);
			}
		}

		break;
	case WeakFoot:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 4 || frameIdx == 5)
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 78 * size, 60 * size, 30 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 60 * size, position.y - 78 * size, 60 * size, 30 * size);

			}
		}

		break;
	case StrongFoot:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 3 || frameIdx == 4 || frameIdx == 5)
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 78 * size, 90 * size, 30 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 90 * size, position.y - 78 * size, 90 * size, 30 * size);

			}
		}

		break;

	case Skill:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx >= 38 && frameIdx <= 42 )
		{
			if (flip == defaultFlip)
			{
				hitBox = GetRect(position.x, position.y - 108 * size, 200 * size, 108 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 200 * size, position.y - 108 * size, 200 * size, 108 * size);

			}
		}

		break;
	case Dead:
		hurtBox = GetRect(1, 1, 1, 1);
		break;
	default:
		hitBox = GetRect(0, 0, 0, 0);
		isSuccessHit = false;
		break;
	}
}