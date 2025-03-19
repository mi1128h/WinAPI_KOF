#pragma once
#include "GameObject.h"

class Tank;
class Enemy;
class RoundManager;
class Image;
class AnimCharacter;
class SherCharacter;
class AnimBackground;

class Kim;
class MainGame : public GameObject

{
private:
    HDC hdc{};            // ���� ��ġ ���ؽ�Ʈ (�׸����)
    PAINTSTRUCT ps{};      // ����Ʈ(�׸���) ���� ����
    HANDLE hTimer{}, hTimer2; // Ÿ�̸� �ڵ� (���� �̺�Ʈ ����)

    int mousePosX{}, mousePosY{}; // ���콺 ��ġ ����
    wchar_t szText[128]{};        // ȭ�鿡 ǥ���� �ؽ�Ʈ

    Tank* tank;           // �÷��̾ �����ϴ� ��ũ ��ü
    vector<Enemy*> enemies; // �� ĳ���� ����Ʈ (���� �Ҵ�)
    int nDeadEnemies;     // óġ�� �� �� ī��Ʈ


	Image* backBuffer;
	AnimCharacter* iori;
	Kim* kim;
	AnimBackground* background;


public:
    // ���� �ʱ�ȭ �Լ� (��ü ����, �ʱ� ����)
    void Init();

    // ���� ���� �� �޸� ���� (��ü ����)
    void Release();

    // ������ ���� ������Ʈ (���� ����, AI ���� ��)
    void Update();

    // ȭ�� ������ (�׸���)
    void Render(HDC hdc);

    // ����� ���� �Ǵ� �߰� UI ������
    void RenderInfo(HDC hdc);

    // ���ο� ���� �����ϴ� �Լ�
    void CreateEnemy();

    // ����ź�� ��ǥ�� �����ϴ� �Լ�
    void SetGuidedBulletsTarget();

    // ������ ������ϴ� �Լ�
    void RestartGame();

    // ������ ���� ������ ���ν��� (�Է� ó��)
    LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

    // ������ (��ü �ʱ�ȭ)
    MainGame();

    // �Ҹ��� (���� �޸� ����)
    ~MainGame();
};

