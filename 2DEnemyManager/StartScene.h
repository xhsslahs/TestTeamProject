#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};