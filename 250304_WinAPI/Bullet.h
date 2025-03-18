#pragma once
#include "GameObject.h"

class Enemy;
class Bullet : public GameObject
{
protected:
	bool isLoaded{};
	FPOINT position{};
	float fireAngle{};
	float speed{};
	float damage{};
	int size{};
	RECT rcCollision{};

	bool guided{};
	Enemy* target{};

public:
	void Init(FPOINT pos, float angle);
	void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Move();
	bool IsLoaded() { return isLoaded; }
	void Fire() { isLoaded = false; }
	FPOINT GetPos() { return position; }
	int GetSize() { return size; }
	void SetLoaded(bool loaded) { isLoaded = loaded; }
	void SetDamage(float d) { damage = d; }
	float GetDamage() { return damage; }
	void SetSpeed(float s) { speed = s; }

	bool IsGuided() { return guided; }
	void SetGuided(bool guidOption) { guided = guidOption; }
	Enemy* GetTarget() { return target; }
	void SetTarget(Enemy* enemy) { target = enemy; }
	void UpdateGuidedAngle();

	virtual void CheckWallCollision();
	void CheckEnemyCollision(Enemy* enemy);

	Bullet();
	~Bullet();
};

class BombBullet : public Bullet
{
protected:
	int countDown{};	// one direction(fireAngle) while countdown
	float angle_360{};	// new direction after countdown

public:
	void SetBombValues(int time, float angle);
	void Update() override;
	void Move() override;
};

class BounceBullet : public Bullet
{
private:
	int bounceNum{};

public:
	void SetBounceNum(int cnt);
	void CheckWallCollision() override;
};

class ConfettiBullet : public BombBullet
{
private:
	int colors[3];
	int lifeTime;

public:
	void SetConfettiValues(int life);
	void Update() override;
	void Render(HDC hdc) override;
};