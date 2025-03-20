#include <chrono>
#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"
#include <string.h>

using namespace std::chrono;

void AnimCharacter::Init()
{
	position = { SetStartPos() };
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
	flip = SetStartFilp();
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
	KeyManager* km2 = KeyManager::GetInstance();
	int deltaX{}, deltaY{};

	// 더블탭 감지용 변수
	steady_clock::time_point lastPressTime_A, lastPressTime_D;
	bool isRunning = false;  // 현재 달리는 중인지 확인

	// 현재 시간 가져오기
	auto now = steady_clock::now();

	bool P1_WeakHand = (km->IsOnceKeyDown('U'));
	bool P1_StrongHand = (km->IsOnceKeyDown('I'));
	bool P1_WeakFoot = (km->IsOnceKeyDown('J'));
	bool P1_StrongFoot = (km->IsOnceKeyDown('K'));

	bool P2_WeakHand = (km2->IsOnceKeyDown(VK_NUMPAD4));
	bool P2_StrongHand = (km2->IsOnceKeyDown(VK_NUMPAD5));
	bool P2_WeakFoot = (km2->IsOnceKeyDown(VK_NUMPAD1));
	bool P2_StrongFoot = (km2->IsOnceKeyDown(VK_NUMPAD2));

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

			if (P1_StrongFoot and P1_WeakFoot) SetState(State::StrongHand); // 커맨드
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

			if (P1_StrongFoot and P1_WeakFoot) SetState(State::StrongHand);
			break;
		case State::Dead: case State::WeakHand: case State::StrongHand: case State::WeakFoot: case State::StrongFoot:
			break;
		}

		SetDelta(deltaX, deltaY);
	}

	else {
		switch (curState) {
		case State::Idle:
			if (km2->IsStayKeyDown(VK_LEFT)) {
				deltaX -= 1;
			}
			if (km2->IsStayKeyDown(VK_RIGHT)) {
				deltaX += 1;
			}
			if (deltaX != 0) SetState(State::Walk);

			if (P2_WeakHand) SetState(State::WeakHand);
			if (P2_StrongHand) SetState(State::StrongHand);
			if (P2_WeakFoot) SetState(State::WeakFoot);
			if (P2_StrongFoot) SetState(State::StrongFoot);

			if (P2_StrongFoot and P2_WeakFoot) SetState(State::StrongHand); 
			break;

		case State::Walk:
			if (km2->IsStayKeyDown(VK_LEFT) ) {
				deltaX -= 1;
			}
			if (km2->IsStayKeyDown(VK_RIGHT)) {
				deltaX += 1;
			}
			if (deltaX == 0) SetState(State::Idle);

			if (P2_WeakHand) SetState(State::WeakHand);
			if (P2_StrongHand) SetState(State::StrongHand);
			if (P2_WeakFoot) SetState(State::WeakFoot);
			if (P2_StrongFoot) SetState(State::StrongFoot);

			if (P2_StrongFoot and P2_WeakFoot) SetState(State::StrongHand); 
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

FPOINT AnimCharacter::SetStartPos()
{
	FPOINT respawnpos;
	if (this->getPlayer_Classification()) {
		respawnpos = { PLAYER1_POSX, PLAYER_POSY };
	}
	else {
		respawnpos = { PLAYER2_POSX, PLAYER_POSY };
	}

	return respawnpos;
}

bool AnimCharacter::SetStartFilp()
{
	if (this->getPlayer_Classification()) return false;
	
	return true;
}


