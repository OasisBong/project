#include "StdAfx.h"
#include "cObjMap.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

cObjMap::cObjMap(void)
	: m_mapMesh(NULL)

{
}


cObjMap::~cObjMap(void)
{
	SAFE_RELEASE(m_mapMesh);
	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
}

void cObjMap::Load( char* szMap, char* szSurface, D3DXMATRIXA16* pmat )
{
	cObjLoader l;
	m_mapMesh = l.Load(szMap, m_vecMtlTex, NULL);

	D3DXMatrixIdentity(&m_matWorld);

	D3DXMATRIXA16 matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.25f, 0.25f, 0.25f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.f, 0.f);
	//m_matWorld = matS * matT;
	//if (szSurface)
	//{
	//	std::vector<D3DXVECTOR3> vecV;

	//	FILE* fp = NULL;
	//	fopen_s(&fp, szSurface, "r");
	//	while(!feof(fp))
	//	{
	//		char szBuf[1024] = {'\0', };

	//		fgets(szBuf, 1024, fp);

	//		if(strlen(szBuf) == 0)
	//			continue;

	//		if (szBuf[0] == '#')
	//		{
	//			continue;
	//		}
	//		else if (szBuf[0] == 'v' && szBuf[1] < 33)
	//		{
	//			float x, y, z;
	//			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
	//			vecV.push_back(D3DXVECTOR3(x, y, z));
	//		}
	//		else if (szBuf[0] == 'f')
	//		{
	//			int aIndex[3];
	//			sscanf_s(szBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
	//				&aIndex[0], &aIndex[1], &aIndex[2]);

	//			for (int i = 0; i < 3; ++i)
	//			{
	//				D3DXVECTOR3 p = vecV[aIndex[i] - 1];
	//				if(pmat)
	//				{
	//					D3DXVec3TransformCoord(&p, &p, pmat);
	//				}
	//				m_vecSurface.push_back(p);
	//			}
	//		}
	//	}
	//	fclose(fp);
	//}

}

bool cObjMap::GetHeight( IN float x, OUT float& y, IN float z )
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

	//D3DXVECTOR3 temp(x, 10000-d, z);
	//temp = 
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
}
