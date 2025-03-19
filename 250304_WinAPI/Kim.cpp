#include "Kim.h"
#include "Image.h"
#include "CommonFunction.h"

void Kim::Init()
{

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* idleImages = new Image();
	if (FAILED(idleImages->Init(L"Image/Kim/kim_idle.bmp", 256 * 4, 256, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stance 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Idle].push_back(idleImages);

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/Kim/kim_walk.bmp", 256 * 6, 256, 6, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_walk 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Walk].push_back(walkImages);

	Image* weakHandImages = new Image();
	if (FAILED(weakHandImages->Init(L"Image/Kim/kim_AAttack.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakhand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakHand].push_back(weakHandImages);

	Image* strongHandImages = new Image();
	if (FAILED(strongHandImages->Init(L"Image/Kim/kim_CAttack.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_stronghand 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongHand].push_back(strongHandImages);

	Image* weakFootImages = new Image();
	if (FAILED(weakFootImages->Init(L"Image/Kim/kim_BAttack.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_weakfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakFoot].push_back(weakFootImages);

	Image* strongFootImages = new Image();
	if (FAILED(strongFootImages->Init(L"Image/Kim/kim_DAttack.bmp", 256 * 5, 256, 5, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongFoot].push_back(strongFootImages);

	Image* deadImages = new Image();
	if (FAILED(deadImages->Init(L"Image/bluemary_fall.bmp", 256, 256, 12, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_fall 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::Dead].push_back(deadImages);

	curState = State::Idle;
	frameIdx = 0;
}

//void Kim::Release()
//{
//	for (auto images : vImages) {
//		for (auto i : images) {
//			i->Release();
//			delete i;
//			i = NULL;
//		}
//	}
//}
//
//void Kim::Update()
//{
//	Move();
//
//	ProcessInput();
//
//	Animate();
//}
//
//void Kim::ProcessInput()
//{
//	KeyManager* km = KeyManager::GetInstance();
//	int deltaX{}, deltaY{};
//	switch (curState) {
//	case State::Idle:
//		if (km->IsOnceKeyDown('a') or km->IsOnceKeyDown('A')) {
//			deltaX -= 1;
//		}
//		if (km->IsOnceKeyDown('d') or km->IsOnceKeyDown('D')) {
//			deltaX += 1;
//		}
//		if (deltaX != 0) SetState(State::Walk);
//		break;
//	case State::Walk:
//		if (km->IsStayKeyDown('a') or km->IsStayKeyDown('A')) {
//			deltaX -= 1;
//		}
//		if (km->IsStayKeyDown('d') or km->IsStayKeyDown('D')) {
//			deltaX += 1;
//		}
//		if (deltaX == 0) SetState(State::Idle);
//		break;
//	case State::Dead:
//		break;
//	}
//
//	SetDelta(deltaX, deltaY);
//}
//
//void Kim::Animate()
//{
//	frameIdx++;
//	int imagesNum = vImages[curState].size();
//	if (imagesNum > 0) {
//		if (imagesNum != 1) {
//			frameIdx %= imagesNum;
//		}
//		else if (imagesNum == 1) {
//			int sn = vImages[curState][0]->GetSpritesNumX() * vImages[curState][0]->GetSpritesNumY();
//			frameIdx %= sn;
//		}
//	}
//	else frameIdx = -1;
//}
//
//void Kim::Render(HDC hdc)
//{
//	if (frameIdx == -1) return;
//	int imagesNum = vImages[curState].size();
//	if (imagesNum == 1) {
//		vImages[curState][0]->Render(hdc, position.x, position.y, size[0], size[1], frameIdx, flip);
//	}
//	else {
//		vImages[curState][frameIdx]->Render(hdc, position.x, position.y, size[0], size[1], 0, flip);
//	}
//}
//
//void Kim::Move()
//{
//	position.x += dx * speed;
//	position.y += dy * speed;
//	position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);
//	if (dx > 0) flip = false;
//	if (dx < 0) flip = true;
//}
