#pragma once
#include "SingletonBase.h"
#include <bitset>

using namespace std;

#define KEYMAX 256

class KeyManager : public SingletoneBase<KeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	void Init()
	{
		for (int i = 0; i < KEYMAX; i++)
		{
			this->GetKeyUp().set(i, false);
			this->GetKeyDown().set(i, false);
		}
	}

	bitset<KEYMAX> GetKeyUp()
	{
		return _keyUp;
	}

	bitset<KEYMAX> GetKeyDown()
	{
		return _keyDown;
	}

	void SetKeyDown(int key, bool state)
	{
		_keyDown.set(key, state);
	}

	void SetKeyUp(int key, bool state)
	{
		_keyUp.set(key, state);
	}

	//Ű�� �ѹ� ������ ó��
	bool isOnceKeyDown(int key)
	{
		if (GetAsyncKeyState(key) & 0x8000)
		{
			if (!this->GetKeyDown()[key])
			{
				this->SetKeyDown(key, true);
				return true;
			}
		}
		else
		{
			this->SetKeyDown(key, false);
		}

		return false;
	}

	//Ű �ѹ� ���� �� ó��
	bool isOnceKeyUp(int key)
	{
		if (GetAsyncKeyState(key) & 0x8000)
		{
			this->SetKeyUp(key, true);
		}
		else
		{
			if (this->GetKeyUp()[key])
			{
				this->SetKeyUp(key, false);
				return true;
			}
		}

		return false;
	}

	//������ ���� �� ó��
	bool isStayKeyDown(int key)
	{
		if (GetAsyncKeyState(key) & 0x8000)
			return true;
		else
			return false;
	}
};