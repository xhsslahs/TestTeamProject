#include "stdafx.h"
#include "Timer.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

void Timer::Init()
{
	//고해상도 타이머의 진동수
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		//타이머 주기
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		isHardware = false;

		lastTime = timeGetTime();
		timeScale = 0.001f;
	}

	frameRate = 0;
	FPSframeCount = 0;
	FPSTimeElapsed = 0;
	worldTime = 0;
}

void Timer::Tick(float lockFPS)
{
	if (isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	}
	else
	{
		curTime = timeGetTime();
	}

	timeElapsed = (curTime - lastTime) * timeScale;

	if (lockFPS > 0)
	{
		while (timeElapsed < (1.0f / lockFPS))
		{
			if (isHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			}
			else
			{
				curTime = timeGetTime();
			}

			timeElapsed = (curTime - lastTime) * timeScale;
		}
	}

	lastTime = curTime;
	FPSframeCount++;
	FPSTimeElapsed += timeElapsed;
	worldTime += timeElapsed;

	if (FPSTimeElapsed > 1.0f)
	{
		frameRate = FPSframeCount;
		FPSframeCount = 0;
		FPSTimeElapsed = 0;
	}
}
