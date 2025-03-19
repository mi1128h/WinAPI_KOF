#include "AnimBackground.h"
#include "Image.h"

void AnimBackground::Init()
{
	position = { 0,0 };
	speed = 10;

	for (int i = 0; i < Stage::Stagelength; ++i) vImages[i] = {};

	Image* background = new Image();
	if (FAILED(background->Init(L"Image/backGroundAnimation.bmp", 800, 5376, 1, 16, FALSE, FALSE))) {
		MessageBox(g_hWnd, L"backGroundAnimation ���� �ε忡 ����", L"���", MB_OK);
	}

	vImages[Stage::Stage1].push_back(background);
	curStage = Stage::Stage1;
	frameIdx = -1;

	accumTime = 0.0f;
	animTime = 2.0f;
}

void AnimBackground::Release()
{
	for (auto images : vImages) {
		for (auto i : images) {
			i->Release();
			delete i;
			i = NULL;
		}
	}
}

void AnimBackground::Update(float elapsedTime)
{
	Animate(elapsedTime);
}

void AnimBackground::Animate(float elapsedTime)
{
	accumTime += elapsedTime;
	int size = vImages[curStage].size();
	if (size > 0) {
		// get total frameNum
		int framesNum{ 1 };
		if (size != 1) {
			framesNum = size;
		}
		else if (size == 1) {
			int sn = vImages[curStage][0]->GetSpritesNumX() * vImages[curStage][0]->GetSpritesNumY();
			framesNum = sn;
		}
		// calculate frameIdx
		int frame = accumTime * framesNum / animTime;
		frameIdx = frame % framesNum;
	}
	else frameIdx = -1;
}

void AnimBackground::Render(HDC hdc)
{
	if (frameIdx == -1) return;
	int size = vImages[curStage].size();
	if (size == 1)
		vImages[curStage][0]->Render(hdc, position.x, position.y, WINSIZE_X, WINSIZE_Y, frameIdx);
}
