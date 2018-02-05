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

	//알파블렌드 셋팅
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

	//알파블렌드 셋팅
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
			hdc,	//복사될 영역의 DC
			destX,	//출력될 좌표
			destY,
			width,	//출력될 크기
			height,
			hMemDC,	//복사할 DC
			0, 0,	//복사해올 좌표
			width,	//복사해올 크기
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
			hdc,	//복사될 영역의 DC
			destX,	//출력될 좌표
			destY,
			frameWidth,	//출력될 크기
			frameHeight,
			hMemDC,	//복사할 DC
			frameWidth	* frameX,	//복사해올 좌표
			frameHeight * frameY,	
			frameWidth,	//복사해올 크기
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
//alpha : 0~255까지 (0이면 투명, 255면 불투명)
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
			width, height,	//출력할 크기
			hMemDC,			//가져올 메모리DC
			0, 0,			//가져올 DC에서 복사 좌표
			width, height,	//가져올 DC에서 복사 할 크기
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
			hAlphaMemDC,	//이미지를 넣을 DC
			0, 0,			//넣을 위치
			frameWidth, frameHeight,	//가져올 이미지 크기
			hMemDC,			//어디서(가져올 DC)
			frameWidth * frameX,	//가져올 DC에서 복사할 좌표
			frameHeight * frameY,
			frameWidth, frameHeight,	//가져올 DC에서 복사할 크기
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
			frameWidth, frameHeight,	//출력할 크기
			hMemDC,			//가져올 메모리DC
			frameWidth*frameX, frameHeight*frameY,			//가져올 DC에서 복사 좌표
			frameWidth, frameHeight,	//가져올 DC에서 복사 할 크기
			blendFunc
		);
	}
}

void Image::AniRender(HDC hdc, int destX, int destY, Animation * ani)
{	
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,	//복사될 영역의 DC
			destX,	//출력될 좌표
			destY,
			frameWidth,	//출력될 크기
			frameHeight,
			hMemDC,	//복사할 DC
			ani->GetFramePos().x,	//복사해올 좌표
			ani->GetFramePos().y,
			frameWidth,	//복사해올 크기
			frameHeight,
			transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			frameWidth, frameHeight,
			hMemDC,
			ani->GetFramePos().x,	//복사해올 좌표
			ani->GetFramePos().y,
			SRCCOPY);
	}
}
