#include "stdafx.h"

#include "hStruct.h"
#include "cSkillManager.h"

cSkillManager::cSkillManager(void)
{
}

cSkillManager::~cSkillManager(void)
{
}

void cSkillManager::Destroy()
{
	for each(auto it in m_mapSkillinfo)
	{
		SAFE_DELETE(it.second);
	}
}

//PS_SKILL cSkillManager::SkillSetup(char* name, int AniNum, float Movement, float CoolTime, float DelayTime, float PassedTime)
//{
//	if (m_mapSkillinfo.find(name) == m_mapSkillinfo.end())
//	{
//		PC_SKILL* temp;
//		temp->m_sSkillName = name;
//		temp->m_Aninum = AniNum;
//		temp->m_CoolTime = CoolTime;
//		temp->m_DelayTime = DelayTime;
//		temp->m_Movement = Movement;
//		temp->m_PassedTime = PassedTime;
//
//		m_mapSkillinfo[name] = temp;
//	}
//
//	return m_mapSkillinfo[name];
//}
