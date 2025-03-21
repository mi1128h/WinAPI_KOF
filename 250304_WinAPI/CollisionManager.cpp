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
			if (attacker->GetState() == State::WeakFoot ||  attacker->GetState() == State::WeakHand)
			{
				// 약한 공격이면 attakcer->GetAttackValue()

				if (defender->GetState() == State::Defend)
				{
					defender->SetHp(defender->GetHp() - 0.5f);
				}
				else
				{
					defender->SetHp(defender->GetHp() - 1.f);
					defender->SetState(State::WeakDamaged);
					// 약공격에 때린넘 스태미나 +2 , 맞은넘 +1  
					attacker->SetStamina(attacker->GetStamina() + 2);
					defender->SetStamina(defender->GetStamina() + 1);
				}
			}
			else if (attacker->GetState() == State::StrongFoot ||  attacker->GetState() == State::StrongHand)
			{
				// 강한 공격이면 attakcer->GetAttackValue() * 2
				if (defender->GetState() == State::Defend)
				{
					defender->SetHp(defender->GetHp() - 1.f);
				}
				else
				{
					defender->SetHp(defender->GetHp() - 2.f);
					defender->SetState(State::StrongDamaged);
					// 강공격에 때린넘 스태미나 + 3, 맞은넘 +2
					attacker->SetStamina(attacker->GetStamina() + 3);
					defender->SetStamina(defender->GetStamina() + 2);
				}
			}

			attacker->SetIsSuccessHit(true);
		}
	}
}
