#include "KeyManager.h"

// KeyManager�� �ʱ�ȭ�ϴ� �Լ�
HRESULT KeyManager::Init()
{
    keyUp.set();        // keyUp ��Ʈ���� ��� true�� ����
    keyDown.reset();    // keyDown ��Ʈ���� ��� false�� ����
    return S_OK;        // ���������� �ʱ�ȭ���� ��ȯ
}

// KeyManager�� �ڿ��� �����ϴ� �Լ�
void KeyManager::Release()
{
    ReleaseInstance();  // �̱��� �ν��Ͻ��� ����
}

// Ű�� �� ���� ���ȴ��� Ȯ���ϴ� �Լ�
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
    if (GetAsyncKeyState(key) & 0x8000) {    // Ű�� ���� ����������
        if (keyDown[key] == false) keyDown[key] = true;  // ������ ������ �ʾҴٸ� ���¸� true�� ����
        return true;    // Ű�� �������� ��ȯ
    }
    else {              // Ű�� ���� �������� ������
        keyDown[key] = false;  // Ű�� ���¸� false�� ����
    }
    return false;       // Ű�� ������ �ʾ����� ��ȯ
}

// Ű�� �� ���� ���������� Ȯ���ϴ� �Լ�
bool KeyManager::IsOnceKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) {    // Ű�� ���� ����������
        keyUp[key] = false;    // keyUp ���¸� false�� ����
    }
    else {                      // Ű�� ���� �������� ������
        if (keyUp[key] == false) {  // ������ Ű�� �����־��ٸ�
            keyUp[key] = true;      // ���¸� true�� ����
            return true;            // Ű�� ���������� ��ȯ
        }
    }
    return false;               // Ű�� �������� �ʾ����� ��ȯ
}

// Ű�� ��� �����ִ��� Ȯ���ϴ� �Լ�
bool KeyManager::IsStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) return true;  // Ű�� ���� ���������� true ��ȯ
    return false;                                     // Ű�� �������� ������ false ��ȯ
}
