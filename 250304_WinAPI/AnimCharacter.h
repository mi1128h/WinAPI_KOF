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
	float speed;
	float hp;
	float accumTime;
	float animTime[State::Statelength];

	bool playerClassification; // 플레이어 구분

	RECT hurtBox;
	RECT hitBox;
	bool isSuccessHit;

	vector<Image*> vImages[State::Statelength];
	State curState;
	int frameIdx;
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
	void SetPos(FPOINT Pos) { this->position = Pos; }  //


	void SetHp(float hp) { this->hp = hp; }
	float GetHp() { return hp; }

	State GetState() { return curState; }
	void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; accumTime = 0.0f; }
	void ChangeStateToIdle();

	FPOINT SetStartPos();


	inline bool getPlayer_Classification() { return playerClassification; }
	inline void setPlayer_Classification(bool player_classification) 
	{this->playerClassification = player_classification;}
	bool SetStartFilp();

	RECT GetHurtBox() { return hurtBox; };
	RECT GetHitBox() { return hitBox; };
	bool GetIsSuccessHit() { return isSuccessHit; };

	void SetHurtBox(RECT hurtBox) { this->hurtBox = hurtBox; }
	void SetHitBox(RECT hitBox) { this->hitBox = hitBox; }
	void SetIsSuccessHit(bool isSuccessHit) { this->isSuccessHit = isSuccessHit; }
};

