#pragma once
class RoundManager
{
	int currentRound;//���������
	int enemyCnt;//���庰 �ִ� ������
	bool isClear; //���� Ŭ���� �ߴ���
	bool gameOver; //������ ��������

public:

	void Init();
	void setIsClear(bool clear) { isClear = clear; }
	void IncEnemyCnt() { enemyCnt++; }
	bool canCreateEnemy();//�� ���� ����  ,������ ��ȯ
	int getCurrentEnemyCnt() { return enemyCnt; }
	int getCurrentRound();// ���� �� ���� ��ȯ
	void CheckGameOver(int hp); //�÷��̾� hp�� 0�̸� gameOver = true;
	bool IsGameOver() { return gameOver; }
	bool IsNewRound();
	//�� ����
	float getEnemySpeed();
	float getFireInterval();
	float getBulletSpeed();
	int getBulletNum();
	//�� �̵��ӵ� ���� 
	int getEnemySize();//�� ũ�� ����
	float getEnemyHp(); //�� hp ����
	bool IsGameClear();
};

