#pragma once
#include "singletonBase.h"
#include "bitset"
using namespace std;
//==================================================================
//		## cKeyManager ## (Ű�Ŵ���)
//==================================================================

#define KEYMAX 256

class cKeyManager : public singletonBase <cKeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	//Ű�Ŵ��� �ʱ�ȭ
	HRESULT init(void);

	//Ű�� �ѹ��� ���ȳ�?
	bool isOnceKeyDown(int key);
	//Ű�� �ѹ� ���ȴ� �����?
	bool isOnceKeyUp(int key);
	//Ű�� ��Ӵ����ֳ�?
	bool isStayKeyDown(int key);
	//Ű�� ����̳�?
	bool isToggleKey(int key);
	

	cKeyManager();
	~cKeyManager();
};

