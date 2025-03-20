#include <chrono>
#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

using namespace std::chrono;

void AnimCharacter::Init()
{
	position = { 0,0 };
	speed = 10;

	dx = 0.0f;
	dy = 0.0f;
	size = 2.0f;
	hp = 10.0f;
	accumTime = 0.0f;


	isSuccessHit = false;

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/iori_idle.bmp", 684, 104, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"iori_idle ?�일 로드???�패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"iori_walk ?�일 로드???�패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);

	curState = State::Idle;
	frameIdx = 0;
	
	offset = 0;

	defaultFlip = flip = false;

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
	Action();
	Move(elapsedTime);

	Animate(elapsedTime);

	ProcessInput();
}

void AnimCharacter::ProcessInput()
{
	KeyManager* km = KeyManager::GetInstance();

	// ?�재 ?�레?�어?????�력??감�??�여 ?�태 �?반환
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
			State moveState = State::Walk;
			if (deltaX > 0) {
				moveState = (defaultFlip == flip) ? State::Walk : State::BackWalk;
			}
			else {
				moveState = (defaultFlip == flip) ? State::BackWalk : State::Walk;
			}

			SetState(moveState);
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

		if (curState == State::Dead and temp == framesNum - 1) {
			frameIdx = temp;
		}
	}
	else frameIdx = -1;
}

void AnimCharacter::Render(HDC hdc)
{
	if (frameIdx == -1) return;
	int imagesNum = vImages[curState].size();
	if (imagesNum == 1) {
		vImages[curState][0]->RenderCenter(hdc, position.x, position.y, size, size, frameIdx, flip, offset);
	}
	else if (imagesNum > 1) {
		vImages[curState][frameIdx]->RenderCenter(hdc, position.x, position.y, size, size, 0, flip, offset);
	}
	// test Ellipse for position
	RenderEllipseAtCenter(hdc, position.x, position.y, 10, 10);

	RenderRect(hdc, hurtBox.left, hurtBox.top, hurtBox.right - hurtBox.left, hurtBox.bottom - hurtBox.top);
	RenderRect(hdc, hitBox.left, hitBox.top, hitBox.right - hitBox.left, hitBox.bottom - hitBox.top);
}

void AnimCharacter::Move(float elapsedTime)
{
	position.x += dx * speed * elapsedTime;
	position.y += dy * speed * elapsedTime;
	position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);
}

void AnimCharacter::ChangeStateToIdle()
{
	if (curState != State::Idle and
		curState != State::Walk and curState != State::BackWalk and
		curState != State::Dead) {
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

void AnimCharacter::LookRight(bool Isright)
{
	bool temp = flip;
	if (Isright) flip = defaultFlip;
	else flip = !defaultFlip;

	if (temp != flip) {
		if (curState == State::Walk) curState = State::BackWalk;
		else if (curState == State::BackWalk) curState = State::Walk;
	}
}


