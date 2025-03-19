#pragma once
#include "Singleton.h"
#include "config.h"


class Character;
class Kim;
class CollisionManager : public Singleton<CollisionManager>
{
	
public:

	HRESULT Init();
	void Release();

    void CheckHit(Character* attacker, Character* defender);
    void CheckHit(Kim* attacker, Kim* defender);
	   
};

