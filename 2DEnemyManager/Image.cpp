#include "stdafx.h"

Image::Image()
{
	hMemDC = NULL;
	hBit = NULL;
	hOldBit = NULL;
	width = 0;
	height = 0;
	currentFrameX = 0;
	currentFrameY = 0;
	maxFrameX = 0;
	maxFrameY = 0;
	frameWidth = 0;
	frameHeight = 0;

	fileName = NULL;
	isTrans = false;
	transColor = RGB(0, 0, 0);
}

void Image::Init(const TCHAR* _fileName, int _width, int _height, BOOL _isTrans, COLORREF _transColor)
{
	HDC hdc = GetDC(hWnd);

	hMemDC = CreateCompatibleDC(hdc);	
	hBit = (HBITMAP)LoadImage(hInst, _fileName, IMAGE_BITMAP,
		_width, _height, LR_LOADFROMFILE);
	hOldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	width = _width;
	height = _height;
	
	int len = wcslen(_fileName);

	fileName = new TCHAR[len + 1];
	wcscpy_s(fileName, len + 1, _fileName);

	isTrans = _isTrans;
	transColor = _transColor;

	//���ĺ��� ����
	hAlphaMemDC = CreateCompatibleDC(hdc);
	hAlphaBit = CreateCompatibleBitmap(hdc, WINWIDTH, WINHEIGHT);
	hOldBit = (HBITMAP)SelectObject(hAlphaMemDC, hAlphaBit);

	ReleaseDC(hWnd, hdc);
}

void Image::Init(const TCHAR * _fileName, int _width, int _height, int _maxFrameX, int _maxFrameY, BOOL _isTrans, COLORREF _transColor)
{
	HDC hdc = GetDC(hWnd);

	hMemDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)LoadImage(hInst, _fileName, IMAGE_BITMAP,
		_width, _height, LR_LOADFROMFILE);
	hOldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	width = _width;
	height = _height;
	frameWidth = _width / _maxFrameX;
	frameHeight = _height / _maxFrameY;
	maxFrameX = _maxFrameX;
	maxFrameY = _maxFrameY;
	
	int len = wcslen(_fileName);

	fileName = new TCHAR[len + 1];
	wcscpy_s(fileName, len + 1, _fileName);

	isTrans = _isTrans;
	transColor = _transColor;

	//���ĺ��� ����
	hAlphaMemDC = CreateCompatibleDC(hdc);
	hAlphaBit = CreateCompatibleBitmap(hdc, WINWIDTH, WINHEIGHT);
	hOldBit = (HBITMAP)SelectObject(hAlphaMemDC, hAlphaBit);

	ReleaseDC(hWnd, hdc);
}

void Image::Release()
{
	SelectObject(hMemDC, hOldBit);
	DeleteObject(hBit);
	DeleteDC(hMemDC);

	delete[] fileName;
}

void Image::SetTransColor(BOOL _isTrans, COLORREF _transColor)
{
	isTrans = _isTrans;
	transColor = _transColor;
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,	//����� ������ DC
			destX,	//��µ� ��ǥ
			destY,
			width,	//��µ� ũ��
			height,
			hMemDC,	//������ DC
			0, 0,	//�����ؿ� ��ǥ
			width,	//�����ؿ� ũ��
			height,
			transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			width, height, hMemDC,
			0, 0, SRCCOPY);
	}
}

void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,	//����� ������ DC
			destX,	//��µ� ��ǥ
			destY,
			frameWidth,	//��µ� ũ��
			frameHeight,
			hMemDC,	//������ DC
			frameWidth	* frameX,	//�����ؿ� ��ǥ
			frameHeight * frameY,	
			frameWidth,	//�����ؿ� ũ��
			frameHeight,
			transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			frameWidth, frameHeight,
			hMemDC,
			frameWidth * frameX,
			frameHeight * frameY,
			SRCCOPY);
	}
}
//alpha : 0~255���� (0�̸� ����, 255�� ������)
void Image::AlphaRender(HDC hdc, int destX, int destY, int alpha)
{
	blendFunc.SourceConstantAlpha = (BYTE)alpha;

	if (isTrans)
	{
		BitBlt(hAlphaMemDC, 0, 0, width, height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(hAlphaMemDC, 0, 0, width, height,
			hMemDC, 0, 0, width, height, transColor);

		GdiAlphaBlend(hdc, destX, destY, width, height,
			hAlphaMemDC, 0, 0, width, height, blendFunc);
	}
	else
	{
		GdiAlphaBlend(hdc,
			destX, destY,
			width, height,	//����� ũ��
			hMemDC,			//������ �޸�DC
			0, 0,			//������ DC���� ���� ��ǥ
			width, height,	//������ DC���� ���� �� ũ��
			blendFunc
		);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, int frameX, int frameY, int alpha)
{
	blendFunc.SourceConstantAlpha = (BYTE)alpha;

	if (isTrans)
	{
		BitBlt(hAlphaMemDC, 0, 0, width, height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(
			hAlphaMemDC,	//�̹����� ���� DC
			0, 0,			//���� ��ġ
			frameWidth, frameHeight,	//������ �̹��� ũ��
			hMemDC,			//���(������ DC)
			frameWidth * frameX,	//������ DC���� ������ ��ǥ
			frameHeight * frameY,
			frameWidth, frameHeight,	//������ DC���� ������ ũ��
			transColor);

		GdiAlphaBlend(hdc, destX, destY,
			frameWidth, frameHeight,
			hAlphaMemDC, 0, 0, 
			frameWidth, frameHeight,
			blendFunc);
	}
	else
	{
		GdiAlphaBlend(hdc,
			destX, destY,
			frameWidth, frameHeight,	//����� ũ��
			hMemDC,			//������ �޸�DC
			frameWidth*frameX, frameHeight*frameY,			//������ DC���� ���� ��ǥ
			frameWidth, frameHeight,	//������ DC���� ���� �� ũ��
			blendFunc
		);
	}
}

void Image::AniRender(HDC hdc, int destX, int destY, Animation * ani)
{	
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,	//����� ������ DC
			destX,	//��µ� ��ǥ
			destY,
			frameWidth,	//��µ� ũ��
			frameHeight,
			hMemDC,	//������ DC
			ani->GetFramePos().x,	//�����ؿ� ��ǥ
			ani->GetFramePos().y,
			frameWidth,	//�����ؿ� ũ��
			frameHeight,
			transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			frameWidth, frameHeight,
			hMemDC,
			ani->GetFramePos().x,	//�����ؿ� ��ǥ
			ani->GetFramePos().y,
			SRCCOPY);
	}
}
