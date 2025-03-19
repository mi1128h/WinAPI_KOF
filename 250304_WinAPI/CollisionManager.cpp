#include "CollisionManager.h"
#include "CommonFunction.h"
#include "AnimCharacter.h"
#include "Kim.h"

HRESULT CollisionManager::Init()
{

	return S_OK;
}

void CollisionManager::Release()
{
	ReleaseInstance();
}

void CollisionManager::CheckHit(Character* attacker, Character* defender)
{
  
}

void CollisionManager::CheckHit(Kim* attacker, Kim* defender)
{
	if (RectInRect(attacker->GetHitBox(), defender->GetHurtBox()))
	{
		defender->SetHp(defender->GetHp() - 10);
	}
	else if (RectInRect(attacker->GetHitBox(), defender->GetHurtBox()) && defender->GetState() == State::Dead)
	{
		////////////////////////////////// �̰� ���� �ΰŷ� �ٲ����
		defender->SetHp(defender->GetHp() - 10 / 10);

	}
}