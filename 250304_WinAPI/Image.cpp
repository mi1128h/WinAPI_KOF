#include "Image.h"

// 이미지 초기화 함수 - 빈 이미지 생성
// width, height: 생성할 이미지의 크기
HRESULT Image::Init(int width, int height)
{
    // 윈도우의 DC를 가져옴
    HDC hdc = GetDC(g_hWnd);

    // 이미지 정보 구조체 할당
    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;                                       // 리소스 ID 초기화
    imageInfo->hMemDC = CreateCompatibleDC(hdc);                // 메모리 DC 생성
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height); // 비트맵 생성
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap); // 비트맵을 DC에 선택

    // 임시 DC와 비트맵 생성 (투명 처리용)
    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    // 이미지 속성 설정
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::Empty;    // 빈 이미지 타입
    imageInfo->spritesNum[0] = 1;                    // 스프라이트 수 X 방향
    imageInfo->spritesNum[1] = 1;                    // 스프라이트 수 Y 방향

    // 사용 완료한 DC 해제
    ReleaseDC(g_hWnd, hdc);

    // 비트맵 생성 실패 시 에러 반환
    if (imageInfo->hBitmap == NULL) {
        Release();
        return E_FAIL;
    }
    return S_OK;   // 성공
}

// 이미지 초기화 함수 - 파일에서 이미지 로드
// filePath: 파일 경로, width/height: 이미지 크기
// spritesNumX/Y: X/Y 방향 스프라이트 수
// isTransparent: 투명 처리 여부, transColor: 투명색
HRESULT Image::Init(const wchar_t* filePath, int width, int height,
    int spritesNumX, int spritesNumY, bool isTransparent, COLORREF transColor)
{
    // 윈도우의 DC를 가져옴
    HDC hdc = GetDC(g_hWnd);

    // 이미지 정보 구조체 할당
    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;                    // 리소스 ID 초기화
    imageInfo->hMemDC = CreateCompatibleDC(hdc);    // 메모리 DC 생성

    // 파일에서 비트맵 로드
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    // 임시 DC와 비트맵 생성 (투명 처리용)
    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    // 이미지 속성 설정
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;    // 파일 로드 타입
    imageInfo->spritesNum[0] = spritesNumX;         // X 방향 스프라이트 수
    imageInfo->spritesNum[1] = spritesNumY;         // Y 방향 스프라이트 수

    // 사용 완료한 DC 해제
    ReleaseDC(g_hWnd, hdc);

    // 비트맵 로드 실패 시 에러 반환
    if (imageInfo->hBitmap == NULL) {
        Release();
        return E_FAIL;
    }

    // 투명 처리 관련 속성 설정
    this->isTransparent = isTransparent;
    this->tansColor = transColor;

    return S_OK;   // 성공
}

// 이미지 렌더링 함수 - 기본 렌더링
// hdc: 대상 DC, destX/Y: 그릴 위치, flip: 좌우 반전 여부
void Image::Render(HDC hdc, int destX, int destY, bool flip)
{
    BitBlt(
        hdc,                // 복사 목적지 DC
        destX, destY,       // 복사 목적지 위치
        imageInfo->width,   // 원본에서 복사될 가로 크기
        imageInfo->height,  // 원본에서 복사될 세로 크기
        imageInfo->hMemDC,  // 원본 DC
        0, 0,               // 원본 복사 시작 위치
        SRCCOPY);           // 복사 옵션
}

// 이미지 렌더링 함수 - 스프라이트 렌더링
// hdc: 대상 DC, destX/Y: 그릴 위치, destWidth/Height: 그릴 크기
// frameIndex: 스프라이트 프레임 인덱스, flip: 좌우 반전 여부
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

	if (destWidth == -1) destWidth = srcWidth;
	if (destHeight == -1) destHeight = srcHeight;

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

// 이미지 리소스 해제 함수
void Image::Release()
{
    if (imageInfo) {
        // 메모리 DC 복원 및 해제
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        // 임시 DC 복원 및 해제
        SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
        DeleteObject(imageInfo->hTempBit);
        DeleteDC(imageInfo->hTempDC);

        // 이미지 정보 구조체 해제
        delete imageInfo;
        imageInfo = NULL;
    }
}
