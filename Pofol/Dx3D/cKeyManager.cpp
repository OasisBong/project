
#include "stdafx.h"
#include "cKeyManager.h"

cKeyManager::cKeyManager()
{
}
cKeyManager::~cKeyManager()
{
}

//Ű�Ŵ��� �ʱ�ȭ
HRESULT cKeyManager::init(void)
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
bool cKeyManager::isOnceKeyDown(int key)
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
bool cKeyManager::isOnceKeyUp(int key)
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
bool cKeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}
//Ű�� ����̳�?
bool cKeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}