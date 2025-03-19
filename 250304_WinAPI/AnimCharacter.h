#pragma once
#include "GameObject.h"

// ĳ���� ���� ������
enum State {
	Idle,         // ��� ����
	Walk,         // �ȱ� ����
	Dead,         // ��� ����
	Statelength   // ���� �� ����
};

class Image;  // Image Ŭ���� ���� ����

// �ִϸ��̼� ĳ���� Ŭ���� - GameObject�� ��ӹ���
class AnimCharacter : public GameObject
{
protected:
	FPOINT position;  // ĳ���� ��ġ (�ε� �Ҽ��� ��ǥ)
	float dx, dy;     // �̵� ���� �� �ӵ� ��
	float speed;      // �̵� �ӵ�
	int size[2];      // ĳ���� ũ�� [�ʺ�, ����]

	vector<Image*> vImages[State::Statelength];  // �� ���º� �̹��� ���� �迭
	State curState;   // ���� ĳ���� ����
	int frameIdx;     // ���� �ִϸ��̼� ������ �ε���
	bool flip;        // �¿� ���� ����

public:
	virtual void Init();          // �ʱ�ȭ �Լ� (���� �Լ�)
	void Release();               // �ڿ� ���� �Լ�
	void Update();                // ������Ʈ �Լ�
	void ProcessInput();          // �Է� ó�� �Լ�
	void Animate();               // �ִϸ��̼� ������Ʈ �Լ�
	void Render(HDC hdc);         // ������ �Լ�
	void Move();                  // ĳ���� �̵� �Լ�

	// �̵� ���� ���� �Լ�
	void SetDelta(int dx, int dy) { this->dx = dx; this->dy = dy; }

	// ���� ��ġ ��ȯ �Լ�
	FPOINT GetPos() { return position; }

	// ���� ���� ��ȯ �Լ�
	State GetState() { return curState; }

	// ���� ���� �Լ� - ���� ���¸� ����, �ٸ� ���¸� ������ �ʱ�ȭ
	void SetState(State state) { if (state == curState) return; curState = state; frameIdx = 0; }
};

