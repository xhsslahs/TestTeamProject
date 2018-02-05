#pragma once
#include "Animation.h"

class Image
{
private:
	HDC hMemDC;				//메모리DC
	HBITMAP hBit, hOldBit;	//비트맵
	int width;				//이미지 가로크기
	int height;				//이미지 세로크기
	int currentFrameX;		//현재 프레임 값
	int currentFrameY;
	int maxFrameX;			//최대 프레임 번호
	int maxFrameY;
	int frameWidth;			//프레임 한장 크기
	int frameHeight;

	TCHAR* fileName;
	BOOL isTrans;
	COLORREF transColor;

	BLENDFUNCTION blendFunc;
	HDC hAlphaMemDC;
	HBITMAP hAlphaBit;

public :
	Image();

	void Init(const TCHAR* _fileName, int _width, int _height,
		BOOL _isTrans = FALSE, COLORREF _transColor = FALSE);
	void Init(const TCHAR* _fileName, int _width, int _height,
		int _maxFrameX, int _maxFrameY, BOOL _isTrans = FALSE, COLORREF _transColor = FALSE);

	void Release();

	void SetTransColor(BOOL _isTrans, COLORREF _transColor);

	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int frameX, int frameY);

	void AlphaRender(HDC hdc, int destX, int destY, int alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int frameX, int frameY, int alpha);

	void AniRender(HDC hdc, int destX, int destY, Animation* ani);

	inline int GetW(){ return width;}
	inline int GetH() { return height; }
	inline int GetFrameW() { return frameWidth; }
	inline int GetFrameH() { return frameHeight; }
	inline int GetFrameX() { return currentFrameX; }
	inline int GetFrameY() { return currentFrameY; }
	inline void SetFrameX(int x) { currentFrameX = x; }
	inline void SetFrameY(int y) { currentFrameY = y; }
	inline int GetMaxFrameX() { return maxFrameX; }
	inline int GetMaxFrameY() { return maxFrameY; }
	inline HDC GetMemDC() { return hMemDC; }
};