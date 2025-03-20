#pragma once
#include "Singleton.h"
#include "config.h"

#define MAX_KEY_COUNT	256
using namespace std;

enum State;
class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<MAX_KEY_COUNT> keyUp;
	bitset<MAX_KEY_COUNT> keyDown;

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	// �ش� Ű�� ó�� ���ȴ��� �Ǵ�
	bool IsOnceKeyUp(int key);		// �ش� Ű�� ���ȴٰ� ó�� ���������� �Ǵ�
	bool IsStayKeyDown(int key);	// �ش� Ű�� ��� �����ִ� �������� �Ǵ�

	void SetKeyDown(int key, bool state) { this->keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { this->keyUp.set(key, state); }

	State GetCommand(bool playerClassification);
};

