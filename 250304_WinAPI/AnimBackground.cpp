#include "AnimBackground.h"
#include "Image.h"

// ��� Ŭ���� �ʱ�ȭ �Լ�
void AnimBackground::Init()
{
    position = { 0,0 };    // ��� ��ġ �ʱ�ȭ
    speed = 10;            // ��� �̵� �ӵ� ����

    // ��� ���������� �̹��� ���� �ʱ�ȭ
    for (int i = 0; i < Stage::Stagelength; ++i) vImages[i] = {};

    // ��� �̹��� ���� �� �ε�
    Image* background = new Image();
    if (FAILED(background->Init(L"Image/backGroundAnimation.bmp", 800, 5376, 1, 16, FALSE, FALSE))) {
        MessageBox(g_hWnd, L"backGroundAnimation ���� �ε忡 ����", L"���", MB_OK);
    }

    // �������� 1�� ��� �̹��� �߰�
    vImages[Stage::Stage1].push_back(background);

    // ���� ���������� ������ �ε��� �ʱ�ȭ
    curStage = Stage::Stage1;
    frameIdx = -1;  // -1�� ���� �ִϸ��̼��� ���۵��� �ʾ����� �ǹ�
}

// �ڿ� ���� �Լ�
void AnimBackground::Release()
{
    // ��� ���������� ��� �̹��� �޸� ����
    for (auto images : vImages) {
        for (auto i : images) {
            i->Release();   // �̹��� ���ҽ� ����
            delete i;       // ���� �Ҵ� �޸� ����
            i = NULL;       // ������ �ʱ�ȭ
        }
    }
}

// ��� ������Ʈ �Լ�
void AnimBackground::Update()
{
    Animate();  // �ִϸ��̼� ó��
}

// �ִϸ��̼� ó�� �Լ�
void AnimBackground::Animate()
{
    frameIdx++;  // ������ �ε��� ����

    int size = vImages[curStage].size();  // ���� ���������� �̹��� ����
    if (size > 0) {
        if (size != 1) {
            // ���� �̹����� ������ �ִϸ��̼��� ���
            frameIdx %= size;  // �̹��� ������ �°� �ε��� ��ȯ
        }
        else if (size == 1) {
            // ���� �̹����� ��������Ʈ �ִϸ��̼��� ���
            int sn = vImages[curStage][0]->GetSpritesNumX() * vImages[curStage][0]->GetSpritesNumY();  // �� ��������Ʈ �� ���
            frameIdx %= sn;  // ��������Ʈ ���� �°� �ε��� ��ȯ
        }
    }
    else frameIdx = -1;  // �̹����� ������ ������ �ε��� �ʱ�ȭ
}

// ��� ������ �Լ�
void AnimBackground::Render(HDC hdc)
{
    if (frameIdx == -1) return;  // ��ȿ�� �������� ������ ������ �ߴ�

    int size = vImages[curStage].size();  // ���� ���������� �̹��� ����
    if (size == 1)
        // ���� �̹����� ���, ������ ũ�⿡ �°� ��������Ʈ ������
        vImages[curStage][0]->Render(hdc, position.x, position.y, WINSIZE_X, WINSIZE_Y, frameIdx);
    // ���� �̹����� ��쿡 ���� ó���� ���� (�ڵ忡�� ������)
}
