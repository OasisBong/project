
#include "stdafx.h"
#include "cKeyManager.h"

cKeyManager::cKeyManager()
{
}
cKeyManager::~cKeyManager()
{
}

//키매니져 초기화
HRESULT cKeyManager::init(void)
{
	//키값을 전부 눌려있지 않은 상태로 초기화 한다.
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp.set(i, false);
		_keyDown.set(i, false);
	}

	return S_OK;
}

//키가 한번만 눌렸냐?
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
//키가 한번 눌렸다 띄었냐?
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
//키가 계속눌려있냐?
bool cKeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}
//키가 토글이냐?
bool cKeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}