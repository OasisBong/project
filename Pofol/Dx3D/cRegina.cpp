#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cRegina.h"

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
	m_pSkinnedMesh = new cSkinnedMesh("monster/regina/", "regina.X");
}

void cRegina::Update(D3DXMATRIX matWorld)
{
	SetWorldTM(matWorld);
}

void cRegina::Render()
{
	if (m_pSkinnedMesh)
	{
		D3DXMATRIXA16 matS;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
		matS = matS * m_matWorld; //  m_pCharController->GetWorldTM();
		m_pSkinnedMesh->UpdateAndRender(&matS);
		//m_pSkinnedMesh->UpdateAndRender(&m_pCharController->GetWorldTM());
	}
}
