#pragma once
#include "config.h"

class Image
{
public :
	enum IMAGE_LOAD_TYPE
	{
		Resource,	// 프로젝트 자체에 포함 시킬 이미지
		File,		// 외부에서 로드할 이미지
		Empty,		// 자체 생산할 이미지
		End
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// 리소스의 고유 ID
		HDC hMemDC;			// 그리기를 주관하는 객체 핸들
		HBITMAP hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		HDC hTempDC;
		HBITMAP hTempBit;
		HBITMAP hOldTemp;
		int width;			// 이미지 가로 크기
		int height;			// 이미지 세로 크기
		BYTE loadType;		// 로드 타입
		int spritesNum[2];	// 가로 세로 스프라이트 개수

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			hTempDC = NULL;
			hTempBit = NULL;
			hOldTemp = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_TYPE::Empty;
			spritesNum[0] = 1;
			spritesNum[1] = 1;
		}
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;	// LPIMAGE_INFO imageInfo
	bool isTransparent;
	COLORREF tansColor;

public:
	// 빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const wchar_t* filePath, int width, int height,
		int spritesNumX = 1, int spritesNumY = 1, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// 화면에 출력
	void Render(HDC hdc, int destX = 0, int destY = 0, bool flip = false);
	void Render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int frameIndex, bool flip = false);
	
	// 메모리 해제
	void Release();

	inline HDC GetMemDC() { if (imageInfo) return imageInfo->hMemDC; else return NULL; }
	inline int GetWidth() { if (imageInfo) return imageInfo->width; else return -1; }
	inline int GetHeight() { if (imageInfo) return imageInfo->height; else return -1; }
	inline int GetSpritesNumX() { if (imageInfo) return imageInfo->spritesNum[0]; else return -1; }
	inline int GetSpritesNumY() { if (imageInfo) return imageInfo->spritesNum[1]; else return -1; }
};

