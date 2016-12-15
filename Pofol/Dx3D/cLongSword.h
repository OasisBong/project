#pragma once
#include "cItemBase.h"

class cLongSword :
	public cItemBase
{
private:
	//ITEM_STATE				m_eState;		//����(�̼���, ����, ����)
	int						m_Durability;	//������
	SYNTHESIZE(ITEM_STATE, m_eState, State);

private:
	LPDIRECT3DTEXTURE9		m_IconTex;


	D3DXMATRIXA16			m_RocalTM;
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorldTM, WorldTM);
	SYNTHESIZE(cOBB*, m_cBox, Box);			//�浹�ڽ�
	SYNTHESIZE(LPD3DXMESH, m_pMesh, Mesh);
	SYNTHESIZE(vector<cMtlTex*>, m_vecMtlTex, vecMtlTex);

public:
	void Setup();
	void Update(D3DXMATRIXA16* worldTM);
	void Render();
	void Getting() { m_eState = ITEM_OWN; }

	void SetRocalTM();
	cLongSword();
	~cLongSword();
};

