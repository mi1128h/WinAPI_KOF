#include "Image.h"

// �̹��� �ʱ�ȭ �Լ� - �� �̹��� ����
// width, height: ������ �̹����� ũ��
HRESULT Image::Init(int width, int height)
{
    // �������� DC�� ������
    HDC hdc = GetDC(g_hWnd);

    // �̹��� ���� ����ü �Ҵ�
    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;                                       // ���ҽ� ID �ʱ�ȭ
    imageInfo->hMemDC = CreateCompatibleDC(hdc);                // �޸� DC ����
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height); // ��Ʈ�� ����
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap); // ��Ʈ���� DC�� ����

    // �ӽ� DC�� ��Ʈ�� ���� (���� ó����)
    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    // �̹��� �Ӽ� ����
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::Empty;    // �� �̹��� Ÿ��
    imageInfo->spritesNum[0] = 1;                    // ��������Ʈ �� X ����
    imageInfo->spritesNum[1] = 1;                    // ��������Ʈ �� Y ����

    // ��� �Ϸ��� DC ����
    ReleaseDC(g_hWnd, hdc);

    // ��Ʈ�� ���� ���� �� ���� ��ȯ
    if (imageInfo->hBitmap == NULL) {
        Release();
        return E_FAIL;
    }
    return S_OK;   // ����
}

// �̹��� �ʱ�ȭ �Լ� - ���Ͽ��� �̹��� �ε�
// filePath: ���� ���, width/height: �̹��� ũ��
// spritesNumX/Y: X/Y ���� ��������Ʈ ��
// isTransparent: ���� ó�� ����, transColor: �����
HRESULT Image::Init(const wchar_t* filePath, int width, int height,
    int spritesNumX, int spritesNumY, bool isTransparent, COLORREF transColor)
{
    // �������� DC�� ������
    HDC hdc = GetDC(g_hWnd);

    // �̹��� ���� ����ü �Ҵ�
    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;                    // ���ҽ� ID �ʱ�ȭ
    imageInfo->hMemDC = CreateCompatibleDC(hdc);    // �޸� DC ����

    // ���Ͽ��� ��Ʈ�� �ε�
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    // �ӽ� DC�� ��Ʈ�� ���� (���� ó����)
    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    // �̹��� �Ӽ� ����
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;    // ���� �ε� Ÿ��
    imageInfo->spritesNum[0] = spritesNumX;         // X ���� ��������Ʈ ��
    imageInfo->spritesNum[1] = spritesNumY;         // Y ���� ��������Ʈ ��

    // ��� �Ϸ��� DC ����
    ReleaseDC(g_hWnd, hdc);

    // ��Ʈ�� �ε� ���� �� ���� ��ȯ
    if (imageInfo->hBitmap == NULL) {
        Release();
        return E_FAIL;
    }

    // ���� ó�� ���� �Ӽ� ����
    this->isTransparent = isTransparent;
    this->tansColor = transColor;

    return S_OK;   // ����
}

// �̹��� ������ �Լ� - �⺻ ������
// hdc: ��� DC, destX/Y: �׸� ��ġ, flip: �¿� ���� ����
void Image::Render(HDC hdc, int destX, int destY, bool flip)
{
    BitBlt(
        hdc,                // ���� ������ DC
        destX, destY,       // ���� ������ ��ġ
        imageInfo->width,   // �������� ����� ���� ũ��
        imageInfo->height,  // �������� ����� ���� ũ��
        imageInfo->hMemDC,  // ���� DC
        0, 0,               // ���� ���� ���� ��ġ
        SRCCOPY);           // ���� �ɼ�
}

// �̹��� ������ �Լ� - ��������Ʈ ������
// hdc: ��� DC, destX/Y: �׸� ��ġ, destWidth/Height: �׸� ũ��
// frameIndex: ��������Ʈ ������ �ε���, flip: �¿� ���� ����
void Image::Render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int frameIndex, bool flip)
{
    // ������ �ε����κ��� ��������Ʈ ��Ʈ ��ǥ ���
    int x = frameIndex % imageInfo->spritesNum[0];
    int y = frameIndex / imageInfo->spritesNum[0];

    // �ҽ� �̹��� ���� ���
    int srcX{}, srcY{};
    int srcWidth{}, srcHeight{};
    srcX = imageInfo->width / imageInfo->spritesNum[0] * x;
    srcY = imageInfo->height / imageInfo->spritesNum[1] * y;
    srcWidth = imageInfo->width / imageInfo->spritesNum[0];
    srcHeight = imageInfo->height / imageInfo->spritesNum[1];

    // �¿� ���� ó��
    if (flip) {
        srcX += srcWidth - 1;
        srcWidth *= -1;
    }

    // �ӽ� DC ����
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    // ���� ó�� ���ο� ���� ������
    if (isTransparent) {
        // ���� ó�� ��, �ӽ� DC�� ���� �׸� �� ���� ó���Ͽ� ��� DC�� ����
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
            tansColor);  // ����� ����
    }
    else {
        // ���� ó�� ���� ���� ��Ʈ��ġ ��Ʈ��
        StretchBlt(
            hdc,
            destX, destY,
            destWidth, destHeight,
            imageInfo->hMemDC,
            srcX, srcY,
            srcWidth, srcHeight,
            SRCCOPY);
    }

    // �ӽ� DC ����
    SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
}

// �̹��� ���ҽ� ���� �Լ�
void Image::Release()
{
    if (imageInfo) {
        // �޸� DC ���� �� ����
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        // �ӽ� DC ���� �� ����
        SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
        DeleteObject(imageInfo->hTempBit);
        DeleteDC(imageInfo->hTempDC);

        // �̹��� ���� ����ü ����
        delete imageInfo;
        imageInfo = NULL;
    }
}
