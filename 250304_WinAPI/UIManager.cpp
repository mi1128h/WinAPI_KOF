#include "UIManager.h"
#include "AnimCharacter.h" 
#include "Image.h"

void UIManager::Init()
{
    FPOINT PlayerHpbarPos = { 50.f, 50.f };
    FPOINT EnemyHpbarPos = { 700.f, 50.f };

    maxHP = 10;
    playerHP = 10;
    enemyHP = 10;

    playerScore = 0;
    enemyScore = 0;

    vUiImages.resize(Ui::Uilength); 
    Image* advImages = new Image();
    if (FAILED(advImages->Init(L"Image/ImageUI/UiAdvanced.bmp", 490, 33, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"UiAdvanced 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::Advanced].push_back(advImages); 
    
    Image* CharacterSelectFrontUi = new Image();  //테스트 characterSelectionUi front
    if (FAILED(CharacterSelectFrontUi->Init(L"Image/ImageUI/CharacterSelectFrontUi.bmp", 302* 3.7 , 104*3.7 , 1, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"CharacterSelectFrontUi 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::StartUiFront].push_back(CharacterSelectFrontUi);

        Image* CharacterSelectUi = new Image();  //테스트 characterSelectionUi
    if (FAILED(CharacterSelectUi->Init(L"Image/ImageUI/CharacterSelectUi.bmp", 302* 3.7 , 227*3.7 , 1, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"CharacterSelectUi 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::StartUi].push_back(CharacterSelectUi);

    float LeftRightImageSz = 1.2;
    Image* leftImages = new Image(); //테스트 왼쪽hp캐릭터 ui
    if (FAILED(leftImages->Init(L"Image/ImageUI/LeftUi.bmp", 264* LeftRightImageSz, 41* LeftRightImageSz, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"LeftUi 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::LeftUi].push_back(leftImages);

    Image* rightImages = new Image(); //테스트 오른쪽hp캐릭터 ui
    if (FAILED(rightImages->Init(L"Image/ImageUI/RightUi.bmp", 264* LeftRightImageSz, 41* LeftRightImageSz, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"RightUi 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::RightUi].push_back(rightImages);

    Image* infinityUI = new Image(); //테스트 센터 시간무한 ui
    if (FAILED(infinityUI->Init(L"Image/ImageUI/infinityUI.bmp", 268*0.5, 256*0.5, 1, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"infinityUI 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::infinityUi].push_back(infinityUI);
}

void UIManager::Release()
{
    ReleaseInstance();
}

void UIManager::Update(AnimCharacter* leftPlayer, AnimCharacter* rightPlayer)
{
    if (leftPlayer) playerHP = leftPlayer->GetHp();
    if (rightPlayer) enemyHP = rightPlayer->GetHp();
    Animate();

}

void UIManager::Render(HDC hdc)
{
  
    UIManager::HpRender(hdc);
    UIManager::advRender(hdc);
    UIManager::SteminaRender(hdc);

    //left, right Character UI
    vUiImages[Ui::LeftUi][0]-> Render(hdc, 20, 5, -1, -1, frameIdx, 0);
    vUiImages[Ui::RightUi][0]->Render(hdc, WINSIZE_X - 70, 5, -1, -1, frameIdx, 1);


    vUiImages[Ui::infinityUi][0]->Render(hdc, WINSIZE_X / 2 - 60, -30, -1, -1, frameIdx, 1);


    
    //---------- 캐릭터 선택 ----------------------
    vUiImages[StartUi][0]->Render(hdc, 0, 0, -1, -1, frameIdx, 1);
    vUiImages[Ui::StartUiFront][0]->Render(hdc, 0, 0, -1, -1, frameIdx, 0);
}


void UIManager::Animate()
{
    frameIdx++;
    int imagesNum = vUiImages[curUi].size();
    if (imagesNum > 0) {
        int framesNum{ 1 };
        if (imagesNum != 1) {
            framesNum = imagesNum;
        }
        else if (imagesNum == 1) {
            int sn = vUiImages[curUi][0]->GetSpritesNumX() * vUiImages[curUi][0]->GetSpritesNumY();
            framesNum = sn;
        }
        frameIdx %= framesNum;
    }
    else frameIdx = -1;
}

void UIManager::advRender(HDC hdc)
{
    int leftadvPosX = 50;
    int rightadvPosX = WINSIZE_X - 150;
    int advPosY = WINSIZE_Y - 90;

    if (frameIdx == -1) return;
    vUiImages[curUi][0]->Render(hdc, leftadvPosX, advPosY, -1, -1, frameIdx, 0);
   
    vUiImages[curUi][0]->Render(hdc, rightadvPosX, advPosY, -1, -1, frameIdx, 0);

    
}

void UIManager::HpRender(HDC hdc)
{
    int barWidth = 400;
    int barHeight = 30;
    int paddingX = 50;
    int paddingY = 20;

    // 플레이어 HP 바 (왼쪽)
    Rectangle(hdc, paddingX, paddingY, paddingX + barWidth, paddingY + barHeight);
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0)); // 초록색 (플레이어)
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Rectangle(hdc, paddingX, paddingY, paddingX + (int)(barWidth * (playerHP / 10.0f)), paddingY + barHeight);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);


    // 플레이어 HP바(오른쪽)
    int enemyBarX = WINSIZE_X - barWidth - paddingX;
    Rectangle(hdc, enemyBarX, paddingY, enemyBarX + barWidth, paddingY + barHeight);
    hBrush = CreateSolidBrush(RGB(50, 50, 200));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    //반대로 차게
    Rectangle(hdc, enemyBarX + (barWidth - (int)(barWidth * (enemyHP / 10.0f))),
        paddingY,
        enemyBarX + barWidth,
        paddingY + barHeight);

    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);

}

void UIManager::SteminaRender(HDC hdc)
{
    int barWidth = 300;
    int barHeight = 20;
    int paddingX = 50;
    int paddingY = WINSIZE_Y-50;

    // 플레이어 스테미나 바 (왼쪽)
    Rectangle(hdc, paddingX, paddingY, paddingX + barWidth, paddingY + barHeight);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0)); // 초록색 (플레이어)
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Rectangle(hdc, paddingX, paddingY, paddingX + (int)(barWidth * (playerStamina / 10.0f)), paddingY + barHeight);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);


    // 플레이어 스테미나바(오른쪽)
    int enemyBarX = WINSIZE_X - barWidth - paddingX;
    Rectangle(hdc, enemyBarX, paddingY, enemyBarX + barWidth, paddingY + barHeight);
    hBrush = CreateSolidBrush(RGB(255, 255, 0));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    //반대로 차게
    Rectangle(hdc, enemyBarX + (barWidth - (int)(barWidth * (enemyStamina / 10.0f))),
        paddingY,
        enemyBarX + barWidth,
        paddingY + barHeight);

    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);

}
