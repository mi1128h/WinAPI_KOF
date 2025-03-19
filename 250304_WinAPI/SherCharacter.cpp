#include "SherCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

// ĳ���� �ʱ�ȭ �Լ�
void SherCharacter::Init()
{
    position = { 0, WINSIZE_Y-200 };  // �ʱ� ��ġ ����
    speed = 10;          // �̵� �ӵ� ����
    dx = 0.0f;           // X ���� �̵��� �ʱ�ȭ
    dy = 0.0f;           // Y ���� �̵��� �ʱ�ȭ

    // ��� ���º� �̹��� ���� �ʱ�ȭ
    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    // ���(Idle) ���� �̹��� �ε�
    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"Image/sher_idle_ver2.bmp", 904, 116, 14, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_idle ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    // �ȱ�(Walk) ���� �̹��� �ε�
    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"Image/sher_walk.bmp", 960, 117, 12, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_walk ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::Walk].push_back(walkImages);

    // ����ġ ����
    Image* weakPunchImages = new Image();
    if (FAILED(walkImages->Init(L"Image/sher_weak_punch_attack_F6.bmp", 1070, 148, 6, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_punch_attack_F6 ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::W_punch].push_back(walkImages);

    // ����ġ ����
    Image* strongPunchImages = new Image();
    if (FAILED(walkImages->Init(L"Image/sher_strong_punch_attack_F12.bmp", 2135, 148, 12, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_strong_attack_F12 ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::S_punch].push_back(walkImages);

    // ��ű ����
    Image* weakKickImages = new Image();
    if (FAILED(walkImages->Init(L"Image/sher_weak_kick_attack_F12.bmp", 1552, 148, 12, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_weak_kick_attack_F12 ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::W_kick].push_back(walkImages);

    // ��ű ����
    Image* strongKickImages = new Image();
    if (FAILED(walkImages->Init(L"Image/sher_strong_kick_attack_F11.bmp", 1420, 148, 11, 1, true, RGB(255, 255, 255)))) {
        MessageBox(g_hWnd, L"sher_strong_kick_attack_F11 ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::S_kick].push_back(walkImages);

    // �ʱ� ���� �� ������ ����
    curState = State::Idle;  // �ʱ� ���´� ���
    frameIdx = 0;            // ������ �ε��� �ʱ�ȭ
    flip = false;            // �¿� ���� ����

    // ĳ���� ũ�� ��� (ù ��° Idle �̹��� ����)
    Image* img = vImages[State::Idle][0];
    size[0] = img->GetWidth() / img->GetSpritesNumX();     // �ʺ� ���
    size[1] = img->GetHeight() / img->GetSpritesNumY();    // ���� ���
}








