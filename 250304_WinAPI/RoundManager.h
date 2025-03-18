#pragma once
class RoundManager
{
	int currentRound;//몇라운드인지
	int enemyCnt;//라운드별 최대 적수량
	bool isClear; //라운드 클리어 했는지
	bool gameOver; //게임이 끝났는지

public:

	void Init();
	void setIsClear(bool clear) { isClear = clear; }
	void IncEnemyCnt() { enemyCnt++; }
	bool canCreateEnemy();//적 수량 증가  ,출현수 반환
	int getCurrentEnemyCnt() { return enemyCnt; }
	int getCurrentRound();// 현재 턴 정보 반환
	void CheckGameOver(int hp); //플레이어 hp가 0이면 gameOver = true;
	bool IsGameOver() { return gameOver; }
	bool IsNewRound();
	//턴 진행
	float getEnemySpeed();
	float getFireInterval();
	float getBulletSpeed();
	int getBulletNum();
	//적 이동속도 증가 
	int getEnemySize();//적 크기 감소
	float getEnemyHp(); //적 hp 증가
	bool IsGameClear();
};

