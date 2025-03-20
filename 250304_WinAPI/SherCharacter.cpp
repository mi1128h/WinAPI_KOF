#include "SherCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

// ĳ���� �ʱ�ȭ �Լ�
void SherCharacter::Init()
{
    position = { 0,0 };  // �ʱ� ��ġ ����
    speed = 10;          // �̵� �ӵ� ����
    dx = 0.0f;           // X ���� �̵��� �ʱ�ȭ
    dy = 0.0f;           // Y ���� �̵��� �ʱ�ȭ

    // ��� ���º� �̹��� ���� �ʱ�ȭ
    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    // ���(Idle) ���� �̹��� �ε�
    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"Image/Sherme/sher_idle_ver2.bmp", 904, 116, 14, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_idle ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    // �ȱ�(Walk) ���� �̹��� �ε�
    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"Image/Sherme/sher_walk.bmp", 960, 117, 12, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_walk ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::Walk].push_back(walkImages);

    // ����ġ ����
    Image* weakPunchImages = new Image();
    if (FAILED(weakPunchImages->Init(L"Image/Sherme/sher_weak_punch_attack_F6_ver2.bmp", 1070, 117, 6, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_punch_attack_F6 ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::WeakHand].push_back(weakPunchImages);

    // ����ġ ����
    Image* strongPunchImages = new Image();
    if (FAILED(strongPunchImages->Init(L"Image/Sherme/sher_strong_punch_attack_F12.bmp", 2135, 148, 12, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_strong_attack_F12 ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::StrongHand].push_back(strongPunchImages);

    // ��ű ����
    Image* weakKickImages = new Image();
    if (FAILED(weakKickImages->Init(L"Image/Sherme/sher_weak_kick_attack_F9_ver3.bmp", 1568, 120, 9, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_kick_attack_F12 ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::WeakFoot].push_back(weakKickImages);

    // ��ű ����
    Image* strongKickImages = new Image();
    if (FAILED(strongKickImages->Init(L"Image/Sherme/sher_strong_kick_attack_F11_ver2.bmp", 1397, 97, 11, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_strong_kick_attack_F11 ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::StrongFoot].push_back(strongKickImages);

    // ����
    Image* deadImages = new Image();
    if (FAILED(deadImages->Init(L"Image/Sherme/sher_dead_F5.bmp", 270, 96, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"bluemary_fall ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::Dead].push_back(deadImages);

    // ĳ���� ũ�� ��� (ù ��° Idle �̹��� ����)
    curState = State::Idle;
    frameIdx = 0;
    flip = SetStartFilp();
}








