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
	//�ɸ��� ����
	PC_DIR								m_eDir;
	SYNTHESIZE(PC_STATE, m_eState, State);

private:
	SYNTHESIZE(PC_ATTACK, m_eAttack, AtkState);
	SYNTHESIZE(PC_SMASH, m_eSmash, SmashState);

	//�ɸ��� �̹��� & �ִϸ��̼�
	float								m_fMaxPeriod;
	std::map<std::string, AniINFO*>		 m_mapAnimation;
	std::map<std::string, PC_SKILL*>	m_mapSkill;

	//�ɸ��� �ɷ�ġ
	SYNTHESIZE(PC_Statuse, m_sStatuse, Statuse);

	//������ �� ����
	D3DXMATRIXA16*						m_matLeftHand;
	D3DXMATRIXA16*						m_matRightHand;
	//std::map<std::string, cItemBase*>	m_mapEquip;	
	//cInventory

	//������ �׽�Ʈ
	cLongSword*				m_sword;
	cSmallShield*			m_shield;

	//�浹 �ڽ�
	SYNTHESIZE(cOBB*, m_cBox, Box);

	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);
	SYNTHESIZE_PASS_BY_REF(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);

	//DEBUG��
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3*, m_pBoxPos, BoxPos);

public:
	cFiona();
	~cFiona();

	void Setup();
	void Update(int AniIndex, D3DXMATRIXA16* matWorld);
	void Render();

	//Animation ����
	void AnimationSetup();
	void ChangeAnimation(int index, PC_ATTACK nexState);
//	int FindIndexByName(char* AniName);

	//��ų ����
	void AtkCombo(float& Period);
	void SmashCombo();
	void SetSkill();
	void SkillSetup(std::string name, float Movement, float CoolTime, float DelayTime);// , float PassedTime);
	
	//Item ����
	void FindFrame(D3DXMATRIXA16** matrix, string frameName, ST_BONE* frame);
};

