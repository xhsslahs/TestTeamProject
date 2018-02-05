#include "stdafx.h"
#include "GameNode.h"

void GameNode::Init()
{
	//SetTimer(hWnd, 1, 10, NULL);
	SetBackBuffer();
	TIMEMANAGER->Init();
	SOUNDMANAGER->Init();
	KEYMANAGER->Init();	
	SCENEMANAGER->Init();
}

void GameNode::Update() //WM_TIMER
{
	InvalidateRect(hWnd, NULL, false);
	TIMEMANAGER->Update(60);
}

void GameNode::Render(HDC hdc)
{

}

void GameNode::Release()
{
	//KillTimer(hWnd, 1);
}

void GameNode::SetBackBuffer()
{
	backBuffer = new BackBuffer;
	backBuffer->Init(WINWIDTH, WINHEIGHT);
}

LRESULT GameNode::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		//this->Init();
		break;
	case WM_TIMER:
		this->Update();
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		this->Render(hdc);

		EndPaint(hWnd, &ps);
	}
	case WM_MOUSEMOVE:
	{
		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);
	}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hWnd, message, wParam, lParam));
}
