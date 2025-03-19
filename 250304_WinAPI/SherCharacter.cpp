#include "SherCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

// 캐릭터 초기화 함수
void SherCharacter::Init()
{
    position = { 0, WINSIZE_Y-200 };  // 초기 위치 설정
    speed = 10;          // 이동 속도 설정
    dx = 0.0f;           // X 방향 이동값 초기화
    dy = 0.0f;           // Y 방향 이동값 초기화

    // 모든 상태별 이미지 벡터 초기화
    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    // 대기(Idle) 상태 이미지 로드
    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"Image/sher_idle_ver2.bmp", 904, 116, 14, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_idle 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    // 걷기(Walk) 상태 이미지 로드
    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"Image/sher_walk.bmp", 960, 117, 12, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_walk 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Walk].push_back(walkImages);

    // 초기 상태 및 프레임 설정
    curState = State::Idle;  // 초기 상태는 대기
    frameIdx = 0;            // 프레임 인덱스 초기화
    flip = false;            // 좌우 반전 없음

    // 캐릭터 크기 계산 (첫 번째 Idle 이미지 기준)
    Image* img = vImages[State::Idle][0];
    size[0] = img->GetWidth() / img->GetSpritesNumX();     // 너비 계산
    size[1] = img->GetHeight() / img->GetSpritesNumY();    // 높이 계산
}








