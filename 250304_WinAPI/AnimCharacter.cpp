#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

// ĳ���� �ʱ�ȭ �Լ�
void AnimCharacter::Init()
{
    position = { 0,0 };  // �ʱ� ��ġ ����
    speed = 10;          // �̵� �ӵ� ����
    dx = 0.0f;           // X ���� �̵��� �ʱ�ȭ
    dy = 0.0f;           // Y ���� �̵��� �ʱ�ȭ

    // ��� ���º� �̹��� ���� �ʱ�ȭ
    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    // ���(Idle) ���� �̹��� �ε�
    Image* idleImages = new Image();
    if (FAILED(idleImages->Init(L"Image/iori_idle.bmp", 684, 104, 9, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"iori_idle ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::Idle].push_back(idleImages);

    // �ȱ�(Walk) ���� �̹��� �ε�
    Image* walkImages = new Image();
    if (FAILED(walkImages->Init(L"Image/iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"iori_walk ���� �ε忡 ����", L"���", MB_OK);
    }
    vImages[State::Walk].push_back(walkImages);

    // �ʱ� ���� �� ������ ����
    curState = State::Idle;  // �ʱ� ���´� ���
    frameIdx = 0;            // ������ �ε��� �ʱ�ȭ
    flip = false;            // �¿� ���� ����

    // ĳ���� ũ�� ��� (ù ��° Idle �̹��� ����)
    Image* img = vImages[State::Idle][0];
    size[0] = img->GetWidth() / img->GetSpritesNumX();     // �ʺ� ���
    size[1] = img->GetHeight() / img->GetSpritesNumY();    // ���� ���
}

// �ڿ� ���� �Լ�
void AnimCharacter::Release()
{
    // ��� ������ ��� �̹��� �޸� ����
    for (auto images : vImages) {
        for (auto i : images) {
            i->Release();   // �̹��� ���ҽ� ����
            delete i;       // ���� �Ҵ� �޸� ����
            i = NULL;       // ������ �ʱ�ȭ
        }
    }
}

// ������Ʈ �Լ�
void AnimCharacter::Update()
{
    Move();         // �̵� ó��
    ProcessInput(); // �Է� ó��
    Animate();      // �ִϸ��̼� ó��
}

// �Է� ó�� �Լ�
void AnimCharacter::ProcessInput()
{
    KeyManager* km = KeyManager::GetInstance();  // Ű �Ŵ��� �̱��� �ν��Ͻ� ȹ��
    int deltaX{}, deltaY{};  // �̵� ���� �ʱ�ȭ

    // ���� ���¿� ���� �Է� ó��
    switch (curState) {
    case State::Idle:  // ��� ������ ��
        // AŰ�� ������ �� �������� �̵�
        if (km->IsOnceKeyDown('a') or km->IsOnceKeyDown('A')) {
            deltaX -= 1;
        }
        // DŰ�� ������ �� ���������� �̵�
        if (km->IsOnceKeyDown('d') or km->IsOnceKeyDown('D')) {
            deltaX += 1;
        }
        // X�� �̵��� ������ �ȱ� ���·� ����
        if (deltaX != 0) SetState(State::Walk);
        break;

    case State::Walk:  // �ȱ� ������ ��
        // AŰ�� ������ ������ �������� �̵�
        if (km->IsStayKeyDown('a') or km->IsStayKeyDown('A')) {
            deltaX -= 1;
        }
        // DŰ�� ������ ������ ���������� �̵�
        if (km->IsStayKeyDown('d') or km->IsStayKeyDown('D')) {
            deltaX += 1;
        }
        // X�� �̵��� ������ ��� ���·� ����
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::W_punch:  // �� ��ġ ����
        if (km->IsStayKeyDown('u') or km->IsStayKeyDown('U')) {
            deltaX -= 1;
        }

        // X�� �̵��� ������ ��� ���·� ����
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::S_punch:  // �� ��ġ ������ ��
        if (km->IsStayKeyDown('i') or km->IsStayKeyDown('I')) {
            deltaX -= 1;
        }
     
        
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::W_kick:  // �� ű ������ ��
        if (km->IsStayKeyDown('j') or km->IsStayKeyDown('J')) {
            deltaX -= 1;
        }
        
        
        // X�� �̵��� ������ ��� ���·� ����
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::S_kick:  // �� ű ������ ��
        if (km->IsStayKeyDown('k') or km->IsStayKeyDown('K')) {
            deltaX -= 1;
        }
       
        
        if (deltaX == 0) SetState(State::Idle);
        break;

    case State::Dead:  // ��� ������ ��
        break;  // �ƹ� ó�� ����
    }

    // �̵� ���� ����
    SetDelta(deltaX, deltaY);
}

// �ִϸ��̼� ó�� �Լ�
void AnimCharacter::Animate()
{
    frameIdx++;  // ������ �ε��� ����

    int imagesNum = vImages[curState].size();  // ���� ������ �̹��� ����
    if (imagesNum > 0) {
        if (imagesNum != 1) {
            // ���� �̹����� ������ �ִϸ��̼��� ���
            frameIdx %= imagesNum;  // �̹��� ������ �°� �ε��� ��ȯ
        }
        else if (imagesNum == 1) {
            // ���� �̹����� ��������Ʈ �ִϸ��̼��� ���
            int sn = vImages[curState][0]->GetSpritesNumX() * vImages[curState][0]->GetSpritesNumY();  // �� ��������Ʈ �� ���
            frameIdx %= sn;  // ��������Ʈ ���� �°� �ε��� ��ȯ
        }
    }
    else frameIdx = -1;  // �̹����� ������ ������ �ε��� �ʱ�ȭ
}

// ������ �Լ�
void AnimCharacter::Render(HDC hdc)
{
    if (frameIdx == -1) return;  // ��ȿ�� �������� ������ ������ �ߴ�

    int imagesNum = vImages[curState].size();  // ���� ������ �̹��� ����
    if (imagesNum == 1) {
        // ���� �̹����� ��� (��������Ʈ��Ʈ)
        vImages[curState][0]->Render(hdc, position.x, position.y, size[0], size[1], frameIdx, flip);
    }
    else {
        // ���� �̹����� ���
        vImages[curState][frameIdx]->Render(hdc, position.x, position.y, size[0], size[1], 0, flip);
    }
}

// �̵� ó�� �Լ�
void AnimCharacter::Move()
{
    // ��ġ ������Ʈ
    position.x += dx * speed;  // X ��ġ ������Ʈ
    position.y += dy * speed;  // Y ��ġ ������Ʈ

    // Y ��ġ�� ȭ�� ���� ���� ����
    position.y = ClampVal(position.y, 0.0f, (float)WINSIZE_Y);

    // �̵� ���⿡ ���� �¿� ���� ����
    if (dx > 0) flip = false;  // ���������� �̵��ϸ� ���� ����
    if (dx < 0) flip = true;   // �������� �̵��ϸ� ����
}