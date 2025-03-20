#include "KeyManager.h"
#include "AnimCharacter.h"

HRESULT KeyManager::Init()
{
    keyUp.set();        // true
    keyDown.reset();    // false

    return S_OK;
}

void KeyManager::Release()
{
    ReleaseInstance();
}

bool KeyManager::IsOnceKeyDown(int key)
{
    /*
        GetAsyncKeyState(key);
        �Լ� ȣ�� ������ ����Ű�� � �������� Ȯ��
        1. 0x0000: ���� �����ӿ� ���� ���� ���� ȣ�� �������� �������� ����
        2. 0x0001: ���� �����ӿ� ���� ���� �ְ� ȣ�� �������� �������� ����
        3. 0x8000: ���� �����ӿ� ���� ���� ���� ȣ�� �������� ��������
        4. 0x8001: ���� �����ӿ� ���� ���� �ְ� ȣ�� �������� ��������
    */

    if (GetAsyncKeyState(key) & 0x8000) {
        if (keyDown[key] == false) keyDown[key] = true;
        return true;
    }
    else {
        keyDown[key] = false;
    }

    return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) {
        keyUp[key] = false;
    }
    else {
        if (keyUp[key] == false) {
            keyUp[key] = true;
            return true;
        }
    }
    return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) return true;
    return false;
}


State KeyManager::GetCommand(bool playerClassification)
{
	// �÷��̾� 1,2 Ű ����
	bool WeakHandKey = (playerClassification) ? IsOnceKeyDown('U') : IsOnceKeyDown(VK_NUMPAD4);
	bool StrongHandKey = (playerClassification) ? IsOnceKeyDown('I') : IsOnceKeyDown(VK_NUMPAD5);
	bool WeakFootKey = (playerClassification) ? IsOnceKeyDown('J') : IsOnceKeyDown(VK_NUMPAD1);
	bool StrongFootKey = (playerClassification) ? IsOnceKeyDown('K') : IsOnceKeyDown(VK_NUMPAD2);

	bool LeftKey = (playerClassification) ? IsOnceKeyDown('A') : IsOnceKeyDown(VK_LEFT);
	bool RightKey = (playerClassification) ? IsOnceKeyDown('D') : IsOnceKeyDown(VK_RIGHT);

	// ����Ű �Է� �� �̵� ���� �޶���
	if (LeftKey) return State::BackWalk;
	if (RightKey) return State::Walk;

	// ����Ű �Է� �� ���� ��ȯ
	if (WeakHandKey) return State::WeakHand;
	if (StrongHandKey) return State::StrongHand;
	if (WeakFootKey) return State::WeakFoot;
	if (StrongFootKey) return State::StrongFoot;

	return State::Idle; // �ƹ�Ű �ȴ����� ��, ���ĵ� ����
}
