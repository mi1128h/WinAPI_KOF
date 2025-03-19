#include "AnimBackground.h"
#include "Image.h"

// 배경 클래스 초기화 함수
void AnimBackground::Init()
{
    position = { 0,0 };    // 배경 위치 초기화
    speed = 10;            // 배경 이동 속도 설정

    // 모든 스테이지의 이미지 벡터 초기화
    for (int i = 0; i < Stage::Stagelength; ++i) vImages[i] = {};

    // 배경 이미지 생성 및 로드
    Image* background = new Image();
    if (FAILED(background->Init(L"Image/backGroundAnimation.bmp", 800, 5376, 1, 16, FALSE, FALSE))) {
        MessageBox(g_hWnd, L"backGroundAnimation 파일 로드에 실패", L"경고", MB_OK);
    }

    // 스테이지 1에 배경 이미지 추가
    vImages[Stage::Stage1].push_back(background);

    // 현재 스테이지와 프레임 인덱스 초기화
    curStage = Stage::Stage1;
    frameIdx = -1;  // -1은 아직 애니메이션이 시작되지 않았음을 의미
}

// 자원 해제 함수
void AnimBackground::Release()
{
    // 모든 스테이지의 모든 이미지 메모리 해제
    for (auto images : vImages) {
        for (auto i : images) {
            i->Release();   // 이미지 리소스 해제
            delete i;       // 동적 할당 메모리 해제
            i = NULL;       // 포인터 초기화
        }
    }
}

// 배경 업데이트 함수
void AnimBackground::Update()
{
    Animate();  // 애니메이션 처리
}

// 애니메이션 처리 함수
void AnimBackground::Animate()
{
    frameIdx++;  // 프레임 인덱스 증가

    int size = vImages[curStage].size();  // 현재 스테이지의 이미지 개수
    if (size > 0) {
        if (size != 1) {
            // 여러 이미지로 구성된 애니메이션인 경우
            frameIdx %= size;  // 이미지 개수에 맞게 인덱스 순환
        }
        else if (size == 1) {
            // 단일 이미지의 스프라이트 애니메이션인 경우
            int sn = vImages[curStage][0]->GetSpritesNumX() * vImages[curStage][0]->GetSpritesNumY();  // 총 스프라이트 수 계산
            frameIdx %= sn;  // 스프라이트 수에 맞게 인덱스 순환
        }
    }
    else frameIdx = -1;  // 이미지가 없으면 프레임 인덱스 초기화
}

// 배경 렌더링 함수
void AnimBackground::Render(HDC hdc)
{
    if (frameIdx == -1) return;  // 유효한 프레임이 없으면 렌더링 중단

    int size = vImages[curStage].size();  // 현재 스테이지의 이미지 개수
    if (size == 1)
        // 단일 이미지인 경우, 윈도우 크기에 맞게 스프라이트 렌더링
        vImages[curStage][0]->Render(hdc, position.x, position.y, WINSIZE_X, WINSIZE_Y, frameIdx);
    // 여러 이미지인 경우에 대한 처리는 없음 (코드에서 생략됨)
}
