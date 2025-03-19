#include "UIManager.h"
#include "AnimCharacter.h" 

void UIManager::Init()
{
    FPOINT PlayerHpbarPos = { 50.f, 50.f };
    FPOINT EnemyHpbarPos = { 700.f, 50.f };

    maxHP = 10;
    playerHP = 10;
    enemyHP = 10;

    playerScore = 0;
    enemyScore = 0;

}

void UIManager::Release()
{
    ReleaseInstance();
}

void UIManager::Update(AnimCharacter* leftPlayer, AnimCharacter* rightPlayer)
{
    if (leftPlayer) playerHP = leftPlayer->GetHp();
    if (rightPlayer) enemyHP = rightPlayer->GetHp();
  
}

void UIManager::Render(HDC hdc)
{
    int barWidth = 200;
    int barHeight = 20;
    int padding = 20;

    // 플레이어 HP 바 (왼쪽)
    Rectangle(hdc, padding, padding, padding + barWidth, padding + barHeight);
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0)); // 초록색 (플레이어)
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Rectangle(hdc, padding, padding, padding + (int)(barWidth * (playerHP / 10.0f)), padding + barHeight);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);


    // 적 HP 바 (오른쪽)
    int enemyBarX = WINSIZE_X - barWidth - padding;
    Rectangle(hdc, enemyBarX, padding, enemyBarX + barWidth, padding + barHeight);
    hBrush = CreateSolidBrush(RGB(0, 255, 0)); // 빨간색 (적)
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Rectangle(hdc, enemyBarX, padding, enemyBarX + (int)(barWidth * (enemyHP / 10.0f)), padding + barHeight);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);




}
