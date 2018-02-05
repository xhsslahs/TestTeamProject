#pragma once

class Effect
{
private:
	POINT pos;
	Image* image;
	Animation* ani;
	bool isRun;
	float elapsedTime;

public:
	Effect();
	void Init(Image* effectImage, int frameW, int frameH,
		int fps, float elapsedTime);
	void Init(Image* effectImage, int fps);

	void Release();
	void Update();
	void Render(HDC hdc);

	void StartEffect(POINT pos);
	void KillEffect();

	bool GetIsRun() { return isRun; }
};