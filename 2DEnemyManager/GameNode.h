#pragma once

class GameNode
{
protected:
	BackBuffer* backBuffer;
public:
	virtual void Init();	//�ʱ�ȭ �Լ�
	virtual void Update();	//����κ�
	virtual void Render(HDC hdc);	//�׸��� �Լ�
	virtual void Release();	//�޸� ���� �Լ�

	void SetBackBuffer();

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};
