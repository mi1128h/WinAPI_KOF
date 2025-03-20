#pragma once
#include "AnimCharacter.h"

class Kim : public AnimCharacter
{
private:

	RECT hurtBox;
	RECT hitBox;
	bool isSuccessHit;

public:
	void Init();

	//void Release();
	
	void Move(float elapsedTime);
	void Action();
	// void SetDelta(int dx, int dy) { this->dx = dx; this->dy = dy; }

	// FPOINT GetPos() { return position; }
	// State GetState() { return curState; }
	// void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; }
	RECT GetHurtBox() { return hurtBox; };
	RECT GetHitBox() { return hitBox; };
	bool GetIsSuccessHit(){ return isSuccessHit; };

	void SetHurtBox(RECT hurtBox) { this->hurtBox = hurtBox; }
	void SetHitBox(RECT hitBox) { this->hitBox = hitBox; }
	void SetIsSuccessHit(bool isSuccessHit) { this->isSuccessHit = isSuccessHit; }
};


