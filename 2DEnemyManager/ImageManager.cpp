#include "stdafx.h"

Image * ImageManager::AddImage(string strKey, const TCHAR * fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img)
		return img;

	img = new Image;
	img->Init(fileName, width, height, trans, transColor);

	imageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddFrameImage(string strKey, const TCHAR * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img)
		return img;

	img = new Image;
	img->Init(fileName, width, height, frameX, frameY, 
		trans, transColor);

	imageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::FindImage(string strKey)
{
	map<string, Image*>::iterator it;
	it = imageList.find(strKey);

	//이미지 키가 있을 경우
	if (it != imageList.end())
	{
		return it->second;
	}

	return NULL;
}

void ImageManager::DeleteAll()
{
	//map<string, Image*>::iterator it = imageList.begin();
	map<string, Image*>::iterator it;

	for (it = imageList.begin() ; it != imageList.end();)
	{
		if (it->second != NULL)
		{
			delete it->second;
			it = imageList.erase(it);
		}
		else
		{
			it++;
		}
	}

	imageList.clear();
}

void ImageManager::DeleteImage(string strKey)
{
	map<string, Image*>::iterator it = imageList.find(strKey);

	if (it != imageList.end())
	{
		it->second->Release();
		delete it->second;
		imageList.erase(it);
		return;
	}
}

void ImageManager::Release()
{
	DeleteAll();
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = FindImage(strKey);

	if (img)
		img->Render(hdc, destX, destY);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY)
{
	Image* img = FindImage(strKey);

	if (img)
		img->Render(hdc, destX, destY, frameX, frameY);
}
