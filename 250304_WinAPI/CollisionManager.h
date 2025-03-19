#pragma once
#include "Singleton.h"
#include "config.h"

/*
    �±⸸ �ϴ� �ݸ����� ���ظ� �ִ� �ݸ����� ���� ������ �ұ�?\
    �����ؼ� �ϸ� ������?
*/
class Character;
class Kim;
class CollisionManager : public Singleton<CollisionManager>
{
	
public:

	HRESULT Init();
	void Release();

    void CheckHit(Character* attacker, Character* defender);
    void CheckHit(Kim* attacker, Kim* defender);

    void UnregisterObject(Character* Character);

    void CheckCollisions();
    
};

