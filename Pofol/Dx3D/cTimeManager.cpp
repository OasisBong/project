#include "StdAfx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager(void)
{
	m_dwLastTimeStamp = GetTickCount();
}


cTimeManager::~cTimeManager(void)
{
}

void cTimeManager::Update()
{
	DWORD dwCurrTime = GetTickCount();
	m_dwDeltaTime = dwCurrTime - m_dwLastTimeStamp;
	m_dwLastTimeStamp = dwCurrTime;
}

float cTimeManager::GetDeltaTime()
{
	return m_dwDeltaTime / 1000.f;
}
