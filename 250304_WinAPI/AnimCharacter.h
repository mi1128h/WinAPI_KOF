#pragma once
#include "GameObject.h"

enum State {
	Idle,
	Run,
	BackWalk,
	Walk,

	WeakHand,
	StrongHand,
	WeakFoot,
	StrongFoot,

	WeakDamaged,
	StrongDamaged,
	
	Dead,
	Statelength,
};

class Image;
class AnimCharacter : public GameObject
{
protected:
	FPOINT position;
	float dx, dy;
	float size;
	float speed;
	float hp;
	float stamina; 

	float accumTime;
	float animTime[State::Statelength];

	bool isPlayer1; 

	RECT hurtBox = { 0,0,0,0 };
	RECT hitBox = { 1,1,1,1 };
	bool isSuccessHit;

	vector<Image*> vImages[State::Statelength];
	State curState;
	int frameIdx;
	bool defaultFlip;
	bool flip;
	int offset;

public:
	virtual void Init();
	void Release();
	void Update(float elapsedTime);
	void ProcessInput();
	void Animate(float elpasedTime);
	void Render(HDC hdc);

	virtual void Action() = 0;

	void Move(float elapsedTime);
	void SetDelta(int dx, int dy) { this->dx = dx; this->dy = dy; }
	


	int GetFrameIdx() { return frameIdx; }

	FPOINT GetPos() { return position; }
	void SetPos(FPOINT Pos) { this->position = Pos; }  


	void SetHp(float hp) { this->hp = hp; }
	float GetHp() { return hp; }
	float GetStamina() { return stamina; }
	
	State GetState() { return curState; }
	void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; accumTime = 0.0f; }
	void ChangeStateToIdle();

	void SetStartPos();


	inline bool GetIsPlayer1() { return isPlayer1; }
	inline void SetPlayerClassification(bool playerClassification) 
	{this->isPlayer1 = playerClassification;}

	bool SetStartFilp();

	RECT GetHurtBox() { return hurtBox; };
	RECT GetHitBox() { return hitBox; };
	bool GetIsSuccessHit() { return isSuccessHit; };

	void SetHurtBox(RECT hurtBox) { this->hurtBox = hurtBox; }
	void LookRight(bool Isright);
	void SetHitBox(RECT hitBox) { this->hitBox = hitBox; }
	void SetIsSuccessHit(bool isSuccessHit) { this->isSuccessHit = isSuccessHit; }

	// 메모리 누수 방지
	virtual ~AnimCharacter(){};
};

