#pragma once
#include "config.h"

class GameObject
{
public:
	virtual void Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ����(������ ���)
	virtual void Render(HDC hdc);	// ������ ������ ���

	GameObject();
	~GameObject();
};

