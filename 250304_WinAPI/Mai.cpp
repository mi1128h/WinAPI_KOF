#include "Mai.h"
#include "Image.h"
#include "config.h"
#include "CommonFunction.h"

void Mai::Init()
{
    position = { 0,0 };
    speed = 10;
    dx = 0.0f;
    dy = 0.0f;

    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"Image/mai/Mai_Endle_ver2.bmp", 1155, 116, 12, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Mai_Endle_ver2 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"Image/mai/Mai_Smove_Front_ver2.bmp", 735, 116, 6, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Mai_Smove_Front_ver2 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Walk].push_back(walkImages);


    Image* strongPunchImages = new Image();
    if (FAILED(strongPunchImages->Init(L"Image/mai/Mai_Spunch_ver2.bmp", 551, 125, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Mai_Spunch_ver2 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongHand].push_back(strongPunchImages);


    Image* weakPunchImages = new Image();
    if (FAILED(weakPunchImages->Init(L"Image/mai/Mai_Wpunch_ver2.bmp", 618, 116, 4, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Mai_Wpunch_ver2 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::WeakHand].push_back(weakPunchImages);


    Image* strongKickImages = new Image();
    if (FAILED(strongKickImages->Init(L"Image/mai/Mai_Highkick_ver2.bmp", 655, 125, 6, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Mai_Highkick_ver2 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongFoot].push_back(strongKickImages);

    Image* weakKickImages = new Image();
    if (FAILED(weakKickImages->Init(L"Image/mai/Mai_Middlekick_ver2.bmp", 755, 125, 6, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Mai_Middlekick_ver2 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::WeakFoot].push_back(weakKickImages);



    curState = State::Idle;
    frameIdx = 0;
    flip = SetStartFilp();
}
