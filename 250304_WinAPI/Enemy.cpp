#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Bullet.h"


vector<Bullet*> Enemy::vBullets = {};
int Enemy::nLoadedBullets = 0;

void Enemy::Init(Tank* tank)
{
	position.x = uid_0_WINSIZEX(dre);
	position.y = 5;
	target = tank;
	hp = 0;
	size = 20;
	speed = 10;
	damage = 10;
	bulletsNum = 0;
	fireInterval = 0;
	elapsedFireTime = 0;
}

void Enemy::SetValuesByRound(float hp, int maxBulletNum, float speed, float size, int fireSpeed, float bulletSpeed)
{
	this->hp = hp;
	this->bulletsNum = maxBulletNum;
	this->speed = speed;
	this->size = size;
	this->fireInterval = fireSpeed;
	this->elapsedFireTime = fireSpeed / 2;
	this->bulletSpeed = bulletSpeed;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	if (hp <= 0) return;

	Move();
	elapsedFireTime++;
	elapsedFireTime %= fireInterval;
	if (elapsedFireTime == 0) {
		Fire();
	}
}

void Enemy::Render(HDC hdc)
{
	if (hp <= 0) return;
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	RenderEllipseAtCenter(hdc, position.x, position.y, size, size);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void Enemy::Move()
{
	float moveAngle = GetAngle(position, target->GetPos());

	position.x += cosf(TORADIAN(moveAngle)) * speed;
	position.y -= sinf(TORADIAN(moveAngle)) * speed;
}

void Enemy::Fire()
{
	if (bulletsNum <= 0) return;
	float angle = GetAngle(position, target->GetPos());
	if (nLoadedBullets > 0) {
		for (int i = 0; i < vBullets.size(); ++i) {
			if (vBullets[i]->IsLoaded()) {
				vBullets[i]->Init(position, angle);
				vBullets[i]->SetSpeed(bulletSpeed);
				vBullets[i]->Fire();
				nLoadedBullets--;
				break;
			}
		}
	}
	else {
		Bullet* bullet = new Bullet;
		bullet->Init(position, angle);
		bullet->SetSpeed(bulletSpeed);
		bullet->Fire();
		vBullets.push_back(bullet);
	}

	bulletsNum--;
}

void Enemy::ReleaseBullets()
{
	for (auto b : vBullets)
		if (b) delete b;
}

void Enemy::UpdateBullets()
{
	for (auto b : vBullets) {
		b->Update();
	}
}

void Enemy::RenderBullets(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	for (auto b : vBullets) {
		b->Render(hdc);
	}

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void Enemy::CheckBulletsCollision(Tank* tank)
{
	for (auto b : vBullets) {
		if (b->IsLoaded()) continue;
		bool collide = CircleCollideCircle(b->GetPos(), tank->GetPos(), b->GetSize(), tank->GetSize());
		if (collide) {
			b->SetLoaded(true);
			tank->AttackedByBullet(b->GetDamage());
		}
	}
}

void Enemy::InitLoadedBullets()
{
	for (auto b : vBullets)
	{
		b->SetLoaded(true);
	}
}
