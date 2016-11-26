#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cFiona.h"


cFiona::cFiona()
	: m_pSkinnedMesh(NULL)
{
}


cFiona::~cFiona()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cFiona::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("monster/regina/", "regina.X");
}

void cFiona::Update(D3DXMATRIX matWorld)
{
	SetWorldTM(matWorld);
}

void cFiona::Render()
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

