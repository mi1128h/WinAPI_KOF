#include "Bullet.h"
#include "CommonFunction.h"
#include "Enemy.h"

void Bullet::Init(FPOINT pos, float angle)
{
	isLoaded = true;
	position = pos;
	fireAngle = angle;
	speed = 20.0f;
	size = 10;
	damage = 3;
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);

	guided = false;
	target = nullptr;
}

void Bullet::Release()
{
}

void Bullet::Update()
{
	if (isLoaded) return;

	if (guided) {
		if (target) {
			UpdateGuidedAngle();
		}
	}

	Move();
	CheckWallCollision();
}

void Bullet::Render(HDC hdc)
{
	if (isLoaded) return;

	RenderEllipseAtCenter(hdc, position.x, position.y, size, size);
}

void Bullet::Move()
{
	position.x += cosf(TORADIAN(fireAngle)) * speed;
	position.y -= sinf(TORADIAN(fireAngle)) * speed;
}

void Bullet::UpdateGuidedAngle()
{
	if (!target) return;
	float targetAngle = GetAngle(position, target->GetPos());

	float dAngle = targetAngle - fireAngle;

	if (abs(dAngle) < 10) fireAngle = targetAngle;
	else {
		float angle{ dAngle };
		float min{ abs(dAngle) };
		if (min > abs(dAngle - 360)) {
			min = abs(dAngle - 360);
			angle = dAngle - 360;
		}
		if (min > abs(dAngle + 360)) {
			min = abs(dAngle + 360);
			angle = dAngle + 360;
		}
		fireAngle += angle * 0.3f;
	}
}

void Bullet::CheckWallCollision()
{
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);
	if (IsOutOfRange(position, WINSIZE_X, WINSIZE_Y)) isLoaded = true;
}

void Bullet::CheckEnemyCollision(Enemy* enemy)
{
	if (isLoaded) return;
	if (enemy->IsDead()) return;

	if (CircleCollideCircle(position, enemy->GetPos(), size, enemy->GetSize())) {
		enemy->AttackedByBullet(damage);
		isLoaded = true;
	}
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void BombBullet::SetBombValues(int time, float angle)
{
	countDown = time;
	angle_360 = angle;
}

void BombBullet::Update()
{
	if (countDown) countDown--;
	Bullet::Update();
}

void BombBullet::Move()
{
	if (countDown > 0) Bullet::Move();
	else {
		position.x += cosf(TORADIAN(angle_360)) * speed;
		position.y -= sinf(TORADIAN(angle_360)) * speed;
	}
}

void BounceBullet::SetBounceNum(int cnt)
{
	bounceNum = cnt;
}

void BounceBullet::CheckWallCollision()
{
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);
	if (IsOutOfRange(position, WINSIZE_X, WINSIZE_Y)) {
		if (!bounceNum) isLoaded = true;
		else {
			bounceNum--;
			bool isUpsideDown = IsOutOfRange({ WINSIZE_X / 2, position.y }, WINSIZE_X, WINSIZE_Y);
			fireAngle = 180 * (isUpsideDown ? 2 : 1) - fireAngle;
			position.x = ClampVal(position.x, 0.0f, (float)WINSIZE_X);
			position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);
		}
	}
}

void ConfettiBullet::SetConfettiValues(int life)
{
	colors[0] = uid_200_255(dre);
	colors[1] = uid_0_255(dre);
	colors[2] = uid_0_255(dre);
	lifeTime = life * uid_1_2(dre);
}

void ConfettiBullet::Update()
{
	BombBullet::Update();
	if (countDown <= 0) {
		speed = uid_0_10(dre);
		lifeTime--;
	}
	if (lifeTime <= 0) isLoaded = true;
}

void ConfettiBullet::Render(HDC hdc)
{
	if (isLoaded) return;
	if (countDown > 0) {
		Bullet::Render(hdc);
	}
	else {
		HBRUSH hBrush = CreateSolidBrush(RGB(colors[0], colors[1], colors[2]));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		RenderRectAtCenter(hdc, position.x, position.y, lifeTime, lifeTime);

		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}
}
