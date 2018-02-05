#include "stdafx.h"

void StartScene::Init()
{

}

void StartScene::Release()
{
}

void StartScene::Update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->ChangeScene("∞‘¿”");
	}
}

void StartScene::Render(HDC hdc)
{

}
