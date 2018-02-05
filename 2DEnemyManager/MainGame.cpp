#include "stdafx.h"
#include "MainGame.h"

void MainGame::Init()
{
	GameNode::Init();
	IMAGEMANAGER->AddImage("bg", L"image/background.bmp", WINWIDTH, WINHEIGHT);


	SCENEMANAGER->AddScene("��ŸƮ", new StartScene);
	SCENEMANAGER->AddScene("����", new GameScene);

	SCENEMANAGER->ChangeScene("��ŸƮ");
}

void MainGame::Update()
{	
	GameNode::Update();
	SCENEMANAGER->Update();
	EFFECTMANAGER->Update();
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = backBuffer->GetMemDC();
	if (backDC == NULL)
		return;
	PatBlt(backDC, 0, 0, WINWIDTH, WINHEIGHT, WHITENESS);
	//////////////////////////////////////////////////////
	
	SCENEMANAGER->Render(backDC);
	///////////////////////////////////////////////
	EFFECTMANAGER->Render(backDC);
	TIMEMANAGER->Render(backDC);
	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	GameNode::Release();

}