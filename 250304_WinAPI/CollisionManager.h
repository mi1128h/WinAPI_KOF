#pragma once
#include "Singleton.h"
#include "config.h"


class AnimCharacter;
class Kim;
class CollisionManager : public Singleton<CollisionManager>
{
	
public:

	HRESULT Init();
	void Release();

    void CheckHit(AnimCharacter* attacker, AnimCharacter* defender);
    void CheckHit(Kim* attacker, Kim* defender);
	   
};

