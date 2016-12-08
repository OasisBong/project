#pragma once
#include "stdafx.h"


enum PC_DIR
{
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

enum PC_STATE
{
	IDEL,
	MOVE,
	ATTECT,
	GUARD,
	LIFT,
	TIRD,
	DAMAGED,
	DOWN,
};

enum PC_ATTACK
{
	ATTACK_0,
	ATTACK_1,
	ATTACK_2,
	ATTACK_3,
	ATTACK_4
};

enum PC_SMASH
{
	SMASH_0,
	SMASH_1,
	SMASH_2,
	SMASH_3,
};

struct PC_Statuse {
	float m_maxHP;
	float m_currentHP;
	
	float m_maxMP;
	float m_currentMP;
	
	float m_maxSP;
	float m_currentSP;

	float m_fAtk;	//공격
	float m_fDef;	//방어
	float m_fAgl;	//공속
};

struct PC_SKILL
{
	LPCSTR		m_sSkillName;		//스킬명
	float		m_CoolTime;			//스킬 대기 시간
	float		m_DelayTime;		//스킬 딜레이 시간
	float		m_PassedTime;		//스킬 구현 시간
};
