#pragma once
#include "GameObject.h"

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

class Image;
class AnimCharacter : public GameObject
{
protected:
	FPOINT position;
	float dx, dy;
	float speed;

	vector<Image*> vImages[State::Statelength];
	State curState;
	int frameIdx;
	bool flip;

public:
	virtual void Init();
	void Release();
	void Update();
	void ProcessInput();
	void Animate();
	void Render(HDC hdc);

	void Move();
	void SetDelta(int dx, int dy) { this->dx = dx; this->dy = dy; }

	FPOINT GetPos() { return position; }
	State GetState() { return curState; }
	void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; }
	void ChangeStateToIdle();
};

