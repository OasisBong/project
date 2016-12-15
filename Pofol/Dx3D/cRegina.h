#pragma once
#include "cOBB.h"
class cSkinnedMesh;
class cHeightMap;

enum REGINA_STATE
{
	RSTATE_IDLE,
	RSTATE_MOVE,

};
class cRegina
{
private:
	//케릭터 상태
	SYNTHESIZE(REGINA_STATE, m_eRegina_state, Regina_state);
	//케릭터 능력치

	//케릭터 이미지 & 애니메이션
	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE(D3DXMATRIX, m_matWorld, WorldTM);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, vPosition);

	SYNTHESIZE_PASS_BY_REF(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);

	SYNTHESIZE(cOBB*, m_OBBRegina, OBBRegina);
	//디버그용

	LPD3DXFONT					m_pFontRocation;	//위치확인 폰트
public:
	cRegina();
	~cRegina();

	void Setup();
	void Update();
	void Update(D3DXMATRIX matWorld);
	void Render(cHeightMap* pMap = NULL);
	void UpdateReginaAnimation();
};

