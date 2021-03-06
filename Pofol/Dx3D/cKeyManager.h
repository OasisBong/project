#pragma once
#include "singletonBase.h"
#include "bitset"
using namespace std;
//==================================================================
//		## cKeyManager ## (키매니져)
//==================================================================

#define KEYMANAGER cKeyManager::getSingleton()

#define KEYMAX 256

class cKeyManager : public singletonBase <cKeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	//키매니져 초기화
	HRESULT init(void);

	//키가 한번만 눌렸냐?
	bool isOnceKeyDown(int key);
	//키가 한번 눌렸다 띄었냐?
	bool isOnceKeyUp(int key);
	//키가 계속눌려있냐?
	bool isStayKeyDown(int key);
	//키가 토글이냐?
	bool isToggleKey(int key);
	

	cKeyManager();
	~cKeyManager();
};

