#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cRegina.h"
#include "cHeightMap.h"

cRegina::cRegina()
	: m_pSkinnedMesh(NULL)
	, m_eRegina_state(RSTATE_IDLE)
{
}


cRegina::~cRegina()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cRegina::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("./Character/Monster/Regina/", "regina.X");
	m_OBBRegina = new cOBB;
	m_OBBRegina->Setup(m_pSkinnedMesh);
}

void cRegina::Update()
{
	D3DXMatrixIdentity(&m_matWorld);
}
void cRegina::Update(D3DXMATRIX matWorld)
{
	SetWorldTM(matWorld);
	//m_OBBRegina->Update(&matWorld);
}

void cRegina::Render(cHeightMap* pMap)
{
	if (m_pSkinnedMesh)
	{
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		D3DXMATRIXA16 matS, matT;
		//m_vPosition = D3DXVECTOR3(-5.0f, 146.0f, 1530.0f);
		m_vPosition = D3DXVECTOR3(-5.0f, 196.0f, 1530.0f);

		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matT);
		//D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
		D3DXMatrixTranslation(&matT, -5.0f, 196.0f, 1530.0f);

		if (pMap)
		{
			D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
			pMap->GetHeightVec(m_vPosition);
		}
		matS = matS * matT * m_matWorld; //  m_pCharController->GetWorldTM();
		m_pSkinnedMesh->UpdateAndRender(&matS);

		m_OBBRegina->DebugRender(D3DCOLOR_ARGB(255, 255, 255, 255));
		//m_pSkinnedMesh->UpdateAndRender(&m_pCharController->GetWorldTM());
		//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}
}

void cRegina::UpdateReginaAnimation()
{
	int regina_aniNum;
	regina_aniNum = 0;
	switch (m_eRegina_state)
	{
	case RSTATE_IDLE:
		m_pSkinnedMesh->SetAnimationIndex(&regina_aniNum);
		break;
	case RSTATE_MOVE:
		break;
	default:
		break;
	}
}
