#pragma once  
#include "Singleton.h"  // Singleton 템플릿 클래스를 포함
#include "config.h"  
#define MAX_KEY_COUNT	256  // 최대 키 개수를 256으로 정의
using namespace std;  

// KeyManager 클래스 정의, Singleton 템플릿을 상속받음
class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<MAX_KEY_COUNT> keyUp;    // 키가 떼어진 상태를 저장하는 비트셋
	bitset<MAX_KEY_COUNT> keyDown;  // 키가 눌린 상태를 저장하는 비트셋

public:
	HRESULT Init();  // 초기화 함수
	void Release();  // 자원 해제 함수

	bool IsOnceKeyDown(int key);    // 해당 키가 처음 눌렸는지 판단
	bool IsOnceKeyUp(int key);      // 해당 키가 눌렸다가 처음 떼어졌는지 판단
	bool IsStayKeyDown(int key);    // 해당 키가 계속 눌려있는 상태인지 판단

	// 키 상태를 직접 설정하는 함수들
	void SetKeyDown(int key, bool state) { this->keyDown.set(key, state); }  // keyDown 비트셋의 특정 키 상태 설정
	void SetKeyUp(int key, bool state) { this->keyUp.set(key, state); }      // keyUp 비트셋의 특정 키 상태 설정
};

