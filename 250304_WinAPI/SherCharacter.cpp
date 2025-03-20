#include "SherCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

// 캐릭터 초기화 함수
void SherCharacter::Init()
{
    position = { 0,0 };  // 초기 위치 설정
    speed = 10;          // 이동 속도 설정
    dx = 0.0f;           // X 방향 이동값 초기화
    dy = 0.0f;           // Y 방향 이동값 초기화

    // 모든 상태별 이미지 벡터 초기화
    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    // 대기(Idle) 상태 이미지 로드
    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"Image/Sherme/sher_idle_ver2.bmp", 904, 116, 14, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_idle 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    // 걷기(Walk) 상태 이미지 로드
    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"Image/Sherme/sher_walk.bmp", 960, 117, 12, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_walk 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Walk].push_back(walkImages);

    // 약펀치 공격
    Image* weakPunchImages = new Image();
    if (FAILED(weakPunchImages->Init(L"Image/Sherme/sher_weak_punch_attack_F6_ver2.bmp", 1070, 117, 6, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_punch_attack_F6 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::WeakHand].push_back(weakPunchImages);

    // 강펀치 공격
    Image* strongPunchImages = new Image();
    if (FAILED(strongPunchImages->Init(L"Image/Sherme/sher_strong_punch_attack_F12.bmp", 2135, 148, 12, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_strong_attack_F12 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongHand].push_back(strongPunchImages);

    // 약킥 공격
    Image* weakKickImages = new Image();
    if (FAILED(weakKickImages->Init(L"Image/Sherme/sher_weak_kick_attack_F9_ver3.bmp", 1568, 120, 9, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_kick_attack_F12 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::WeakFoot].push_back(weakKickImages);

    // 강킥 공격
    Image* strongKickImages = new Image();
    if (FAILED(strongKickImages->Init(L"Image/Sherme/sher_strong_kick_attack_F11_ver2.bmp", 1397, 97, 11, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_strong_kick_attack_F11 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongFoot].push_back(strongKickImages);

    // 죽음
    Image* deadImages = new Image();
    if (FAILED(deadImages->Init(L"Image/Sherme/sher_dead_F5.bmp", 270, 96, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"bluemary_fall 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Dead].push_back(deadImages);

    // 캐릭터 크기 계산 (첫 번째 Idle 이미지 기준)
    curState = State::Idle;
    frameIdx = 0;
    flip = SetStartFilp();
}








