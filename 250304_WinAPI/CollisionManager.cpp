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

// ��ĥ���Ѱ� : ����� ��ȯ�ϰ� �� ����� MainGame���� Ȱ���Ͽ� �Ǻ��ϰ�
void CollisionManager::CheckHit(AnimCharacter* attacker, AnimCharacter* defender)
{
	if (!attacker->GetIsSuccessHit())
	{
		if (RectInRect(attacker->GetHitBox(), defender->GetHurtBox()))
		{
			if (attacker->GetState() == State::WeakFoot ||  attacker->GetState() == State::WeakHand)
			{
				// ���� �����̸� attakcer->GetAttackValue()

				if (defender->GetState() == State::Defend)
				{
					defender->SetHp(defender->GetHp() - 0.5f);
				}
				else
				{
					defender->SetHp(defender->GetHp() - 1.f);
					defender->SetState(State::WeakDamaged);
					// ����ݿ� ������ ���¹̳� +2 , ������ +1  
					attacker->SetStamina(attacker->GetStamina() + 2);
					defender->SetStamina(defender->GetStamina() + 1);
				}
			}
			else if (attacker->GetState() == State::StrongFoot ||  attacker->GetState() == State::StrongHand)
			{
				// ���� �����̸� attakcer->GetAttackValue() * 2
				if (defender->GetState() == State::Defend)
				{
					defender->SetHp(defender->GetHp() - 1.f);
				}
				else
				{
					defender->SetHp(defender->GetHp() - 2.f);
					defender->SetState(State::StrongDamaged);
					// �����ݿ� ������ ���¹̳� + 3, ������ +2
					attacker->SetStamina(attacker->GetStamina() + 3);
					defender->SetStamina(defender->GetStamina() + 2);
				}
			}

			attacker->SetIsSuccessHit(true);
		}
	}
}
