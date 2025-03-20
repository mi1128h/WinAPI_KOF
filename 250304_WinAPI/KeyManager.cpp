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
        함수 호출 시점에 가상키가 어떤 상태인지 확인
        1. 0x0000: 이전 프레임에 누른 적이 없고 호출 시점에도 눌려있지 않음
        2. 0x0001: 이전 프레임에 누른 적이 있고 호출 시점에는 눌려있지 않음
        3. 0x8000: 이전 프레임에 누른 적이 없고 호출 시점에는 눌려있음
        4. 0x8001: 이전 프레임에 누른 적이 있고 호출 시점에도 눌려있음
    */

    if (GetAsyncKeyState(key) & 0x8000) {
        if (keyDown[key] == false) keyDown[key] = true;
        return true;
    }
    else {
        keyDown[key] = false;
    }

    return false;

    // GetAsyncKeyState 호출 시 상태 확인
    //if ((GetAsyncKeyState(key) & 0x8000) != 0) { // 키가 눌렸는지 확인
    //    if (!keyDown[key]) {
    //        keyDown[key] = true; // 상태 갱신
    //        return true;         // 처음 눌린 경우 true 반환
    //    }
    //}
    //else {
    //    keyDown[key] = false;     // 키가 눌리지 않았을 때 상태 초기화
    //}
    //return false;

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
	// 플레이어 1,2 키 구분
	bool WeakHandKey = (playerClassification) ? IsOnceKeyDown('U') : IsOnceKeyDown(VK_NUMPAD4);
	bool StrongHandKey = (playerClassification) ? IsOnceKeyDown('I') : IsOnceKeyDown(VK_NUMPAD5);
	bool WeakFootKey = (playerClassification) ? IsOnceKeyDown('J') : IsOnceKeyDown(VK_NUMPAD1);
	bool StrongFootKey = (playerClassification) ? IsOnceKeyDown('K') : IsOnceKeyDown(VK_NUMPAD2);

	// 공격키 입력 시 공격 변환
	if (WeakHandKey) return State::WeakHand;
	if (StrongHandKey) return State::StrongHand;
	if (WeakFootKey) return State::WeakFoot;
	if (StrongFootKey) return State::StrongFoot;

	return (State) -1; // 아무키 안눌렀을 때, 스탠딩 상태
}

bool KeyManager::IsLeftKeyDown(bool playerClassification)
{
    bool LeftKey = (playerClassification) ? IsOnceKeyDown('A') : IsOnceKeyDown(VK_LEFT);
    return LeftKey;
}

bool KeyManager::IsRightKeyDown(bool playerClassification)
{
    bool RightKey = (playerClassification) ? IsOnceKeyDown('D') : IsOnceKeyDown(VK_RIGHT);
    return RightKey;
}
