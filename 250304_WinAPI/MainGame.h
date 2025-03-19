#pragma once
#include "GameObject.h"

class Tank;
class Enemy;
class RoundManager;
class Image;
class AnimCharacter;
class SherCharacter;
class AnimBackground;
class MainGame : public GameObject  // 'GameObject'클래스를 상속받아 MainGame 생성
{
private:
    HDC hdc{};            // 현재 장치 컨텍스트 (그리기용)
    PAINTSTRUCT ps{};      // 페인트(그리기) 정보 저장
    HANDLE hTimer{}, hTimer2; // 타이머 핸들 (게임 이벤트 제어)

    int mousePosX{}, mousePosY{}; // 마우스 위치 저장
    wchar_t szText[128]{};        // 화면에 표시할 텍스트

    Tank* tank;           // 플레이어가 조종하는 탱크 객체
    vector<Enemy*> enemies; // 적 캐릭터 리스트 (동적 할당)
    int nDeadEnemies;     // 처치한 적 수 카운트

    RoundManager* roundManager; // 게임의 라운드를 관리하는 객체

    Image* backBuffer;        // 백버퍼 (화면 깜빡임 방지용)
    AnimCharacter* iori;      // 애니메이션 캐릭터 객체 (이오리)
    SherCharacter* sher;
    AnimBackground* background; // 애니메이션 배경 객체

public:
    // 게임 초기화 함수 (객체 생성, 초기 설정)
    void Init();

    // 게임 종료 시 메모리 해제 (객체 삭제)
    void Release();

    // 게임의 상태 업데이트 (물리 연산, AI 동작 등)
    void Update();

    // 화면 렌더링 (그리기)
    void Render(HDC hdc);

    // 디버깅 정보 또는 추가 UI 렌더링
    void RenderInfo(HDC hdc);

    // 새로운 적을 생성하는 함수
    void CreateEnemy();

    // 유도탄의 목표를 설정하는 함수
    void SetGuidedBulletsTarget();

    // 게임을 재시작하는 함수
    void RestartGame();

    // 게임의 메인 윈도우 프로시저 (입력 처리)
    LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

    // 생성자 (객체 초기화)
    MainGame();

    // 소멸자 (동적 메모리 해제)
    ~MainGame();
};

