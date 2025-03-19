#include "KeyManager.h"

// KeyManager를 초기화하는 함수
HRESULT KeyManager::Init()
{
    keyUp.set();        // keyUp 비트셋을 모두 true로 설정
    keyDown.reset();    // keyDown 비트셋을 모두 false로 설정
    return S_OK;        // 성공적으로 초기화됨을 반환
}

// KeyManager의 자원을 해제하는 함수
void KeyManager::Release()
{
    ReleaseInstance();  // 싱글톤 인스턴스를 해제
}

// 키가 한 번만 눌렸는지 확인하는 함수
bool KeyManager::IsOnceKeyDown(int key)
{
    /*
        GetAsyncKeyState(key);
        함수 호출 시점에 가상키가 어떤 상태인지 확인
        1. 0x0000: 이전 프레임에 누른 적이 없고 호출 시점에도 눌려있지 않음
        2. 0x0001: 이전 프레임에 누른 적이 있고 호출 시점에는 눌려있지 않음
        3. 0x8000: 이전 프레임에 누른 적이 없고 호출 시점에는 눌려있음
        4. 0x8001: 이전 프레임에 누른 적이 있고 호출 시점에도 눌려있음
    */
    if (GetAsyncKeyState(key) & 0x8000) {    // 키가 현재 눌려있으면
        if (keyDown[key] == false) keyDown[key] = true;  // 이전에 눌리지 않았다면 상태를 true로 변경
        return true;    // 키가 눌렸음을 반환
    }
    else {              // 키가 현재 눌려있지 않으면
        keyDown[key] = false;  // 키의 상태를 false로 설정
    }
    return false;       // 키가 눌리지 않았음을 반환
}

// 키가 한 번만 떼어졌는지 확인하는 함수
bool KeyManager::IsOnceKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) {    // 키가 현재 눌려있으면
        keyUp[key] = false;    // keyUp 상태를 false로 설정
    }
    else {                      // 키가 현재 눌려있지 않으면
        if (keyUp[key] == false) {  // 이전에 키가 눌려있었다면
            keyUp[key] = true;      // 상태를 true로 변경
            return true;            // 키가 떼어졌음을 반환
        }
    }
    return false;               // 키가 떼어지지 않았음을 반환
}

// 키가 계속 눌려있는지 확인하는 함수
bool KeyManager::IsStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) return true;  // 키가 현재 눌려있으면 true 반환
    return false;                                     // 키가 눌려있지 않으면 false 반환
}
