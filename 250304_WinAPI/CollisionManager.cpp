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

void CollisionManager::CheckHit(AnimCharacter* attacker, AnimCharacter* defender)
{
	
}

void CollisionManager::CheckHit(Kim* attacker, Kim* defender)
{
	if (RectInRect(attacker->GetHitBox(), defender->GetHurtBox()))
	{
		if (defender->GetState() == State::Dead)
		{
			// TODO : Change to State Guard
			defender->SetHp(defender->GetHp() - 10 / 10);
		}
		// Properties to clear HitBox when successful exploitation
		attacker->SetIsSuccessHit(true);
		defender->SetHp(defender->GetHp() - 10);
		defender->SetState(State::WeakDamaged);
	}
}