#include "Kim.h"
#include "Image.h"
#include "CommonFunction.h"

void Kim::Init()
{
	position = { 0,0 };
	speed = 10;
	dx = 0.0f;
	dy = 0.0f;
	hurtBox = { 0,0,0,0 };
	hitBox = { 0,0,0,0 };
	isSuccessHit = false;
	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/Kim/kim_stance.bmp", 256 * 4, 256, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stance 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/Kim/kim_walk.bmp", 256 * 6, 256, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);

	Image* weakHandImages = new Image();
	if (FAILED(weakHandImages->Init(L"Image/Kim/kim_weakhand.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakhand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakHandImages);

	Image* strongHandImages = new Image();
	if (FAILED(strongHandImages->Init(L"Image/Kim/kim_stronghand.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stronghand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongHandImages);

	Image* weakFootImages = new Image();
	if (FAILED(weakFootImages->Init(L"Image/Kim/kim_weakfoot.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakFootImages);

	Image* strongFootImages = new Image();
	if (FAILED(strongFootImages->Init(L"Image/Kim/kim_strongfoot.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongFootImages);

	Image* weakDamageImages = new Image();
	if (FAILED(weakDamageImages->Init(L"Image/Kim/kim_weakdamage.bmp", 256 * 2, 256, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakDamaged].push_back(weakDamageImages);

	Image* StrongDamageImages = new Image();
	if (FAILED(StrongDamageImages->Init(L"Image/Kim/kim_strongdamage.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongDamaged].push_back(StrongDamageImages);

	/*Image* deadImages = new Image();
	if (FAILED(deadImages->Init(L"Image/bluemary_fall.bmp", 256, 256, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_fall 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Dead].push_back(deadImages);*/

	curState = State::Idle;
	frameIdx = 0;
	flip = true;
}

void Kim::Update()
{
	Action();
	Move();
	

	Animate();

	ProcessInput();
}

void Kim::ProcessInput()
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
			if (km->IsStayKeyDown(VK_LEFT)) {
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

void Kim::Render(HDC hdc)
{
	if (frameIdx == -1) return;
	int imagesNum = vImages[curState].size();
	if (imagesNum == 1) {
		vImages[curState][0]->Render(hdc, position.x, position.y, -1, -1, frameIdx, flip);
	}
	else {
		vImages[curState][frameIdx]->Render(hdc, position.x, position.y, -1, -1, 0, flip);
	}
	//RenderRect(hdc, hurtBox.left, hurtBox.top, 112, 208);
	//RenderRect(hdc, hitBox.left, hitBox.top, hitBox.right - hitBox.left, hitBox.bottom - hitBox.top);
}

void Kim::Move()
{
	position.x += dx * speed;
	position.y += dy * speed;
	position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);
	if (dx > 0) flip = true;
	if (dx < 0) flip = false;
}

void Kim::Action()
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


