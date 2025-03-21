#include "CollisionManager.h"
#include "CommonFunction.h"
#include "AnimCharacter.h"

HRESULT CollisionManager::Init()
{

	return S_OK;
}

void CollisionManager::Release()
{
	ReleaseInstance();
}

// 고칠만한거 : 결과를 반환하고 그 결과를 MainGame에서 활용하여 판별하게
void CollisionManager::CheckHit(AnimCharacter* attacker, AnimCharacter* defender)
{
	if (!attacker->GetIsSuccessHit())
	{
		if (RectInRect(attacker->GetHitBox(), defender->GetHurtBox()))
		{
			if (attacker->GetState() == State::WeakFoot || attacker->GetState() == State::WeakHand)
			{
				// 약한 공격이면 attakcer->GetAttackValue()
				defender->SetHp(defender->GetHp() - 1);
				defender->SetState(State::WeakDamaged);
			}
			else if (attacker->GetState() == State::StrongFoot || attacker->GetState() == State::StrongHand)
			{
				// 강한 공격이면 attakcer->GetAttackValue() * 2
				defender->SetHp(defender->GetHp() - 2);
				defender->SetState(State::StrongDamaged);
			}
			else if (defender->GetState() == State::Dead)
			{
				// TODO : Change to State Guard
				defender->SetHp(defender->GetHp() - 0.5);
			}
			attacker->SetIsSuccessHit(true);
		}
	}
}