#pragma once
#include "SingletonBase.h"
#include "Image.h"
#include <map>

using namespace std;

class ImageManager : public SingletoneBase<ImageManager>
{
private:
	map<string, Image*> imageList;

public :
	Image* AddImage(string strKey, const TCHAR* fileName,
		int width, int height, bool trans = false,
		COLORREF transColor = NULL);
	Image* AddFrameImage(string strKey, const TCHAR* fileName,
		int width, int height, int frameX, int frameY,
		bool trans = false, COLORREF transColor = NULL);

	Image* FindImage(string strKey);

	void DeleteAll();
	void DeleteImage(string strKey);
	void Release();

	void Render(string strKey, HDC hdc, int destX, int destY);
	void Render(string strKey, HDC hdc, int destX, int destY,
		int frameX, int frameY);
};