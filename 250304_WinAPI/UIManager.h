#pragma once
#include "Singleton.h"
#include "config.h"
class AnimCharacter;
class Image;


enum Ui {
    Advanced,
    KyoUi,
    LeftUi,
    RightUi,
    Uilength,
};

class UIManager :public Singleton<UIManager> {
public:
    void Init();
    void Release();
    void Update(AnimCharacter* leftPlayer, AnimCharacter* rightPlayer);
    void Render(HDC hdc);

    void Animate();

    void advRender(HDC hdc);
    void HpRender(HDC hdc);


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
    
    int frameIdx;
    Ui curUi;

    POINT PlayerHpbarPos;
    POINT EnemyHpbarPos;

    int playerScore = 0;
    int enemyScore = 0;
};
