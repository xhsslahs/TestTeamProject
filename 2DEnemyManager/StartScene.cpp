#include "stdafx.h"

void StartScene::Init()
{
	IMAGEMANAGER->AddImage("btn", L"image/button.bmp", 300, 300
		, true, RGB(255, 255, 255));

	btnRc.left = 200;
	btnRc.top = 200;
	btnRc.right = 500;
	btnRc.bottom = 500;
}

void StartScene::Release()
{
}

void StartScene::Update()
{
	if (PtInRect(&btnRc, mousePos))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->ChangeScene("����");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->ChangeScene("����");
	}
}

void StartScene::Render(HDC hdc)
{
	IMAGEMANAGER->Render("btn", hdc, 200, 200);
}
