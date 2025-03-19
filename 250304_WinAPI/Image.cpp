#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);
	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_TYPE::Empty;
	imageInfo->spritesNum[0] = 1;
	imageInfo->spritesNum[1] = 1;
	
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) {
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height,
	int spritesNumX, int spritesNumY, bool isTransparent, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);
	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hTempBit = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_TYPE::File;
	imageInfo->spritesNum[0] = spritesNumX;
	imageInfo->spritesNum[1] = spritesNumY;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) {
		Release();
		return E_FAIL;
	}

	this->isTransparent = isTransparent;
	this->tansColor = transColor;

	return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY, bool flip)
{
	BitBlt(
		hdc,				// 복사 목적지 DC
		destX, destY,		// 복사 목적지 위치
		imageInfo->width,	// 원본에서 복사될 가로 크기
		imageInfo->height,	// 원본에서 복사될 세로 크기
		imageInfo->hMemDC,	// 원본 DC
		0, 0,				// 원본 복사 시작 위치
		SRCCOPY);			// 복사 옵션
}

void Image::Render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int frameIndex, bool flip)
{
	int x = frameIndex % imageInfo->spritesNum[0];
	int y = frameIndex / imageInfo->spritesNum[0];

	int srcX{}, srcY{};
	int srcWidth{}, srcHeight{};
	srcX = imageInfo->width / imageInfo->spritesNum[0] * x;
	srcY = imageInfo->height / imageInfo->spritesNum[1] * y;
	srcWidth = imageInfo->width / imageInfo->spritesNum[0];
	srcHeight = imageInfo->height / imageInfo->spritesNum[1];
	if (flip) {
		srcX += srcWidth - 1;
		srcWidth *= -1;
	}

	imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);
	
	if (isTransparent) {
		StretchBlt(
			imageInfo->hTempDC,
			0, 0,
			abs(srcWidth), abs(srcHeight),
			imageInfo->hMemDC,
			srcX, srcY,
			srcWidth, srcHeight,
			SRCCOPY);

		TransparentBlt(
			hdc,
			destX, destY,
			destWidth, destHeight,
			imageInfo->hTempDC,
			0, 0,
			abs(srcWidth), abs(srcHeight),
			tansColor);
	}
	else {
		StretchBlt(
			hdc,
			destX, destY,
			destWidth, destHeight,
			imageInfo->hMemDC,
			srcX, srcY,
			srcWidth, srcHeight,
			SRCCOPY);
	}

	SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
}

void Image::Release()
{
	if (imageInfo) {
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
		DeleteObject(imageInfo->hTempBit);
		DeleteDC(imageInfo->hTempDC);

		delete imageInfo;
		imageInfo = NULL;
	}
}
