#pragma once  
#include "config.h"  

// 게임 스테이지 열거형
enum Stage {
    Stage1,       // 첫 번째 스테이지
    Stagelength   // 스테이지 총 개수
};

class Image;  // Image 클래스에 대한 전방 선언
class AnimCharacter;  // AnimCharacter 클래스에 대한 전방 선언

// 애니메이션 배경 클래스
class AnimBackground
{
private:
    FPOINT position;  // 배경의 위치 (부동 소수점 좌표)
    float speed;      // 배경 이동 속도
    vector<Image*> vImages[Stage::Stagelength];  // 각 스테이지별 배경 이미지 벡터 배열
    Stage curStage;   // 현재 스테이지
    int frameIdx;     // 현재 애니메이션 프레임 인덱스
    AnimCharacter* focusTarget;  // 배경이 따라다닐 캐릭터 포인터 (예: 카메라 타겟)

public:
    void Init();      // 초기화 함수
    void Release();   // 자원 해제 함수
    void Update();    // 업데이트 함수
    void Animate();   // 애니메이션 업데이트 함수
    void Render(HDC hdc);  // 배경 렌더링 함수

    // 배경 위치 반환 함수
    FPOINT GetPos() { return position; }

    // 현재 스테이지 반환 함수
    Stage GetStage() { return curStage; }

    // 스테이지 설정 함수
    void SetStage(Stage stage) { curStage = stage; }
};

