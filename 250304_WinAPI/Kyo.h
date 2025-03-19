#pragma once
#include "AnimCharacter.h"

class Kyo : public AnimCharacter
{
public:
    void Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;

private:
    void ProcessInput() ;
};

