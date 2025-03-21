#include "Mai.h"
#include "Image.h"
#include "CommonFunction.h"

void Mai::Init()
{
	position = { 100,200 };
	speed = 100;
	dx = 0.0f;
	dy = 0.0f;
	size = 2.0f;
	hp = 10.0f;
	accumTime = 0.0f;

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

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
	animTime[State::Walk] = 1.0f;

	Image* backWalkImages = new Image();
	if (FAILED(backWalkImages->Init(L"Image/mai/mai_backwalk_ver2.bmp", 200 * 6, 164, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_backwalk_ver2", L"경고", MB_OK);
	}
	vImages[State::BackWalk].push_back(backWalkImages);
	animTime[State::BackWalk] = 1.0f;

	Image* DefendImages = new Image();
	if (FAILED(DefendImages->Init(L"Image/mai/mai_defend_ver3.bmp", 200, 146, 1, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_defend_ver2", L"경고", MB_OK);
	}
	vImages[State::Defend].push_back(DefendImages);
	animTime[State::Defend] = 1.0f;

	Image* weakPunchImages = new Image();
	if (FAILED(weakPunchImages->Init(L"Image/mai/mai_weakpunch_ver2.bmp", 200 * 4, 146, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_weakpunch_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakPunchImages);
	animTime[State::WeakHand] = 1.0f;

	Image* strongPunchImages = new Image();
	if (FAILED(strongPunchImages->Init(L"Image/mai/mai_strongpunch_ver2.bmp", 200 * 4, 146, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_strongpunch_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongPunchImages);
	animTime[State::StrongHand] = 1.0f;

	Image* weakKickImages = new Image();
	if (FAILED(weakKickImages->Init(L"Image/mai/mai_weakkick_ver2.bmp", 200 * 6, 178, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_weakkick_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakKickImages);
	animTime[State::WeakFoot] = 1.0f;

	Image* strongKickImages = new Image();
	if (FAILED(strongKickImages->Init(L"Image/mai/mai_strongkick_ver2.bmp", 200 * 6, 178, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_strongkick_ver2 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongKickImages);
	animTime[State::StrongFoot] = 1.0f;

	Image* skillImages = new Image();
	if (FAILED(skillImages->Init(L"Image/mai/mai_skill.bmp", 284 * 27, 260, 27, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"mai_skill 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Skill].push_back(skillImages);
	animTime[State::Skill] = 1.0f;

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


	curState = State::Idle;
	frameIdx = 0;
	defaultFlip = flip = false;
	offset = 10;
}


void Mai::Action()
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