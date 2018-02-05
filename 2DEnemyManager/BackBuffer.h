#pragma once


class BackBuffer
{
private:
	HDC hMemDC;
	HBITMAP hBit, hOldBit;
	int width;
	int height;

public:
	BackBuffer();
	void Init(int _width, int _height);
	void Release();
	void Render(HDC hdc);

	inline HDC GetMemDC()
	{
		if (this == NULL)
			return NULL;
		return hMemDC;
	}
};