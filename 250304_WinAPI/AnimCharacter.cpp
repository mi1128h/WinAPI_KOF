#include <chrono>
#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

using namespace std::chrono;

void AnimCharacter::Init()
{
	position = { SetStartPos() };
	speed = 10;
	dx = 0.0f;
	dy = 0.0f;

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/iori_idle.bmp", 684, 104, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"iori_idle ���� �ε忡 ����", L"���", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"iori_walk ���� �ε忡 ����", L"���", MB_OK);
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
	// �÷��̾� �Ǵ�?
	KeyManager* km = KeyManager::GetInstance();
	int deltaX{}, deltaY{};

	// ������ ������ ����
	steady_clock::time_point lastPressTime_A, lastPressTime_D;
	bool isRunning = false;  // ���� �޸��� ������ Ȯ��

	// ���� �ð� ��������
	auto now = steady_clock::now();

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
            #ifdef ���� ������
			if (km->IsOnceKeyDown('a') or km->IsOnceKeyDown('A')) {
				deltaX -= 1;
			}
			if (km->IsOnceKeyDown('d') or km->IsOnceKeyDown('D')) {
				deltaX += 1;
			}
			if (deltaX != 0) SetState(State::Walk);
            #endif
			if (km->IsOnceKeyDown('a') or km->IsOnceKeyDown('A')) {
				// ù ��° �Է��̶�� �ð� ���
				if (duration_cast<milliseconds>(now - lastPressTime_A).count() < 300) {
					isRunning = true;  // 300ms �̳��� �� ��° �Է� �� �޸���
				}
				lastPressTime_A = now;
				deltaX -= (isRunning ? 5 : 1);  // �޸��� �� ������ �̵�
			}
			if (km->IsOnceKeyDown('d') or km->IsOnceKeyDown('D')) {
				if (duration_cast<milliseconds>(now - lastPressTime_D).count() < 300) {
					isRunning = true;
				}
				lastPressTime_D = now;
				deltaX += (isRunning ? 5 : 1);
			}

			if (deltaX != 0) SetState(isRunning ? State::Run : State::Walk);

			if (P1_WeakHand) SetState(State::WeakHand);
			if (P1_StrongHand) SetState(State::StrongHand);
			if (P1_WeakFoot) SetState(State::WeakFoot);
			if (P1_StrongFoot) SetState(State::StrongFoot);
			if (P1_StrongFoot and P1_WeakFoot) SetState(State::StrongHand); // Ŀ�ǵ�
			break;

		case State::Walk:
            #ifdef �����ڵ�

			if (km->IsStayKeyDown('a') or km->IsStayKeyDown('A')) {
				deltaX -= 1;
			}
			if (km->IsStayKeyDown('d') or km->IsStayKeyDown('D')) {
				deltaX += 1;
			}
			if (deltaX == 0) SetState(State::Idle);
            #endif
			if (km->IsStayKeyDown('a') or km->IsStayKeyDown('A')) {
				deltaX -= (isRunning ? 5 : 1);
			}
			if (km->IsStayKeyDown('d') or km->IsStayKeyDown('D')) {
				deltaX += (isRunning ? 5 : 1);
			}
			if (deltaX == 0) {
				isRunning = false;
				SetState(State::Idle);
			}

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
			if (P2_StrongFoot and P2_WeakFoot) SetState(State::StrongHand); 
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


