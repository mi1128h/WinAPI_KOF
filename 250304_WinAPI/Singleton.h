#pragma once

template<typename T>
class Singleton
{
protected:
	static T* instance;

	Singleton() {};
	~Singleton() {};

public:
	static T* GetInstance();
	void ReleaseInstance();
};

/*
	��ũ �������� �ߺ� ���Ǹ� ����
	�� ���ø� �ν��Ͻ��� ���� ����ƽ ������ �����ϰ� �����ϵ��� ����
*/

template<typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T* Singleton<T>::GetInstance()
{
	if (!instance) {
		instance = new T;
	}
		
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseInstance()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}
