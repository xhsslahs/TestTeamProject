#pragma once
#include "SingletonBase.h"
#include "Timer.h"

class TimeManager : public SingletoneBase<TimeManager>
{
private:
	Timer* timer;

public:
	void Init();
	void Release();
	void Update(float lock = 0.0f);
	void Render(HDC hdc);

	inline float GetElapsedTime() { return timer->GetElapsedTime(); }
	inline float GetWorldTime() { return timer->GetWorldTime(); }
};