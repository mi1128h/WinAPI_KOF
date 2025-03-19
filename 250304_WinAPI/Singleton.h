#pragma once

// 템플릿 싱글톤 클래스 정의
// T는 싱글톤으로 만들고자 하는 클래스 타입
template<typename T>
class Singleton
{
protected:
    static T* instance;  // 싱글톤 인스턴스를 저장하는 정적 포인터
    Singleton() {};      // 생성자는 protected로 외부에서 직접 객체 생성 방지
    ~Singleton() {};     // 소멸자도 protected로 외부에서 직접 객체 삭제 방지
public:
    static T* GetInstance();    // 싱글톤 인스턴스를 반환하는 정적 메서드
    void ReleaseInstance();     // 싱글톤 인스턴스를 해제하는 메서드
};

/*
    링크 과정에서 중복 정의를 방지
    각 템플릿 인스턴스에 대한 스태틱 변수가 고유하게 존재하도록 보장
*/

// 정적 멤버 변수 초기화 - 모든 템플릿 인스턴스에 대해 nullptr로 초기화
template<typename T>
T* Singleton<T>::instance = nullptr;

// GetInstance() 메서드 구현
// 인스턴스가 없으면 새로 생성하고, 있으면 기존 인스턴스 반환
template<typename T>
inline T* Singleton<T>::GetInstance()
{
    if (!instance) {  // 인스턴스가 없으면
        instance = new T;  // 새 인스턴스 생성
    }

    return instance;  // 인스턴스 반환
}

// ReleaseInstance() 메서드 구현
// 인스턴스가 존재하면 메모리 해제하고 포인터를 nullptr로 설정
template<typename T>
inline void Singleton<T>::ReleaseInstance()
{
    if (instance) {  // 인스턴스가 존재하면
        delete instance;  // 메모리 해제
        instance = nullptr;  // 포인터 초기화
    }
}
