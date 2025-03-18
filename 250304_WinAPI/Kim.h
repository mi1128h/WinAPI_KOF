#pragma once
#include "AnimCharacter.h"

class Kim : public AnimCharacter
{


public:
	virtual void Init();
	/*void Release();
	void Update();
	void ProcessInput();
	void Animate();
	void Render(HDC hdc);

	void Move();*/
	// void SetDelta(int dx, int dy) { this->dx = dx; this->dy = dy; }

	// FPOINT GetPos() { return position; }
	// State GetState() { return curState; }
	// void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; }
};

