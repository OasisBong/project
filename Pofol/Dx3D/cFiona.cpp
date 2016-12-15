#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cFiona.h"
#include "cCharController.h"

cFiona::cFiona()
	: m_pSkinnedMesh(NULL)
	, m_eDir(FRONT)
	, m_eState(IDEL)
	, m_eSmash(SMASH_0)
	, m_eAttack(ATTACK_0)
{
}


cFiona::~cFiona()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cFiona::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("./Character/PC/Fiona3/", "fiona.X");
	m_cBox = new cOBB;
	m_cBox->Setup(m_pSkinnedMesh);

	//int maxAniNum = m_pSkinnedMesh->GetAniController()->GetMaxNumAnimationSets();
	//for (int i = 0; i < maxAniNum; i++)
	//{
	//	LPD3DXANIMATIONSET TempSet = NULL;
	//	m_pSkinnedMesh->GetAniController()->GetAnimationSet(i, &TempSet);
	//	string AniSetName = TempSet->GetName();
	//	m_mapAnimation.insert(pair<string, int>(AniSetName, i));
	//}


}

void cFiona::Update(int nAniIndex, D3DXMATRIX matWorld)
{
	SetWorldTM(matWorld);
	m_cBox->Update((D3DXMATRIXA16*)&m_matWorld);
	//m_pSkinnedMesh->SetAnimationIndex(&nAniIndex);
	int a = 0;

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

	if (KEYMANAGER->isToggleKey('P'))
	{
		m_cBox->DebugRender(D3DCOLOR_ARGB(255, 255, 255, 255));

	}



}

int cFiona::FindIndexByName(char* AniName)
{
	return m_mapAnimation[AniName];
}