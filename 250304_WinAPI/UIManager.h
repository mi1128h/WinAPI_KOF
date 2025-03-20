#pragma once
#include "Singleton.h"
#include "config.h"
class AnimCharacter;
class Image;


enum Ui {
    Advanced,
    StartUi,
    StartUiFront,
    LeftUi,
    RightUi,
    infinityUi,
    Uilength,
};

class UIManager :public Singleton<UIManager> {
public:
    void Init();
    void Release();
    void Update(AnimCharacter* leftPlayer, AnimCharacter* rightPlayer, float elapsedTime);
    void Render(HDC hdc);


    void Animate(float elapsedTime);

    void advRender(HDC hdc);
    void HpRender(HDC hdc);

    void SteminaRender(HDC hdc);


    void SetPlayerHP(float hp) { playerHP = hp; }
    void SetEnemyHP(float hp) { enemyHP = hp; }
    void SetPlayerScore(int score) { playerScore = score; }
    void SetEnemyScore(int score) { enemyScore = score; }

private:
    AnimCharacter* player = nullptr;
    AnimCharacter* enemy = nullptr;
    std::vector<std::vector<Image*>> vUiImages; 

    float maxHP = 10;
    float playerHP = 10;
    float enemyHP = 10;
    float playerStamina = 3.f;
    float enemyStamina = 3.f;

    int frameIdx;
    Ui curUi;

    POINT PlayerHpbarPos;
    POINT EnemyHpbarPos;

    int playerScore = 0;
    int enemyScore = 0;


    float accumTime;
    float animTime = 0.7f;


    //--character selection ui--


};
