#include "RoundManager.h"

void RoundManager::Init()
{
    currentRound = 1;
    enemyCnt = 0;
    isClear = false;
    gameOver = false;
}

bool RoundManager::canCreateEnemy() //적 수량 증가  ,출현수 반환
{
    switch (currentRound)
    {
    case 1:
        return enemyCnt < 10;
        break;
    case 2:
        return enemyCnt < 10;
        break;
    case 3:
        return enemyCnt < 20;
        break;
    default:
        break;
    }
}

int RoundManager::getCurrentRound()
{
    return currentRound;
}

void RoundManager::CheckGameOver(int hp)
{
    if (hp <= 0)
    {
        gameOver = true;
    }
    else
    {
        gameOver = false;
    }
}

bool RoundManager::IsNewRound()
{
    if (isClear == true)
    {
        isClear = false;
        currentRound++;
        enemyCnt = 0;
        return true;
    }
    return false;
}

int RoundManager::getEnemySize()
{
    switch (currentRound)
    {
    case 1:
        return 20;
        break;
    case 2:
        return 40;
        break;
    case 3:
        return 100;
        break;
    default:
        break;
    }
}

float RoundManager::getEnemyHp()
{
    switch (currentRound)
    {
    case 1:
        return 1.0f;
        break;
    case 2:
        return 20.0f;
        break;
    case 3:
        return 80.0f;
        break;
    default:
        break;
    }
}

bool RoundManager::IsGameClear()
{
    if (currentRound == 4 && gameOver == false)
    {
        return true;
    }
    return false;
}

float RoundManager::getEnemySpeed()
{
    switch (currentRound)
    {
    case 1:
        return 10.0f;
        break;
    case 2:
        return 20.0f;
        break;
    case 3:
        return 10.0f;
        break;
    default:
        break;
    }
}

float RoundManager::getFireInterval()
{
    switch (currentRound)
    {
    case 1:
        return 20.0f;
        break;
    case 2:
        return 10.0f;
        break;
    case 3:
        return 10.0f;
        break;
    default:
        break;
    }
}

float RoundManager::getBulletSpeed()
{
    switch (currentRound)
    {
    case 1:
        return 15.0f;
        break;
    case 2:
        return 30.0f;
        break;
    case 3:
        return 30.0f; //매우빠를듯
        break;
    default:
        break;
    }
}

int RoundManager::getBulletNum()
{
    switch (currentRound)
    {
    case 1:
        return 3;
        break;
    case 2:
        return 10;
        break;
    case 3:
        return 50;
        break;
    default:
        break;
    }
}