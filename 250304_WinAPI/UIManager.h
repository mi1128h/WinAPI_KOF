#pragma once
#include "Singleton.h"
#include "config.h"
class AnimCharacter;
class Image;


enum Ui {
    Advanced,
    StartUi,
    StartUiFront,
    HpUi,
    LeftUi,
    RightUi,
    BackWindow,
    infinityUi,
    EndingUi,
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
    void StartRender(HDC hdc);

    void SteminaRender(HDC hdc);


    void SetPlayerHP(float hp) { playerHP = hp; }
    void SetEnemyHP(float hp) { enemyHP = hp; }
    void SetPlayerScore(int score) { playerScore = score; }
    void SetEnemyScore(int score) { enemyScore = score; }

    void SetDrawFirstScreen(bool draw) { drawFirstScreen = draw; };
        
private:
    AnimCharacter* player = nullptr;
    AnimCharacter* enemy = nullptr;
    std::vector<std::vector<Image*>> vUiImages; 

    float maxHP = 10;
    float playerHP = 10;
    float enemyHP = 10;
    float playerStamina;
    float enemyStamina;

    int frameIdx[Uilength]{};
    Ui curUi;

    POINT PlayerHpbarPos;
    POINT EnemyHpbarPos;

    int playerScore = 0;
    int enemyScore = 0;

    int StartUiFrontY = 116;

    float accumTime;
    float animTime = 5.f;

    bool firstAnimEnd = false;

    //--character selection ui--
    bool drawFirstScreen = true;

};
