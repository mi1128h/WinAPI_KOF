#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

void AnimCharacter::Init()
{
	position = { respawnPlayer() };
	speed = 10;
	hp = 100;

	dx = 0.0f;
	dy = 0.0f;

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/iori_idle.bmp", 684, 104, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"iori_idle 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"iori_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);

	curState = State::Idle;
	frameIdx = 0;
	flip = false;
}

void AnimCharacter::Release()
{
	for (auto images : vImages) {
		for (auto i : images) {
			i->Release();
			delete i;
			i = NULL;
		}
	}
}

void AnimCharacter::Update()
{
	Move();

	Animate();

	ProcessInput();
}

void AnimCharacter::ProcessInput()
{
	// 플레이어 판단?
	KeyManager* km = KeyManager::GetInstance();
	int deltaX{}, deltaY{};

	bool P1_WeakHand = (km->IsOnceKeyDown('u') or km->IsOnceKeyDown('U'));
	bool P1_StrongHand = (km->IsOnceKeyDown('i') or km->IsOnceKeyDown('I'));
	bool P1_WeakFoot = (km->IsOnceKeyDown('j') or km->IsOnceKeyDown('J'));
	bool P1_StrongFoot = (km->IsOnceKeyDown('k') or km->IsOnceKeyDown('K'));

	bool P2_WeakHand = (km->IsOnceKeyDown(VK_NUMPAD4));
	bool P2_StrongHand = (km->IsOnceKeyDown(VK_NUMPAD5));
	bool P2_WeakFoot = (km->IsOnceKeyDown(VK_NUMPAD1));
	bool P2_StrongFoot = (km->IsOnceKeyDown(VK_NUMPAD2));

	if (this->getPlayer_Classification()) {
		switch (curState) {
		case State::Idle:
			if (km->IsOnceKeyDown('a') or km->IsOnceKeyDown('A')) {
				deltaX -= 1;
			}
			if (km->IsOnceKeyDown('d') or km->IsOnceKeyDown('D')) {
				deltaX += 1;
			}
			if (deltaX != 0) SetState(State::Walk);

			if (P1_WeakHand) SetState(State::WeakHand);
			if (P1_StrongHand) SetState(State::StrongHand);
			if (P1_WeakFoot) SetState(State::WeakFoot);
			if (P1_StrongFoot) SetState(State::StrongFoot);
			break;

		case State::Walk:
			if (km->IsStayKeyDown('a') or km->IsStayKeyDown('A')) {
				deltaX -= 1;
			}
			if (km->IsStayKeyDown('d') or km->IsStayKeyDown('D')) {
				deltaX += 1;
			}
			if (deltaX == 0) SetState(State::Idle);

			if (P1_WeakHand) SetState(State::WeakHand);
			if (P1_StrongHand) SetState(State::StrongHand);
			if (P1_WeakFoot) SetState(State::WeakFoot);
			if (P1_StrongFoot) SetState(State::StrongFoot);
			break;
		case State::Dead: case State::WeakHand: case State::StrongHand: case State::WeakFoot: case State::StrongFoot:
			break;
		}

		SetDelta(deltaX, deltaY);
	}

	else {
		switch (curState) {
		case State::Idle:
			if (km->IsStayKeyDown(VK_LEFT)) {
				deltaX -= 1;
			}
			if (km->IsStayKeyDown(VK_RIGHT)) {
				deltaX += 1;
			}
			if (deltaX != 0) SetState(State::Walk);

			if (P2_WeakHand) SetState(State::WeakHand);
			if (P2_StrongHand) SetState(State::StrongHand);
			if (P2_WeakFoot) SetState(State::WeakFoot);
			if (P2_StrongFoot) SetState(State::StrongFoot);
			break;

		case State::Walk:
			if (km->IsStayKeyDown(VK_LEFT) ) {
				deltaX -= 1;
			}
			if (km->IsStayKeyDown(VK_RIGHT)) {
				deltaX += 1;
			}
			if (deltaX == 0) SetState(State::Idle);

			if (P2_WeakHand) SetState(State::WeakHand);
			if (P2_StrongHand) SetState(State::StrongHand);
			if (P2_WeakFoot) SetState(State::WeakFoot);
			if (P2_StrongFoot) SetState(State::StrongFoot);
			break;
		case State::Dead: case State::WeakHand: case State::StrongHand: case State::WeakFoot: case State::StrongFoot:
			break;
		}

		SetDelta(deltaX, deltaY);
	}
}

void AnimCharacter::Animate()
{
	frameIdx++;
	int imagesNum = vImages[curState].size();
	if (imagesNum > 0) {
		int framesNum{ 1 };
		if (imagesNum != 1) {
			framesNum = imagesNum;
		}
		else if (imagesNum == 1) {
			int sn = vImages[curState][0]->GetSpritesNumX() * vImages[curState][0]->GetSpritesNumY();
			framesNum = sn;
		}
		if (frameIdx == framesNum) ChangeStateToIdle();
		frameIdx %= framesNum;
	}
	else frameIdx = -1;
}

void AnimCharacter::Render(HDC hdc)
{
	if (frameIdx == -1) return;
	int imagesNum = vImages[curState].size();
	if (imagesNum == 1) {
		vImages[curState][0]->Render(hdc, position.x, position.y, -1, -1, frameIdx, flip);
	}
	else {
		vImages[curState][frameIdx]->Render(hdc, position.x, position.y, -1, -1, 0, flip);
	}
}

void AnimCharacter::Move()
{
	position.x += dx * speed;
	position.y += dy * speed;
	position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);
	if (dx > 0) flip = false;
	if (dx < 0) flip = true;
}

void AnimCharacter::ChangeStateToIdle()
{
	if (curState != State::Idle and curState != State::Walk and curState != State::Dead) {
		SetState(State::Idle);
	}
}

FPOINT AnimCharacter::respawnPlayer()
{
	FPOINT respawnpos;
	if (this->getPlayer_Classification()) {
		respawnpos = { 100, 340 };
	}
	else {
		respawnpos = { 900, 340 };
	}

	return respawnpos;
}
