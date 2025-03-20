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
			////////////////////////////////// 이거 가드 인거로 바꿔야함
			defender->SetHp(defender->GetHp() - 10 / 10);
		}
		else if (defender->GetState() == State::WeakDamaged)
		{
			return;
			// 이미 한번 맞은 상태면 아무런 일이 일어나지 않는다
			// 이거도 State 알맞게 수정 해야한다.
		}
		defender->SetHp(defender->GetHp() - 10);
		defender->SetState(State::WeakDamaged);
		// 죽는거 말고 피격상태중으로 
	}
}