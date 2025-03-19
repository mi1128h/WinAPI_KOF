#pragma once  
#include "config.h"  

// ���� �������� ������
enum Stage {
    Stage1,       // ù ��° ��������
    Stagelength   // �������� �� ����
};

class Image;  // Image Ŭ������ ���� ���� ����
class AnimCharacter;  // AnimCharacter Ŭ������ ���� ���� ����

// �ִϸ��̼� ��� Ŭ����
class AnimBackground
{
private:
    FPOINT position;  // ����� ��ġ (�ε� �Ҽ��� ��ǥ)
    float speed;      // ��� �̵� �ӵ�
    vector<Image*> vImages[Stage::Stagelength];  // �� ���������� ��� �̹��� ���� �迭
    Stage curStage;   // ���� ��������
    int frameIdx;     // ���� �ִϸ��̼� ������ �ε���
    AnimCharacter* focusTarget;  // ����� ����ٴ� ĳ���� ������ (��: ī�޶� Ÿ��)

public:
    void Init();      // �ʱ�ȭ �Լ�
    void Release();   // �ڿ� ���� �Լ�
    void Update();    // ������Ʈ �Լ�
    void Animate();   // �ִϸ��̼� ������Ʈ �Լ�
    void Render(HDC hdc);  // ��� ������ �Լ�

    // ��� ��ġ ��ȯ �Լ�
    FPOINT GetPos() { return position; }

    // ���� �������� ��ȯ �Լ�
    Stage GetStage() { return curStage; }

    // �������� ���� �Լ�
    void SetStage(Stage stage) { curStage = stage; }
};

