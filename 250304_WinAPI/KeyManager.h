#pragma once  
#include "Singleton.h"  // Singleton ���ø� Ŭ������ ����
#include "config.h"  
#define MAX_KEY_COUNT	256  // �ִ� Ű ������ 256���� ����
using namespace std;  

// KeyManager Ŭ���� ����, Singleton ���ø��� ��ӹ���
class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<MAX_KEY_COUNT> keyUp;    // Ű�� ������ ���¸� �����ϴ� ��Ʈ��
	bitset<MAX_KEY_COUNT> keyDown;  // Ű�� ���� ���¸� �����ϴ� ��Ʈ��

public:
	HRESULT Init();  // �ʱ�ȭ �Լ�
	void Release();  // �ڿ� ���� �Լ�

	bool IsOnceKeyDown(int key);    // �ش� Ű�� ó�� ���ȴ��� �Ǵ�
	bool IsOnceKeyUp(int key);      // �ش� Ű�� ���ȴٰ� ó�� ���������� �Ǵ�
	bool IsStayKeyDown(int key);    // �ش� Ű�� ��� �����ִ� �������� �Ǵ�

	// Ű ���¸� ���� �����ϴ� �Լ���
	void SetKeyDown(int key, bool state) { this->keyDown.set(key, state); }  // keyDown ��Ʈ���� Ư�� Ű ���� ����
	void SetKeyUp(int key, bool state) { this->keyUp.set(key, state); }      // keyUp ��Ʈ���� Ư�� Ű ���� ����
};

