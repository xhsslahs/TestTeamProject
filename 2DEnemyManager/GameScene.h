#pragma once
#include "GameNode.h"


class GameScene : public GameNode
{
private:

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};