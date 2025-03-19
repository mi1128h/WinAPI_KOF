#pragma once
#include "GameObject.h"

// 캐릭터 상태 열거형
enum State {
	Idle,
	Walk,
	WeakHand,
	StrongHand,
	WeakFoot,
	StrongFoot,
	Dead,
	Statelength
};

class Image;  // Image 클래스 전방 선언

// 애니메이션 캐릭터 클래스 - GameObject를 상속받음
class AnimCharacter : public GameObject
{
protected:
	FPOINT position;
	float dx, dy;
	float speed;


	vector<Image*> vImages[State::Statelength];  // 각 상태별 이미지 벡터 배열
	State curState;   // 현재 캐릭터 상태
	int frameIdx;     // 현재 애니메이션 프레임 인덱스
	bool flip;        // 좌우 반전 여부

public:
	virtual void Init();          // 초기화 함수 (가상 함수)
	void Release();               // 자원 해제 함수
	void Update();                // 업데이트 함수
	void ProcessInput();          // 입력 처리 함수
	void Animate();               // 애니메이션 업데이트 함수
	void Render(HDC hdc);         // 렌더링 함수
	void Move();                  // 캐릭터 이동 함수

	// 이동 방향 설정 함수
	void SetDelta(int dx, int dy) { this->dx = dx; this->dy = dy; }

	// 현재 위치 반환 함수
	FPOINT GetPos() { return position; }

	// 현재 상태 반환 함수
	State GetState() { return curState; }

	// 상태 설정 함수 - 같은 상태면 무시, 다른 상태면 프레임 초기화
	void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; }
	void ChangeStateToIdle();
};

