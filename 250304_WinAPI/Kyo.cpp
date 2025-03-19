#include "Kyo.h"
#include "Image.h"
#include "config.h"
#include "CommonFunction.h"

void Kyo::Init()
{
    position = { respawnPlayer() };
    speed = 10;
    dx = 0.0f;
    dy = 0.0f;

    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"Image/ImageKyo/Kyo_Idle.bmp", 750, 117, 10, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_idle 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"Image/ImageKyo/Kyo_Walk.bmp", 360, 126, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_walk 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Walk].push_back(walkImages);


    Image* strongPunchImages = new Image();
    if (FAILED(strongPunchImages->Init(L"Image/ImageKyo/Kyo_strongPunch.bmp", 928, 116, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_strongPunch 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongHand].push_back(strongPunchImages); 
    
    
    Image* weakPunchImages = new Image();
    if (FAILED(weakPunchImages->Init(L"Image/ImageKyo/Kyo_weakPunch.bmp", 530, 116, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_weakPunch 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::WeakHand].push_back(weakPunchImages);


    Image* strongKickImages = new Image();
    if (FAILED(strongKickImages->Init(L"Image/ImageKyo/Kyo_strongKick.bmp", 1463, 127, 11, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_strongKick 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongFoot].push_back(strongKickImages);

    Image* weakKickImages = new Image();
    if (FAILED(weakKickImages->Init(L"Image/ImageKyo/Kyo_weakKick.bmp", 1413, 128, 9, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_weakKick 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::WeakFoot].push_back(weakKickImages);



    curState = State::Idle;
    frameIdx = 0;
    flip = false;
}

