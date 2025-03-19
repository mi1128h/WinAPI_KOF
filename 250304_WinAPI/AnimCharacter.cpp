#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

// 캐릭터 초기화 함수
void AnimCharacter::Init()
{

	position = { 0,0 };
	speed = 10;
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

// 자원 해제 함수
void AnimCharacter::Release()
{
    // 모든 상태의 모든 이미지 메모리 해제
    for (auto images : vImages) {
        for (auto i : images) {
            i->Release();   // 이미지 리소스 해제
            delete i;       // 동적 할당 메모리 해제
            i = NULL;       // 포인터 초기화
        }
    }
}

// 업데이트 함수
void AnimCharacter::Update()
{

	Move();

	Animate();

	ProcessInput();

}

// 입력 처리 함수
void AnimCharacter::ProcessInput()
{

	KeyManager* km = KeyManager::GetInstance();
	int deltaX{}, deltaY{};

	bool WeakHand = (km->IsOnceKeyDown('u') or km->IsOnceKeyDown('U'));
	bool StrongHand = (km->IsOnceKeyDown('i') or km->IsOnceKeyDown('I'));
	bool WeakFoot = (km->IsOnceKeyDown('j') or km->IsOnceKeyDown('J'));
	bool StrongFoot = (km->IsOnceKeyDown('k') or km->IsOnceKeyDown('K'));

	switch (curState) {
	case State::Idle:
		if (km->IsOnceKeyDown('a') or km->IsOnceKeyDown('A')) {
			deltaX -= 1;
		}
		if (km->IsOnceKeyDown('d') or km->IsOnceKeyDown('D')) {
			deltaX += 1;
		}
		if (deltaX != 0) SetState(State::Walk);

		if (WeakHand) SetState(State::WeakHand);
		if (StrongHand) SetState(State::StrongHand);
		if (WeakFoot) SetState(State::WeakFoot);
		if (StrongFoot) SetState(State::StrongFoot);
		break;
	case State::Walk:
		if (km->IsStayKeyDown('a') or km->IsStayKeyDown('A')) {
			deltaX -= 1;
		}
		if (km->IsStayKeyDown('d') or km->IsStayKeyDown('D')) {
			deltaX += 1;
		}
		if (deltaX == 0) SetState(State::Idle);

		if (WeakHand) SetState(State::WeakHand);
		if (StrongHand) SetState(State::StrongHand);
		if (WeakFoot) SetState(State::WeakFoot);
		if (StrongFoot) SetState(State::StrongFoot);
		break;
	case State::Dead: case State::WeakHand: case State::StrongHand: case State::WeakFoot: case State::StrongFoot:
		break;
	}

	SetDelta(deltaX, deltaY);

}

// 애니메이션 처리 함수
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

// 렌더링 함수
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

// 이동 처리 함수
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

