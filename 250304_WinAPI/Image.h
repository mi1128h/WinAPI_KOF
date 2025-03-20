#pragma once
#include "config.h"

class Image
{
public :
	enum IMAGE_LOAD_TYPE
	{
		Resource,	// ������Ʈ ��ü�� ���� ��ų �̹���
		File,		// �ܺο��� �ε��� �̹���
		Empty,		// ��ü ������ �̹���
		End
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// ���ҽ��� ���� ID
		HDC hMemDC;			// �׸��⸦ �ְ��ϴ� ��ü �ڵ�
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		HDC hTempDC;
		HBITMAP hTempBit;
		HBITMAP hOldTemp;
		int width;			// �̹��� ���� ũ��
		int height;			// �̹��� ���� ũ��
		BYTE loadType;		// �ε� Ÿ��
		int spritesNum[2];	// ���� ���� ��������Ʈ ����

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
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const wchar_t* filePath, int width, int height,
		int spritesNumX = 1, int spritesNumY = 1, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ȭ�鿡 ���
	void Render(HDC hdc, int destX = 0, int destY = 0, bool flip = false);
	void Render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int frameIndex, bool flip = false);
	void RenderCenter(HDC hdc, int destX, int destY, int destWidth, int destHeight, int frameIndex, bool flip = false, int offset=0);
	
	// �޸� ����
	void Release();

	inline HDC GetMemDC() { if (imageInfo) return imageInfo->hMemDC; else return NULL; }
	inline int GetWidth() { if (imageInfo) return imageInfo->width; else return -1; }
	inline int GetHeight() { if (imageInfo) return imageInfo->height; else return -1; }
	inline int GetSpritesNumX() { if (imageInfo) return imageInfo->spritesNum[0]; else return -1; }
	inline int GetSpritesNumY() { if (imageInfo) return imageInfo->spritesNum[1]; else return -1; }
};

