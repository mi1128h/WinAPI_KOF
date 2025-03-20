#include <chrono>
#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

using namespace std::chrono;

void AnimCharacter::Init()
{
	position = { 0,0 };
	speed = 10;
	hp = 100;

	dx = 0.0f;
	dy = 0.0f;
	hp = 10.0f;
	accumTime = 0.0f;

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
	
	offset = 0;
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

void AnimCharacter::Update(float elapsedTime)
{
	Move(elapsedTime);

	Animate(elapsedTime);

	ProcessInput();
}

void AnimCharacter::ProcessInput()
{
	KeyManager* km = KeyManager::GetInstance();

	// 현재 플레이어의 키 입력을 감지하여 상태 값 반환
	State keyCommand = km->GetCommand(isPlayer1);
	int deltaX = 0, deltaY = 0;

	switch (curState) {
	case State::Idle:

		if (km->IsLeftKeyDown(isPlayer1)) {
			deltaX -= 1;
		}
		if (km->IsRightKeyDown(isPlayer1)) {
			deltaX += 1;
		}

		if (deltaX != 0) {

			SetState(State::Walk);
		}

		if (keyCommand != -1)
			SetState(keyCommand);

		break;

	case State::Walk: case State::BackWalk:

		if (km->IsLeftKeyDown(isPlayer1)) {
			deltaX -= 1;
		}
		if (km->IsRightKeyDown(isPlayer1)) {
			deltaX += 1;
		}
		if (deltaX == 0) SetState(State::Idle);

		if (keyCommand != -1)
			SetState(keyCommand);
		break;

	case State::Dead: case State::WeakHand: case State::StrongHand: case State::WeakFoot: case State::StrongFoot:
		break;
	}

	SetDelta(deltaX, deltaY);
}



void AnimCharacter::Animate(float elapsedTime)
{
	accumTime += elapsedTime;
	int imagesNum = vImages[curState].size();
	if (imagesNum > 0) {
		// get total frameNum
		int framesNum{ 1 };
		if (imagesNum != 1) {
			framesNum = imagesNum;
		}
		else if (imagesNum == 1) {
			int sn = vImages[curState][0]->GetSpritesNumX() * vImages[curState][0]->GetSpritesNumY();
			framesNum = sn;
		}
		// calculate frameIdx
		int temp = frameIdx;
		int frame = accumTime * framesNum / animTime[curState];
		frameIdx = frame % framesNum;
		if (temp == framesNum - 1 and frameIdx == 0) ChangeStateToIdle();
	}
	else frameIdx = -1;
}

void AnimCharacter::Render(HDC hdc)
{
	if (frameIdx == -1) return;
	int imagesNum = vImages[curState].size();
	if (imagesNum == 1) {
		vImages[curState][0]->RenderCenter(hdc, position.x, position.y, -1, -1, frameIdx, flip, offset);
	}
	else {
		vImages[curState][frameIdx]->RenderCenter(hdc, position.x, position.y, -1, -1, 0, flip, offset);
	}
	// test Ellipse for position
	RenderEllipseAtCenter(hdc, position.x, position.y, 10, 10);
}

void AnimCharacter::Move(float elapsedTime)
{
	position.x += dx * speed * elapsedTime;
	position.y += dy * speed * elapsedTime;
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

void AnimCharacter::SetStartPos()
{
	if (this->GetIsPlayer1()) {
		position = { PLAYER1_POSX, PLAYER_POSY };
	}
	else {
		position = { PLAYER2_POSX, PLAYER_POSY };
	}
}

bool AnimCharacter::SetStartFilp()
{
	if (this->GetIsPlayer1()) return false;
	
	return true;
}


