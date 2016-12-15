#pragma once
//#include "stdafx.h"
#include "hStruct.h"
#include "cItemBase.h"
#include "cOBB.h"
#include "cLongSword.h"
#include "cSmallShield.h"
#include "cSkinnedMesh.h"

//class cSkinnedMesh;

struct AniINFO {
	string	 AniName;
	float	 period;
	int		 index;
};

class cFiona
{
private:
	//케릭터 상태
	PC_DIR								m_eDir;
	SYNTHESIZE(PC_STATE, m_eState, State);

private:
	SYNTHESIZE(PC_ATTACK, m_eAttack, AtkState);
	SYNTHESIZE(PC_SMASH, m_eSmash, SmashState);

	//케릭터 이미지 & 애니메이션
	float								m_fMaxPeriod;
	std::map<std::string, AniINFO*>		 m_mapAnimation;
	std::map<std::string, PC_SKILL*>	m_mapSkill;

	//케릭터 능력치
	SYNTHESIZE(PC_Statuse, m_sStatuse, Statuse);

	//아이템 및 장착
	D3DXMATRIXA16*						m_matLeftHand;
	D3DXMATRIXA16*						m_matRightHand;
	//std::map<std::string, cItemBase*>	m_mapEquip;	
	//cInventory

	//아이템 테스트
	cLongSword*				m_sword;
	cSmallShield*			m_shield;

	//충돌 박스
	SYNTHESIZE(cOBB*, m_cBox, Box);

	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);
	SYNTHESIZE_PASS_BY_REF(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);

	//DEBUG용
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3*, m_pBoxPos, BoxPos);

public:
	cFiona();
	~cFiona();

	void Setup();
	void Update(int AniIndex, D3DXMATRIXA16* matWorld);
	void Render();

	//Animation 관련
	void AnimationSetup();
	void ChangeAnimation(int index, PC_ATTACK nexState);
//	int FindIndexByName(char* AniName);

	//스킬 관련
	void AtkCombo(float& Period);
	void SmashCombo();
	void SetSkill();
	void SkillSetup(std::string name, float Movement, float CoolTime, float DelayTime);// , float PassedTime);
	
	//Item 관련
	void FindFrame(D3DXMATRIXA16** matrix, string frameName, ST_BONE* frame);
};

