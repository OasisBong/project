#include "KeyManager.h"
#include "stdafx.h"
KeyManager::KeyManager()
{
}
KeyManager::~KeyManager()
{
}

//Ű�Ŵ��� �ʱ�ȭ
HRESULT KeyManager::init(void)
{
	//Ű���� ���� �������� ���� ���·� �ʱ�ȭ �Ѵ�.
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp.set(i, false);
		_keyDown.set(i, false);
	}

	return S_OK;
}

//Ű�� �ѹ��� ���ȳ�?
bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		_keyDown.set(key, false);
	}

	return false;
}
//Ű�� �ѹ� ���ȴ� �����?
bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp.set(key, true);
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp.set(key, false);
			return true;
		}
	}

	return false;
}
//Ű�� ��Ӵ����ֳ�?
bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}
//Ű�� ����̳�?
bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}