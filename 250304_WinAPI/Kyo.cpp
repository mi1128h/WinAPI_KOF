#include "Kyo.h"
#include "Image.h"
#include "config.h"
#include "CommonFunction.h"

void Kyo::Init()
{
    position = { 600,200 };
    speed = 300;

    dx = 0.0f;
    dy = 0.0f;
    size = 2.0f;
    hp = 10.f; //추가됨
    stamina = 5.f;

    for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

    Image* idleImages = new Image();

    if (FAILED(idleImages->Init(L"Image/ImageKyo/Kyo_Idle.bmp", 200*10, 200, 10, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_idle 파일 로드에 실패", L"경고", MB_OK);

    }
    vImages[State::Idle].push_back(idleImages);
    animTime[State::Idle] = 1.0f;

    Image* walkImages = new Image();

    if (FAILED(walkImages->Init(L"Image/ImageKyo/Kyo_Walk.bmp", 200*5, 200, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_walk 파일 로드에 실패", L"경고", MB_OK);
    }   
    vImages[State::Walk].push_back(walkImages);

    animTime[State::Walk] = 0.5f;

    Image* backWalkImages = new Image();
    if (FAILED(backWalkImages->Init(L"Image/ImageKyo/Kyo_BackWalk.bmp", 200*6, 200, 6, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"kyo_backwalk 파일 로드에 실패", L"경고", MB_OK);
    }   
    vImages[State::BackWalk].push_back(backWalkImages);
    animTime[State::BackWalk] = 0.5f;


    //---------공격--------------
    Image* strongPunchImages = new Image();
    if (FAILED(strongPunchImages->Init(L"Image/ImageKyo/Kyo_strongPunch.bmp", 200*8, 200, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_strongPunch 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongHand].push_back(strongPunchImages); 
    animTime[State::StrongHand] = 0.7f;
    
    Image* weakPunchImages = new Image();

    if (FAILED(weakPunchImages->Init(L"Image/ImageKyo/Kyo_weakPunch.bmp", 200*5, 200, 5, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_weakPunch 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::WeakHand].push_back(weakPunchImages);
    animTime[State::WeakHand] = 0.3f;

    Image* strongKickImages = new Image();

    if (FAILED(strongKickImages->Init(L"Image/ImageKyo/Kyo_strongKick.bmp", 200*11, 200, 11, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_strongKick파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::StrongFoot].push_back(strongKickImages);
    animTime[State::StrongFoot] = 1.f;

    Image* weakKickImages = new Image();

    if (FAILED(weakKickImages->Init(L"Image/ImageKyo/Kyo_weakKick.bmp", 200*9, 200, 9, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_weakKick 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::WeakFoot].push_back(weakKickImages);
	animTime[State::WeakFoot] = 1.f;



    //------------맞기-----------
	Image* weakDamageImages = new Image();
	if (FAILED(weakDamageImages->Init(L"Image/ImageKyo/Kyo_WeakHurt.bmp", 136, 116, 2, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"Kyo_Hurt 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::WeakDamaged].push_back(weakDamageImages);
	animTime[State::WeakDamaged] = 0.5f;


	Image* StrongDamageImages = new Image();
	if (FAILED(StrongDamageImages->Init(L"Image/ImageKyo/Kyo_Hurt.bmp", 272, 116, 4, 1, true, RGB(255, 0, 255)))) {
		MessageBox(g_hWnd, L"Kyo_Hurt 파일 로드에 실패", L"경고", MB_OK);
	}
	vImages[State::StrongDamaged].push_back(StrongDamageImages);
	animTime[State::StrongDamaged] = 0.3f;


    Image* defendImages = new Image();
    if (FAILED(defendImages->Init(L"Image/ImageKyo/Kyo_defendOneFrame.bmp", 111, 116, 1, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_defendOneFrame 파일 로드에 실패", L"경고", MB_OK);
    }
    vImages[State::Defend].push_back(defendImages);
    animTime[State::Defend] = 1.f;


    //----------스킬-----------
    Image* Kyo_skill500 = new Image();
    if (FAILED(Kyo_skill500->Init(L"Image/ImageKyo/Kyo_skill500.bmp", 16000, 157, 50, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_skill50 파일 로드 실패", L"경고", MB_OK);
    }
    vImages[State::Skill].push_back(Kyo_skill500);
    animTime[State::Skill] = 3.3f;


    //----------die-----------
    Image* KyoDead = new Image();
    if (FAILED(KyoDead->Init(L"Image/ImageKyo/Kyo_Dead.bmp", 1305, 170, 8, 1, true, RGB(255, 0, 255)))) {
        MessageBox(g_hWnd, L"Kyo_Dead 파일 로드 실패", L"경고", MB_OK);
    }
    vImages[State::Dead].push_back(KyoDead);
    animTime[State::Dead] = 1.0f;


    curState = State::Idle;
    frameIdx = 0;
    defaultFlip = flip = false;
    offset = 10;

}

void Kyo::Action()
{
	hurtBox = GetRect(position.x - 35*size, position.y - 115*size, 70*size, 115*size);

    switch (curState)
    {
    case WeakHand:
        hitBox = GetRect(0, 0, 0, 0);

        if (frameIdx == 1)
        {
            if (flip == defaultFlip)
            {
                hitBox = GetRect(position.x, position.y - 95 * size, 65 * size, 15 * size);

            }
            else
            {
                hitBox = GetRect(position.x - 65 * size, position.y - 95 * size, 65 * size, 15 * size);

            }
        }

        break;
    case StrongHand:
        hitBox = GetRect(0, 0, 0, 0);

        if (frameIdx == 3 || frameIdx == 4)
        {
            if (flip == defaultFlip)
            {
                hitBox = GetRect(position.x, position.y - 90 * size, 75 * size, 17 * size);

            }
            else
            {
                hitBox = GetRect(position.x - 75 * size, position.y - 90 * size, 75 * size, 17 * size);

            }
        }

        break;
    case WeakFoot:
        hitBox = GetRect(0, 0, 0, 0);

        if (frameIdx == 2 || frameIdx == 3 || frameIdx == 4)
        {
            if (flip == defaultFlip)
            {
                hitBox = GetRect(position.x, position.y - 85 * size, 110 * size, 22 * size);

            }
            else
            {
                hitBox = GetRect(position.x - 110 * size, position.y - 85 * size, 110 * size, 22 * size);

            }
        }
		
		break;
	case StrongFoot:
        hitBox = GetRect(0, 0, 0, 0);

        if (frameIdx == 5)
        {
            if (flip == defaultFlip)
            {
                hitBox = GetRect(position.x, position.y - 75 * size, 90 * size, 20 * size);

            }
            else
            {
                hitBox = GetRect(position.x - 90 * size, position.y - 75 * size, 90 * size, 20 * size);

            }
        }
		
		break;
    case Skill:
        hitBox = GetRect(0, 0, 0, 0);
        if (frameIdx >= 33 && frameIdx <= 45)
        {
            if (flip == defaultFlip)
            {
                hitBox = GetRect(position.x, position.y - 100 * size, 160 * size, 60 * size);

            }
            else
            {
                hitBox = GetRect(position.x - 90 * size, position.y - 75 * size, 90 * size, 20 * size);

            }
        }
        break;
    case Dead:
        hurtBox = GetRect(1, 1, 1, 1);
        break;
	default:
		hitBox = GetRect(0, 0, 0, 0);
		isSuccessHit = false;
		break;
	}
}