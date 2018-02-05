#include "stdafx.h"
#include "GameScene.h"

void GameScene::Init()
{
	IMAGEMANAGER->AddFrameImage("enemy", L"image/ufo.bmp", 530, 32,
		10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("bullet", L"image/ball.bmp", 30, 30, true, RGB(255, 0, 255));
	em = new EnemyManager;
	em->SetEnemy();
}

void GameScene::Release()
{

}

void GameScene::Update()
{
	em->Update();
}

void GameScene::Render(HDC hdc)
{
	IMAGEMANAGER->Render("bg", hdc, 0, 0);
	em->Render(hdc);	
}
