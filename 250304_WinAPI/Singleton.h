#pragma once

// ���ø� �̱��� Ŭ���� ����
// T�� �̱������� ������� �ϴ� Ŭ���� Ÿ��
template<typename T>
class Singleton
{
protected:
    static T* instance;  // �̱��� �ν��Ͻ��� �����ϴ� ���� ������
    Singleton() {};      // �����ڴ� protected�� �ܺο��� ���� ��ü ���� ����
    ~Singleton() {};     // �Ҹ��ڵ� protected�� �ܺο��� ���� ��ü ���� ����
public:
    static T* GetInstance();    // �̱��� �ν��Ͻ��� ��ȯ�ϴ� ���� �޼���
    void ReleaseInstance();     // �̱��� �ν��Ͻ��� �����ϴ� �޼���
};

/*
    ��ũ �������� �ߺ� ���Ǹ� ����
    �� ���ø� �ν��Ͻ��� ���� ����ƽ ������ �����ϰ� �����ϵ��� ����
*/

// ���� ��� ���� �ʱ�ȭ - ��� ���ø� �ν��Ͻ��� ���� nullptr�� �ʱ�ȭ
template<typename T>
T* Singleton<T>::instance = nullptr;

// GetInstance() �޼��� ����
// �ν��Ͻ��� ������ ���� �����ϰ�, ������ ���� �ν��Ͻ� ��ȯ
template<typename T>
inline T* Singleton<T>::GetInstance()
{
    if (!instance) {  // �ν��Ͻ��� ������
        instance = new T;  // �� �ν��Ͻ� ����
    }

    return instance;  // �ν��Ͻ� ��ȯ
}

// ReleaseInstance() �޼��� ����
// �ν��Ͻ��� �����ϸ� �޸� �����ϰ� �����͸� nullptr�� ����
template<typename T>
inline void Singleton<T>::ReleaseInstance()
{
    if (instance) {  // �ν��Ͻ��� �����ϸ�
        delete instance;  // �޸� ����
        instance = nullptr;  // ������ �ʱ�ȭ
    }
}
