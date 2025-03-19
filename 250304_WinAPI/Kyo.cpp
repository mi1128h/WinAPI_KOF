#include "Kyo.h"
#include "Image.h"
#include "config.h"
#include "CommonFunction.h"

void Kyo::Init()
{
    position = { 0,100 };
    speed = 10;
    dx = 0.0f;
    dy = 0.0f;

    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"ImageKyo/Kyo_Idle.bmp", 750, 117, 10, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_idle 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"ImageKyo/Kyo_Walk.bmp", 360, 126, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_walk 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Walk].push_back(walkImages);

    Image* strongKickImages = new Image();
    if (FAILED(strongKickImages->Init(L"ImageKyo/Kyo_weakPunch.bmp", 928, 116, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_strongKick 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongKick].push_back(strongKickImages);

    //Image* strongKickImages = new Image();
    //if (FAILED(strongKickImages->Init(L"ImageKyo/Kyo_weakPunch.bmp", 928, 116, 8, 1, true, RGB(255, 0, 255)))) {
    //    MessageBox(g_hWnd, L"kyo_strongKick 파일 로드에 실패", L"경고", MB_OK);
    //}
    //vImages[State::StrongKick].push_back(strongKickImages);



    curState = State::Idle;
    frameIdx = 0;
    flip = false;

    Image* img = vImages[State::Idle][0];
    size[0] = img->GetWidth() / img->GetSpritesNumX();
    size[1] = img->GetHeight() / img->GetSpritesNumY();
}

void Kyo::Release()
{
    for (auto images : vImages) {
        for (auto i : images) {
            i->Release();
            delete i;
            i = NULL;
        }
    }
}

void Kyo::Update()
{
    Move();
    ProcessInput();
    Animate();
}

void Kyo::Render(HDC hdc)
{
    if (frameIdx == -1) return;
    int imagesNum = vImages[curState].size();
    if (imagesNum == 1) {
        vImages[curState][0]->Render(hdc, position.x, position.y, size[0], size[1], frameIdx, flip);
    }
    else {
        vImages[curState][frameIdx]->Render(hdc, position.x, position.y, size[0], size[1], 0, flip);
    }
}


void Kyo::ProcessInput()
{
    KeyManager* km = KeyManager::GetInstance();
    int deltaX{}, deltaY{};
    switch (curState) {
    case State::Idle:
        if (km->IsOnceKeyDown('A')) deltaX -= 1;
        if (km->IsOnceKeyDown('D')) deltaX += 1;
        if (km->IsOnceKeyDown('I')) SetState(State::StrongKick);
        if (deltaX != 0) SetState(State::Walk);
        break;
    case State::Walk:
        if (km->IsStayKeyDown('A')) deltaX -= 1;
        if (km->IsStayKeyDown('D')) deltaX += 1;
        if (km->IsOnceKeyDown('I')) SetState(State::StrongKick);
        if (deltaX == 0) SetState(State::Idle);
        break;
    case State::StrongKick:
        if (frameIdx == vImages[State::StrongKick][0]->GetSpritesNumX() * vImages[State::StrongKick][0]->GetSpritesNumY() - 1) {
            SetState(State::Idle);
        }
        break;
    case State::Dead:
        break;
    }
    SetDelta(deltaX, deltaY);
}





