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
	//�ɸ��� ����
	SYNTHESIZE(REGINA_STATE, m_eRegina_state, Regina_state);
	//�ɸ��� �ɷ�ġ

	//�ɸ��� �̹��� & �ִϸ��̼�
	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE(D3DXMATRIX, m_matWorld, WorldTM);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, vPosition);

	SYNTHESIZE_PASS_BY_REF(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);

	SYNTHESIZE(cOBB*, m_OBBRegina, OBBRegina);
	//����׿�

	LPD3DXFONT					m_pFontRocation;	//��ġȮ�� ��Ʈ
public:
	cRegina();
	~cRegina();

	void Setup();
	void Update();
	void Update(D3DXMATRIX matWorld);
	void Render(cHeightMap* pMap = NULL);
	void UpdateReginaAnimation();
};

