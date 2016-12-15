#include "StdAfx.h"
#include "cObjMap.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

cObjMap::cObjMap(void)
	: m_mapMesh(NULL)
	, m_mapHiddenMesh(NULL)
{
}


cObjMap::~cObjMap(void)
{
	SAFE_RELEASE(m_mapMesh);
	SAFE_RELEASE(m_mapHiddenMesh);

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
	for each(auto p in m_vecHiddenMtlTex)
	{
		SAFE_RELEASE(p);
	}
	//for each(auto p in m_vecFlower)
	//{
	//	SAFE_RELEASE(p);
	//}
}

void cObjMap::Load(char* szMap, char* szSurface, D3DXMATRIXA16* pmat)
{
	cObjLoader l;
	//m_mapMesh = l.Load(szMap, m_vecMtlTex,NULL);
	//m_mapMesh = l.Load(szMap, NULL, m_vecMtlTex, m_mapMesh, m_vecHiddenMtlTex, m_vecFlower);
	l.Loadmap(szMap, NULL, m_vecMtlTex, m_mapMesh, m_vecHiddenMtlTex, m_mapHiddenMesh);


	D3DXMatrixIdentity(&m_matWorld);

	D3DXMATRIXA16 matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.25f, 0.25f, 0.25f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.f, 0.f);


}

bool cObjMap::GetHeight(IN float x, OUT float& y, IN float z)
{
	D3DXVECTOR3 vRayPos(x, 10000, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	float u, v, d;
	BOOL pHit;
	DWORD pFaceIndex;
	LPD3DXBUFFER ppAllHits;
	DWORD pCountOfHits;
	D3DXIntersect(m_mapMesh,
		&vRayPos,
		&vRayDir,
		&pHit,
		NULL,
		&u, &v, &d,
		NULL,
		NULL);

	if (pHit)
	{
		y = 10000 - d;
		return true;
	}
	return false;
}

void cObjMap::Render()
{
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_mapMesh->DrawSubset(i);
	}

	for (size_t i = 0; i < m_vecHiddenMtlTex.size(); i++)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetMaterial(&m_vecHiddenMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecHiddenMtlTex[i]->GetTexture());
		m_mapHiddenMesh->DrawSubset(i);
	}
}
