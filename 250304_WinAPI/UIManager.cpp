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

   
     Image* HpUi = new Image(); //hp바
    if (FAILED(HpUi->Init(L"Image/ImageUI/HPbar.bmp", 264, 41, 1, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"HPbar 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::HpUi].push_back(HpUi);

    float LeftRightImageSz = 1.2;
    Image* leftImages = new Image(); //테스트 왼쪽hp캐릭터 ui
    if (FAILED(leftImages->Init(L"Image/ImageUI/LeftUi.bmp", 264* LeftRightImageSz, 41* LeftRightImageSz, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"LeftUi 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::LeftUi].push_back(leftImages);


    Image* BackWindow = new Image(); //backwindow 뒷그림
    if (FAILED(BackWindow->Init(L"Image/ImageUI/BackWindow.bmp",61 , 42*1.6, 1, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"BackWindow 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::BackWindow].push_back(BackWindow);


    Image* rightImages = new Image(); //테스트 오른쪽hp캐릭터 ui
    if (FAILED(rightImages->Init(L"Image/ImageUI/RightUi.bmp", 264* LeftRightImageSz, 41* LeftRightImageSz, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"RightUi 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::RightUi].push_back(rightImages);


    Image* infinityUI = new Image(); //테스트 센터 시간무한 ui
    if (FAILED(infinityUI->Init(L"Image/ImageUI/infinityUI.bmp", 268*0.3, 256*0.3, 1, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"infinityUI 파일 로드에 실패", L"경고", MB_OK);
    }
    vUiImages[Ui::infinityUi].push_back(infinityUI);
    
    


}

void UIManager::Release()
{
    ReleaseInstance();
}

void UIManager::Update(AnimCharacter* leftPlayer, AnimCharacter* rightPlayer, float elapsedTime)
{
    if (leftPlayer){
        playerHP = leftPlayer->GetHp();
        playerStamina = leftPlayer->GetStamina();

    }
    if (rightPlayer) {

        enemyHP = rightPlayer->GetHp();
        enemyStamina = rightPlayer->GetHp();
    }
    
    Animate(elapsedTime);

}

void UIManager::Render(HDC hdc)
{
  
    UIManager::HpRender(hdc);
    UIManager::advRender(hdc);
    UIManager::SteminaRender(hdc);

    //left, right Character UI
    vUiImages[Ui::BackWindow][0]-> Render(hdc, 10, 0, -1, -1, 0 , 1);
    vUiImages[Ui::LeftUi][0]-> Render(hdc, 20, 5, -1, -1, frameIdx, 0);

    vUiImages[Ui::BackWindow][0]->Render(hdc, WINSIZE_X - 80, 0, -1, -1, frameIdx, 1);
    vUiImages[Ui::RightUi][0]->Render(hdc, WINSIZE_X - 70, 5, -1, -1, frameIdx, 1);


    vUiImages[Ui::infinityUi][0]->Render(hdc, WINSIZE_X / 2 -30 , -10, -1, -1, frameIdx, 1);
   

    
    //---------- 스타트 스크린 ----------------------
    if (drawFirstScreen) UIManager::StartRender(hdc);

    
}


void UIManager::Animate(float elapsedTime)
{


    accumTime += elapsedTime;
    int imagesNum = vUiImages[curUi].size();
    if (imagesNum > 0) {
        // get total frameNum
        int framesNum{ 1 };
        if (imagesNum != 1) {
            framesNum = imagesNum;
        }
        else if (imagesNum == 1) {
            int sn = vUiImages[curUi][0]->GetSpritesNumX() * vUiImages[curUi][0]->GetSpritesNumY();
            framesNum = sn;
        }
        // calculate frameIdx
        int temp = frameIdx;
        int frame = accumTime * framesNum / animTime;
        frameIdx = frame % framesNum;
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
    int barHeight = 15;
    int paddingX = 50;
    int paddingY = 20;
    int borderThickness = 3; // 테두리 두께

    int playerHpWidth = (int)(barWidth * (playerHP / 10.0f));
    int enemyBarX = WINSIZE_X - barWidth - paddingX;
    int enemyHpWidth = (int)(barWidth * (enemyHP / 10.0f));

    HPEN borderPen = CreatePen(PS_SOLID, borderThickness, RGB(255, 255, 255)); // 흰색 테두리 펜
    HPEN oldPen = (HPEN)SelectObject(hdc, borderPen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));  // 내부 투명 처리

    Rectangle(hdc, paddingX - borderThickness, paddingY - borderThickness,
        paddingX + barWidth + borderThickness, paddingY + barHeight + borderThickness);
    
    Rectangle(hdc, enemyBarX - borderThickness, paddingY - borderThickness,
        enemyBarX + barWidth + borderThickness, paddingY + barHeight + borderThickness);

    // 원래 펜과 브러시로 복구
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(borderPen);

    if (playerHpWidth > 0)
    {
        TRIVERTEX vertex[2] = {
            { paddingX, paddingY, 0x0000, 0xC000, 0x0000, 0x0000 }, // 연한 초록색
            { paddingX + playerHpWidth, paddingY + barHeight, 0x0000, 0x4000, 0x0000, 0x0000 } // 진한 초록색
        };
        GRADIENT_RECT pGradientRect = { 0, 1 };
        GradientFill(hdc, vertex, 2, &pGradientRect, 1, GRADIENT_FILL_RECT_H);
    }

    if (enemyHpWidth > 0)
    {
        TRIVERTEX enemyVertex[2] = {
            { enemyBarX + (barWidth - enemyHpWidth), paddingY, 0x0000, 0x0000, 0xC000, 0x0000 }, // 연한 파란색
            { enemyBarX + barWidth, paddingY + barHeight, 0x0000, 0x0000, 0x4000, 0x0000 } // 진한 파란색
        };
        GRADIENT_RECT eGradientRect = { 0, 1 };
        GradientFill(hdc, enemyVertex, 2, &eGradientRect, 1, GRADIENT_FILL_RECT_H);
    }
}

void UIManager::StartRender(HDC hdc)
{
    vUiImages[StartUi][0]->Render(hdc, 0, 0, -1, -1, frameIdx, 1);
    vUiImages[Ui::StartUiFront][0]->Render(hdc, 0, StartUiFrontY, -1, -1, frameIdx, 0);
    --StartUiFrontY;
    if (StartUiFrontY < -500) StartUiFrontY = 500;
}

void UIManager::SteminaRender(HDC hdc)
{
    int barWidth = 300;
    int barHeight = 20;
    int paddingX = 50;
    int paddingY = WINSIZE_Y - 50;
    int borderThickness = 2; // 테두리 두께

    int playerStaminaWidth = (int)(barWidth * (playerStamina / 10.0f));
    int enemyBarX = WINSIZE_X - barWidth - paddingX;
    int enemyStaminaWidth = (int)(barWidth * (enemyStamina / 10.0f));

    HPEN borderPen = CreatePen(PS_SOLID, borderThickness, RGB(255, 255, 255));
    HPEN oldPen = (HPEN)SelectObject(hdc, borderPen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH)); // 내부 투명

    Rectangle(hdc, paddingX - borderThickness, paddingY - borderThickness,
        paddingX + barWidth + borderThickness, paddingY + barHeight + borderThickness);

    Rectangle(hdc, enemyBarX - borderThickness, paddingY - borderThickness,
        enemyBarX + barWidth + borderThickness, paddingY + barHeight + borderThickness);

    // 원래 펜과 브러시로 복구
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(borderPen);

    if (playerStaminaWidth > 0)
    {
        TRIVERTEX vertex[2] = {
            { paddingX, paddingY, 0xC000, 0xC000, 0x0000, 0x0000 }, // 연한 노란색
            { paddingX + playerStaminaWidth, paddingY + barHeight, 0x8000, 0x8000, 0x0000, 0x0000 } // 진한 노란색
        };
        GRADIENT_RECT pGradientRect = { 0, 1 };
        GradientFill(hdc, vertex, 2, &pGradientRect, 1, GRADIENT_FILL_RECT_H);
    }

    if (enemyStaminaWidth > 0)
    {
        TRIVERTEX enemyVertex[2] = {
            { enemyBarX + (barWidth - enemyStaminaWidth), paddingY, 0xC000, 0xC000, 0x0000, 0x0000 }, // 연한 노란색
            { enemyBarX + barWidth, paddingY + barHeight, 0x8000, 0x8000, 0x0000, 0x0000 } // 진한 노란색
        };
        GRADIENT_RECT eGradientRect = { 0, 1 };
        GradientFill(hdc, enemyVertex, 2, &eGradientRect, 1, GRADIENT_FILL_RECT_H);
    }
}

