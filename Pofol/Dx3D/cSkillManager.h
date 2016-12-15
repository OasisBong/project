#pragma once

#include "stdafx.h"
#include "hStruct.h"

#define g_pSkillManager cSkillManager::GetInstance()

class cSkillManager
{
private:
	std::map<std::string, PC_SKILL*> m_mapSkillinfo;

public:
	SINGLETONE(cSkillManager);
	
	void Destroy();
	//PC_SKILL SkillSetup(char* name, int AniNum, float Movement, float CoolTime, float DelayTime, float PassedTime);
};