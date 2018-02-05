#include "stdafx.h"

BackBuffer::BackBuffer()
{
	hMemDC = NULL;
	hBit = NULL;
	hOldBit = NULL;
	width = 0;
	height = 0;
}

void BackBuffer::Init(int _width, int _height)
{
	HDC hdc = GetDC(hWnd);

	hMemDC = CreateCompatibleDC(hdc);
	hBit = CreateCompatibleBitmap(hdc, _width, _height);
	hOldBit = (HBITMAP)SelectObject(hMemDC, hBit);
	width = _width;
	height = _height;

	ReleaseDC(hWnd, hdc);
}

void BackBuffer::Release()
{
	SelectObject(hMemDC, hOldBit);
	DeleteObject(hBit);
	DeleteDC(hMemDC);
}

void BackBuffer::Render(HDC hdc)
{
	BitBlt(hdc, 0, 0,
		width, height,
		hMemDC,
		0, 0,
		SRCCOPY);
}
