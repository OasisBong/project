#pragma once
#include "stdafx.h"

struct PC_SKILL
{
	LPCSTR		m_sSkillName;		//스킬명
	float		m_CoolTime;			//스킬 대기 시간
	float		m_DelayTime;		//스킬 딜레이 시간
	float		m_PassedTime;		//스킬 구현 시간
};