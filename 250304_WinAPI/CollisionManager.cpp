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
		defender->SetHp(defender->GetHp() - 10);
		defender->SetState(State::Dead);
		// �״°� ���� �ǰݻ��������� 
	}
	else if (RectInRect(attacker->GetHitBox(), defender->GetHurtBox()) && defender->GetState() == State::Dead)
	{
		////////////////////////////////// �̰� ���� �ΰŷ� �ٲ����
		defender->SetHp(defender->GetHp() - 10 / 10);
	}
	else if (RectInRect(attacker->GetHitBox(), defender->GetHurtBox()) && defender->GetState() == State::Dead)
	{
		// �̹� �ѹ� ���� ���¸� �ƹ��� ���� �Ͼ�� �ʴ´�
		// �̰ŵ� State �˸°� ���� �ؾ��Ѵ�.
	}

}