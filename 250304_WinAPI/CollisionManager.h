#pragma once
#include "Singleton.h"
#include "config.h"

/*
    맞기만 하는 콜리전과 피해만 주는 콜리전을 따로 만들어야 할까?\
    구분해서 하면 좋을까?
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

