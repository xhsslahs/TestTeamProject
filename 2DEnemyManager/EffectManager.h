#pragma once
#include "SingletonBase.h"

class Effect;

class EffectManager : public SingletoneBase<EffectManager>
{
private:
	//map<string, vector<Effect*>> totalEffect;
	typedef vector<Effect*> vEffect;
	map<string, vEffect> totalEffect;

public:
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEffect(string effectName, const TCHAR* imageName,
		int imageWidth, int imageHeight, int frameX, int frameY,
		int fps, int buffer, COLORREF color);

	void Play(string effectName, int x, int y);
	void Play(string effectName, POINT pos);
};