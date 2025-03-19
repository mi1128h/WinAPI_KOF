#pragma once
#include "AnimCharacter.h"

class Kim : public AnimCharacter
{
private:

	RECT hurtBox;
	RECT hitBox;

public:
	void Init();

	//void Release();
	void Update();
	void ProcessInput();
	//void Animate();
	void Render(HDC hdc);
	
	void Move();
	void Action();
	// void SetDelta(int dx, int dy) { this->dx = dx; this->dy = dy; }

	// FPOINT GetPos() { return position; }
	// State GetState() { return curState; }
	// void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; }
	RECT GetHurtBox() { return hurtBox; };
	RECT GetHitBox() { return hitBox; };
};


