#include "Kyo.h"
#include "Image.h"
#include "config.h"
#include "CommonFunction.h"

void Kyo::Init()
{
    position = { 600,200 };
    speed = 100;

    dx = 0.0f;
    dy = 0.0f;
    hp = 10.f; //Ãß°¡µÊ

    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    Image* idleImages = new Image();

    if (FAILED(idleImages->Init(L"Image/ImageKyo/Kyo_Idle.bmp", 200*10, 200, 10, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_idle ?Œì¼ ë¡œë“œ???¤íŒ¨", L"ê²½ê³ ", MB_OK);

    }
    vImages[State::Idle].push_back(idleImages);
    animTime[State::Idle] = 1.0f;

    Image* walkImages = new Image();

    if (FAILED(walkImages->Init(L"Image/ImageKyo/Kyo_Walk.bmp", 200*5, 200, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_walk ?Œì¼ ë¡œë“œ???¤íŒ¨", L"ê²½ê³ ", MB_OK);
    }   
    vImages[State::Walk].push_back(walkImages);
    animTime[State::Walk] = 1.0f;

    Image* backWalkImages = new Image();
    if (FAILED(backWalkImages->Init(L"Image/ImageKyo/Kyo_BackWalk.bmp", 200*6, 200, 6, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_backwalk ÆÄÀÏ ·Îµå¿¡ ½ÇÆÐ", L"°æ°í", MB_OK);
    }   
    vImages[State::BackWalk].push_back(backWalkImages);
    animTime[State::BackWalk] = 1.0f;

    Image* strongPunchImages = new Image();
    if (FAILED(strongPunchImages->Init(L"Image/ImageKyo/Kyo_strongPunch.bmp", 200*8, 200, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_strongPunch ?Œì¼ ë¡œë“œ???¤íŒ¨", L"ê²½ê³ ", MB_OK);
    }
    vImages[State::StrongHand].push_back(strongPunchImages); 
    animTime[State::StrongHand] = 1.0f;
    
    Image* weakPunchImages = new Image();

    if (FAILED(weakPunchImages->Init(L"Image/ImageKyo/Kyo_weakPunch.bmp", 200*5, 200, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_weakPunch ?Œì¼ ë¡œë“œ???¤íŒ¨", L"ê²½ê³ ", MB_OK);
    }
    vImages[State::WeakHand].push_back(weakPunchImages);
    animTime[State::WeakHand] = 0.3f;

    Image* strongKickImages = new Image();

    if (FAILED(strongKickImages->Init(L"Image/ImageKyo/Kyo_strongKick.bmp", 200*11, 200, 11, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_strongKick?Œì¼ ë¡œë“œ???¤íŒ¨", L"ê²½ê³ ", MB_OK);
    }
    vImages[State::StrongFoot].push_back(strongKickImages);
    animTime[State::StrongFoot] = 1.5f;

    Image* weakKickImages = new Image();

    if (FAILED(weakKickImages->Init(L"Image/ImageKyo/Kyo_weakKick.bmp", 200*9, 200, 9, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_weakKick ?Œì¼ ë¡œë“œ???¤íŒ¨", L"ê²½ê³ ", MB_OK);
    }
    vImages[State::WeakFoot].push_back(weakKickImages);
	animTime[State::WeakFoot] = 1.5f;

	Image* weakDamageImages = new Image();
	if (FAILED(weakDamageImages->Init(L"Image/Kim/kim_weakdamage.bmp", 256 * 2, 256, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot ÆÄÀÏ ·Îµå¿¡ ½ÇÆÐ", L"°æ°í", MB_OK);
	}
	vImages[State::WeakDamaged].push_back(weakDamageImages);
	animTime[State::WeakDamaged] = 1.f;

	Image* StrongDamageImages = new Image();
	if (FAILED(StrongDamageImages->Init(L"Image/Kim/kim_strongdamage.bmp", 256 * 3, 256, 3, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"bluemary_strongfoot ÆÄÀÏ ·Îµå¿¡ ½ÇÆÐ", L"°æ°í", MB_OK);
	}
	vImages[State::StrongDamaged].push_back(StrongDamageImages);
	animTime[State::StrongDamaged] = 1.f;



    curState = State::Idle;
    frameIdx = 0;
    defaultFlip = flip = false;
    offset = 20;

}

void Kyo::Action()
{
	hurtBox = GetRect(position.x - 70, position.y - 230, 140, 230);

	switch (curState)
	{
	case WeakHand:
		
			hitBox = GetRect(position.x , position.y - 190, 130, 30);

		break;
	case StrongHand:
		
			hitBox = GetRect(position.x, position.y - 180, 150, 35);
		
		break;
	case WeakFoot:
		
			hitBox = GetRect(position.x, position.y - 170, 220, 45);
		
		break;
	case StrongFoot:
		
			hitBox = GetRect(position.x, position.y - 150, 180, 40);
		
		break;
	case WeakDamaged:
		break;
	case StrongDamaged:
		break;
	default:
		hitBox = GetRect(0, 0, 0, 0);
		isSuccessHit = false;
		break;
	}
}