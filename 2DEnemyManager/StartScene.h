#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:
	RECT btnRc;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};