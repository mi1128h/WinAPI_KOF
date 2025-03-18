#pragma once
#include "GameObject.h"

enum State {
	Idle,
	Walk,
	Dead,
	Statelength
};

class Image;
class AnimCharacter : public GameObject
{
private:
	FPOINT position;
	float dx, dy;
	float speed;
	int size[2];

	vector<Image*> vImages[State::Statelength];
	State curState;
	int frameIdx;
	bool flip;

public:
	void Init();
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
};

