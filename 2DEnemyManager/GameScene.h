#pragma once
#include "GameNode.h"
#include "EnemyManager.h"

class GameScene : public GameNode
{
private:
	EnemyManager* em;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};