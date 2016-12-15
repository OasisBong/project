#include "stdafx.h"
#include "cLongSword.h"
#include "cObjLoader.h"

cLongSword::cLongSword()
	: m_eState(ITEM_NONE)
	, m_Durability(100)			//내구력 기본 100
{
}


cLongSword::~cLongSword()
{
//	SAFE_DELETE(m_pSkinnedMesh);
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		SAFE_RELEASE(m_vecMtlTex[i]);
	}
	SAFE_DELETE(m_cBox);
}


void cLongSword::Setup()
{
	//OBJ Loader
	cObjLoader* Item = new cObjLoader;
	m_pMesh = Item->Load("./Item/Equipment/sword/sword.obj", m_vecMtlTex, NULL);

	D3DXMatrixIdentity(&m_RocalTM);
	SetRocalTM();

	m_cBox = new cOBB;
	m_cBox->Setup(m_pMesh);
}

void cLongSword::Update(D3DXMATRIXA16* worldTM)
{
	//D3DXMatrixMultiply(&m_matWorldTM, &m_RocalTM, &worldTM);
	m_matWorldTM = m_RocalTM * (*worldTM);
	m_cBox->Update(&m_matWorldTM);
}

void cLongSword::Render()
{
	//아이템이 인벤토리에 있는것이 아니면 그린다
	//if (!(m_eState == ITEM_OWN) && !(m_Durability <= 0))
	//{
		for (size_t i = 0; i < m_vecMtlTex.size(); i++)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
			g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMtl());
			g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
			m_pMesh->DrawSubset(i);
		}
	//}

	m_cBox->DebugRender(D3DCOLOR_ARGB(255, 255, 255, 255));
}

void cLongSword::SetRocalTM()
{
	D3DXMATRIXA16 matT, matX, matY, matZ;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matX);
	D3DXMatrixIdentity(&matY);
	D3DXMatrixIdentity(&matZ);
	//D3DXMatrixRotationX(&matX, D3DX_PI/2);
	D3DXMatrixRotationY(&matY, D3DX_PI / 2);
	D3DXMatrixRotationZ(&matZ, D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, -3.f, 0, 0);
	m_RocalTM = matX * matY * matZ * matT;
}
