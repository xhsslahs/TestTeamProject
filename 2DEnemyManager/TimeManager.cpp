#include "stdafx.h"

void TimeManager::Init()
{
	timer = new Timer;
	timer->Init();
}

void TimeManager::Release()
{
	if (timer != NULL)
	{
		delete timer;
		timer = NULL;
	}
}

void TimeManager::Update(float lock)
{
	if (timer != NULL)
	{
		timer->Tick(lock);
	}
}

void TimeManager::Render(HDC hdc)
{
	TCHAR str[100];

	//TextOut�� ����� �� �� ��� �����
	SetBkMode(hdc, TRANSPARENT);

	swprintf_s(str, L"FramePerSec(FPS) : %d", (int)timer->GetFrameRate());
	TextOut(hdc, 0, 0, str, wcslen(str));

	swprintf_s(str, L"WordTime : %.2f", timer->GetWorldTime());
	TextOut(hdc, 0, 20, str, wcslen(str));
}
