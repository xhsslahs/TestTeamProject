#pragma once

class GameNode
{
protected:
	BackBuffer* backBuffer;
public:
	virtual void Init();	//초기화 함수
	virtual void Update();	//연산부분
	virtual void Render(HDC hdc);	//그리는 함수
	virtual void Release();	//메모리 헤제 함수

	void SetBackBuffer();

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};
