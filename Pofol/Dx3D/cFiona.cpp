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
	m_pSkinnedMesh = new cSkinnedMesh("./Character/PC/Fiona/", "fiona.X");
	//m_pSkinnedMesh = new cSkinnedMesh("./Character/Monster/Regina/", "regina.X");
}

void cFiona::Update(D3DXMATRIX matWorld)
{
	SetWorldTM(matWorld);
}

void cFiona::Render()
{	
	if (m_pSkinnedMesh)
	{
		D3DXMATRIXA16 matS, matR;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationY(&matR, -(D3DX_PI / 2));
		matS = matS * matR * m_matWorld;
		m_pSkinnedMesh->UpdateAndRender(&matS);
		//m_pSkinnedMesh->UpdateAndRender(&m_pCharController->GetWorldTM());
	}
}

