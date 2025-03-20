#include "KeyManager.h"

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

    //if (GetAsyncKeyState(key) & 0x8000) {
    //    if (keyDown[key] == false) keyDown[key] = true;
    //    return true;
    //}
    //else {
    //    keyDown[key] = false;
    //}

    //return false;

    // GetAsyncKeyState ȣ�� �� ���� Ȯ��
    if ((GetAsyncKeyState(key) & 0x8000) != 0) { // Ű�� ���ȴ��� Ȯ��
        if (!keyDown[key]) {
            keyDown[key] = true; // ���� ����
            return true;         // ó�� ���� ��� true ��ȯ
        }
    }
    else {
        keyDown[key] = false;     // Ű�� ������ �ʾ��� �� ���� �ʱ�ȭ
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
