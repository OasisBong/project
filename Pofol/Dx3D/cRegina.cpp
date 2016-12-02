#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cRegina.h"
#include "cHeightMap.h"

cRegina::cRegina()
	: m_pSkinnedMesh(NULL)
{
}


cRegina::~cRegina()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cRegina::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("./Character/Monster/Regina/", "regina.X");
}

void cRegina::Update()
{
	D3DXMatrixIdentity(&m_matWorld);
}
void cRegina::Update(D3DXMATRIX matWorld)
{
	SetWorldTM(matWorld);
}

void cRegina::Render(cHeightMap* pMap)
{
	if (m_pSkinnedMesh)
	{
		D3DXMATRIXA16 matS, matT;
		D3DXVECTOR3 position(100,0,100);

		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matT);
		//D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
		D3DXMatrixTranslation(&matT, -5.0f, 146.0f, 1530.0f);

		if (pMap)
		{
			D3DXMatrixTranslation(&matT, position.x, position.y, position.z);
			pMap->GetHeightVec(position);
		}
		matS = matS * matT * m_matWorld; //  m_pCharController->GetWorldTM();
		m_pSkinnedMesh->UpdateAndRender(&matS);
		//m_pSkinnedMesh->UpdateAndRender(&m_pCharController->GetWorldTM());
	}
}
