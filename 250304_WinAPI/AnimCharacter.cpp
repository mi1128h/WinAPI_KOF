#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

// 캐릭터 초기화 함수
void AnimCharacter::Init()
{
    position = { 0,0 };  // 초기 위치 설정
    speed = 10;          // 이동 속도 설정
    dx = 0.0f;           // X 방향 이동값 초기화
    dy = 0.0f;           // Y 방향 이동값 초기화

    // 모든 상태별 이미지 벡터 초기화
    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    // 대기(Idle) 상태 이미지 로드
    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"Image/iori_idle.bmp", 684, 104, 9, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"iori_idle 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    // 걷기(Walk) 상태 이미지 로드
    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"Image/iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"iori_walk 파일 로드에 실패", L"경고", MB_OK);
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

// 자원 해제 함수
void AnimCharacter::Release()
{
    // 모든 상태의 모든 이미지 메모리 해제
    for (auto images : vImages) {
        for (auto i : images) {
            i->Release();   // 이미지 리소스 해제
            delete i;       // 동적 할당 메모리 해제
            i = NULL;       // 포인터 초기화
        }
    }
}

// 업데이트 함수
void AnimCharacter::Update()
{
    Move();         // 이동 처리
    ProcessInput(); // 입력 처리
    Animate();      // 애니메이션 처리
}

// 입력 처리 함수
void AnimCharacter::ProcessInput()
{
    KeyManager* km = KeyManager::GetInstance();  // 키 매니저 싱글톤 인스턴스 획득
    int deltaX{}, deltaY{};  // 이동 방향 초기화

    // 현재 상태에 따른 입력 처리
    switch (curState) {
    case State::Idle:  // 대기 상태일 때
        // A키를 눌렀을 때 왼쪽으로 이동
        if (km->IsOnceKeyDown('a') or km->IsOnceKeyDown('A')) {
            deltaX -= 1;
        }
        // D키를 눌렀을 때 오른쪽으로 이동
        if (km->IsOnceKeyDown('d') or km->IsOnceKeyDown('D')) {
            deltaX += 1;
        }
        // X축 이동이 있으면 걷기 상태로 변경
        if (deltaX != 0) SetState(State::Walk);
        break;

    case State::Walk:  // 걷기 상태일 때
        // A키를 누르고 있으면 왼쪽으로 이동
        if (km->IsStayKeyDown('a') or km->IsStayKeyDown('A')) {
            deltaX -= 1;
        }
        // D키를 누르고 있으면 오른쪽으로 이동
        if (km->IsStayKeyDown('d') or km->IsStayKeyDown('D')) {
            deltaX += 1;
        }
        // X축 이동이 없으면 대기 상태로 변경
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::W_punch:  // 약 펀치 상태
        if (km->IsStayKeyDown('u') or km->IsStayKeyDown('U')) {
            deltaX -= 1;
        }

        // X축 이동이 없으면 대기 상태로 변경
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::S_punch:  // 강 펀치 상태일 때
        if (km->IsStayKeyDown('i') or km->IsStayKeyDown('I')) {
            deltaX -= 1;
        }
     
        
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::W_kick:  // 약 킥 상태일 때
        if (km->IsStayKeyDown('j') or km->IsStayKeyDown('J')) {
            deltaX -= 1;
        }
        
        
        // X축 이동이 없으면 대기 상태로 변경
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::S_kick:  // 강 킥 상태일 때
        if (km->IsStayKeyDown('k') or km->IsStayKeyDown('K')) {
            deltaX -= 1;
        }
       
        
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::Dead:  // 사망 상태일 때
        break;  // 아무 처리 없음
    }

    // 이동 방향 설정
    SetDelta(deltaX, deltaY);
}

// 애니메이션 처리 함수
void AnimCharacter::Animate()
{
    frameIdx++;  // 프레임 인덱스 증가

    int imagesNum = vImages[curState].size();  // 현재 상태의 이미지 개수
    if (imagesNum > 0) {
        if (imagesNum != 1) {
            // 여러 이미지로 구성된 애니메이션인 경우
            frameIdx %= imagesNum;  // 이미지 개수에 맞게 인덱스 순환
        }
        else if (imagesNum == 1) {
            // 단일 이미지의 스프라이트 애니메이션인 경우
            int sn = vImages[curState][0]->GetSpritesNumX() * vImages[curState][0]->GetSpritesNumY();  // 총 스프라이트 수 계산
            frameIdx %= sn;  // 스프라이트 수에 맞게 인덱스 순환
        }
    }
    else frameIdx = -1;  // 이미지가 없으면 프레임 인덱스 초기화
}

// 렌더링 함수
void AnimCharacter::Render(HDC hdc)
{
    if (frameIdx == -1) return;  // 유효한 프레임이 없으면 렌더링 중단

    int imagesNum = vImages[curState].size();  // 현재 상태의 이미지 개수
    if (imagesNum == 1) {
        // 단일 이미지인 경우 (스프라이트시트)
        vImages[curState][0]->Render(hdc, position.x, position.y, size[0], size[1], frameIdx, flip);
    }
    else {
        // 여러 이미지인 경우
        vImages[curState][frameIdx]->Render(hdc, position.x, position.y, size[0], size[1], 0, flip);
    }
}

// 이동 처리 함수
void AnimCharacter::Move()
{
    // 위치 업데이트
    position.x += dx * speed;  // X 위치 업데이트
    position.y += dy * speed;  // Y 위치 업데이트

    // Y 위치를 화면 높이 내로 제한
    position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);

    // 이동 방향에 따른 좌우 반전 설정
    if (dx > 0) flip = false;  // 오른쪽으로 이동하면 반전 없음
    if (dx < 0) flip = true;   // 왼쪽으로 이동하면 반전
}