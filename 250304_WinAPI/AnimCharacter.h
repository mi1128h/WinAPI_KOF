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
	bool player_classification; // �÷��̾� ����


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
	void SetPos(FPOINT Pos) { this->position = Pos; }  //


	void SetHp(float hp) { this->hp = hp; }
	float GetHp() { return hp; }

	State GetState() { return curState; }
	void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; }
	void ChangeStateToIdle();

	FPOINT respawnPlayer();

	inline bool getPlayer_Classification() { return player_classification; }
	inline void setPlayer_Classification(bool player_classification) 
	{this->player_classification = player_classification;}

};

