#pragma once
//#include "stdafx.h"
#include "hStruct.h"
#include "cOBB.h"

class cSkinnedMesh;

class cFiona
{
private:
	//케릭터 상태
	PC_DIR								m_eDir;
	PC_STATE							m_eState;
	PC_ATTACK							m_eAttack;
	PC_SMASH							m_eSmash;

	//케릭터 이미지 & 애니메이션
	std::map<std::string, int>			m_mapAnimation;
	std::map<std::string, PC_SKILL*>	m_mapSkill;

	//케릭터 능력치
	SYNTHESIZE(PC_Statuse, m_sStatuse, Statuse);

	//충돌 박스
	SYNTHESIZE(cOBB*, m_cBox, Box);

	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE(D3DXMATRIX, m_matWorld, WorldTM);
	SYNTHESIZE_PASS_BY_REF(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);

	//DEBUG용
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3*, m_pBoxPos, BoxPos);

public:
	cFiona();
	~cFiona();

	void Setup();
	void Update(int AniIndex, D3DXMATRIX matWorld);
	void Render();
	int FindIndexByName(char* AniName);
};

