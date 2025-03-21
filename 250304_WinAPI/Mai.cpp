#include "Mai.h"
#include "Image.h"
#include "CommonFunction.h"

void Mai::Init()
{
	position = { 100,200 };
	speed = 300;
	dx = 0.0f;
	dy = 0.0f;
	size = 2.0f;
	hp = 10.0f;
	accumTime = 0.0f;
	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	//---------걷기, 막기---------
	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/mai/mai_stance_ver2.bmp", 200 * 12, 150, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_stance_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);
	animTime[State::Idle] = 1.0f;

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/mai/mai_walk_ver2.bmp", 200 * 6, 160, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_walk_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);
	animTime[State::Walk] = 0.5f;

	Image* backWalkImages = new Image();
	if (FAILED(backWalkImages->Init(L"Image/mai/mai_backwalk_ver2.bmp", 200 * 6, 164, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_backwalk_ver2", L"경고", MB_OK);
	}
	vImages[State::BackWalk].push_back(backWalkImages);
	animTime[State::BackWalk] = 0.5f;


	//---------공격--------------
	Image* weakPunchImages = new Image();
	if (FAILED(weakPunchImages->Init(L"Image/mai/mai_weakpunch_ver2.bmp", 200 * 4, 146, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_weakpunch_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakPunchImages);
	animTime[State::WeakHand] = 0.7f;

	Image* strongPunchImages = new Image();
	if (FAILED(strongPunchImages->Init(L"Image/mai/mai_strongpunch_ver2.bmp", 200 * 4, 146, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_strongpunch_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongPunchImages);
	animTime[State::StrongHand] = 0.5f;

	Image* weakKickImages = new Image();
	if (FAILED(weakKickImages->Init(L"Image/mai/mai_weakkick_ver2.bmp", 200 * 6, 178, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_weakkick_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakKickImages);
	animTime[State::WeakFoot] = 0.5f;

	Image* strongKickImages = new Image();
	if (FAILED(strongKickImages->Init(L"Image/mai/mai_strongkick_ver2.bmp", 200 * 6, 178, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_strongkick_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongKickImages);
	animTime[State::StrongFoot] = 0.8f;


	//------------맞기-----------
	Image* weakDamageImages = new Image();
	if (FAILED(weakDamageImages->Init(L"Image/mai/mai_weakhurt_ver2.bmp", 200 * 2, 116, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_weakhurt_ver3 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakDamaged].push_back(weakDamageImages);
	animTime[State::WeakDamaged] = 0.3f;

	Image* StrongDamageImages = new Image();
	if (FAILED(StrongDamageImages->Init(L"Image/mai/mai_stronghurt_ver3.bmp", 390, 146, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_stronghurt_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongDamaged].push_back(StrongDamageImages);
	animTime[State::StrongDamaged] = 0.3f;

	Image* DefendImages = new Image();
	if (FAILED(DefendImages->Init(L"Image/mai/mai_defend_ver3.bmp", 200, 146, 1, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_defend_ver3", L"경고", MB_OK);
	}
	vImages[State::Defend].push_back(DefendImages);
	animTime[State::Defend] = 1.0f;


	//----------스킬-----------
	Image* skillImages = new Image();
	if (FAILED(skillImages->Init(L"Image/mai/mai_skill4.bmp", 17050, 260, 62, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_skill 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Skill].push_back(skillImages);
	animTime[State::Skill] = 5.0f;


	//----------die-----------
	Image* DeadImage = new Image();
	if (FAILED(DeadImage->Init(L"Image/mai/mai_dead_ver2.bmp", 200 * 4, 160, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"Kyo_Dead 파일 로드 실패", L"경고", MB_OK);
	}
	vImages[State::Dead].push_back(DeadImage);
	animTime[State::Dead] = 1.0f;


	curState = State::Idle;
	frameIdx = 0;
	defaultFlip = flip = false;
	offset = 0;
}


void Mai::Action()
{
	hurtBox = GetRect(position.x - 35 * size, position.y - 105 * size, 70 * size, 105 * size);

	switch (curState)
	{
	case WeakHand:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 1)
		{
			if (flip == false)
			{
				hitBox = GetRect(position.x, position.y - 65 * size, 65 * size, 15 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 65 * size, position.y - 65 * size, 65 * size, 15 * size);

			}
		}

		break;
	case StrongHand:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 3 || frameIdx == 4)
		{
			if (flip == false)
			{
				hitBox = GetRect(position.x, position.y - 70 * size, 75 * size, 17 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 75 * size, position.y - 70 * size, 75 * size, 17 * size);

			}
		}

		break;
	case WeakFoot:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 2 || frameIdx == 3 || frameIdx == 4)
		{
			if (flip == false)
			{
				hitBox = GetRect(position.x, position.y - 85 * size, 50 * size, 22 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 50 * size, position.y - 85 * size, 90 * size, 22 * size);

			}
		}

		break;
	case StrongFoot:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx == 2)
		{
			if (flip == false)
			{
				hitBox = GetRect(position.x, position.y - 105 * size, 50 * size, 22 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 50 * size, position.y - 105 * size, 50 * size, 20 * size);

			}
		}

		break;

	case Skill:
		hitBox = GetRect(0, 0, 0, 0);

		if (frameIdx >= 31 && frameIdx <= 41)
		{
			if (flip == false)
			{
				hitBox = GetRect(position.x, position.y - 105 * size, 200 * size, 105 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 100 * size, position.y - 105 * size, 100 * size, 105 * size);

			}
		}

		if (frameIdx >= 54 && frameIdx <= 60)
		{
			if (flip == false)
			{
				hitBox = GetRect(position.x, position.y - 105 * size, 200 * size, 105 * size);

			}
			else
			{
				hitBox = GetRect(position.x - 200 * size, position.y - 105 * size, 200 * size, 105 * size);

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