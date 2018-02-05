#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:	
	
public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};