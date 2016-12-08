#include "StdAfx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"

cObjLoader::cObjLoader(void)
{
}

cObjLoader::~cObjLoader(void)
{
}

void cObjLoader::Load(IN char* szFilename, OUT std::vector<cGroup*>& vecGroup, IN D3DXMATRIXA16* pmat)

{
	m_mapMtlTex.clear();

	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR3> vecVN;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<ST_PNT_VERTEX> vecVertex;
	std::string sMtlName;

	FILE* fp = NULL;
	fopen_s(&fp, szFilename, "r");
	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };

		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlPath, 1024);
			LoadMtlLib(szMtlPath);
		}
		else if (szBuf[0] == 'g')
		{
			if (!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];

				if (pmat)
				{
					D3DXVec3TransformNormal(&v.n, &vecVN[aIndex[i][2] - 1], pmat);
					D3DXVec3TransformCoord(&v.p, &vecV[aIndex[i][0] - 1], pmat);
				}
				vecVertex.push_back(v);
			}
		}
	}
	fclose(fp);

	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
}

LPD3DXMESH cObjLoader::Load(IN char* szFilename, OUT std::vector<cMtlTex*>& vecMtlTex, IN D3DXMATRIXA16* pmat /*= NULL*/)
{
	m_mapMtlTex.clear();

	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR3> vecVN;
	std::vector<D3DXVECTOR2> vecVT;

	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecAttr;
	std::string sMtlName;

	FILE* fp = NULL;
	fopen_s(&fp, szFilename, "r");
	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };

		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlPath, 1024);
			LoadMtlLib(szMtlPath, vecMtlTex);
		}
		else if (szBuf[0] == 'g')
		{
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, 1 - v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];

				if (pmat)
				{
					D3DXVec3TransformNormal(&v.n, &vecVN[aIndex[i][2] - 1], pmat);
					D3DXVec3TransformCoord(&v.p, &vecV[aIndex[i][0] - 1], pmat);
				}
				vecVertex.push_back(v);
			}
			vecAttr.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}
	fclose(fp);

	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], sizeof(ST_PNT_VERTEX) * vecVertex.size());
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (DWORD i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttr[0], sizeof(DWORD) * vecAttr.size());
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	pMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		NULL,
		NULL,
		NULL);

	return pMesh;
}

LPD3DXMESH cObjLoader::Load(IN char * szFilename, IN D3DXMATRIX* pMat,
	OUT std::vector<cMtlTex*>& vecMtlTex, OUT LPD3DXMESH& mesh,
	OUT std::vector<cMtlTex*>& vecHiddenMtlTex, OUT std::vector<LPD3DXMESH>& vecHiddenMesh)
{

	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<D3DXVECTOR2>	vecVT;

	std::string					sMtlName;

	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecAttr;

	std::vector<ST_PNT_VERTEX>	vecHiddenVertex;
	std::vector<DWORD>			vecHiddenAttr;


	FILE* fp = NULL;
	string sFullpath = m_sPath + szFilename;

	fopen_s(&fp, sFullpath.c_str(), "r");
	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };

		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;
		else if (szBuf[0] == '#')
		{
			if (StartsWith(szBuf, "# object"))
			{
				if (vecHiddenVertex.empty()) continue;
				else
				{
					LPD3DXMESH pMesh = NULL;
					D3DXCreateMeshFVF(vecHiddenVertex.size() / 3,
						vecHiddenVertex.size(),
						D3DXMESH_MANAGED | D3DXMESH_32BIT,
						ST_PNT_VERTEX::FVF,
						g_pD3DDevice,
						&pMesh);

					ST_PNT_VERTEX* pV = NULL;
					pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
					memcpy(pV, &vecHiddenVertex[0], sizeof(ST_PNT_VERTEX) * vecHiddenVertex.size());
					pMesh->UnlockVertexBuffer();

					int* pI = NULL;
					pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
					for (int i = 0; i < vecHiddenVertex.size(); ++i)
					{
						pI[i] = i;
					}
					pMesh->UnlockIndexBuffer();

					DWORD* pA = NULL;
					pMesh->LockAttributeBuffer(0, &pA);
					memcpy(pA, &vecHiddenAttr[0], sizeof(DWORD) * vecHiddenAttr.size());
					pMesh->UnlockAttributeBuffer();

					std::vector<DWORD> vecAdj(vecHiddenVertex.size());
					pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

					pMesh->OptimizeInplace(
						D3DXMESHOPT_COMPACT |
						D3DXMESHOPT_ATTRSORT |
						D3DXMESHOPT_VERTEXCACHE,
						&vecAdj[0],
						NULL,
						NULL,
						NULL);

					vecHiddenMesh.push_back(pMesh);

					vecHiddenAttr.clear();
					vecHiddenVertex.clear();

				}
			}
			else
				continue;
		}

		else if (szBuf[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlPath, 1024);
			LoadMtlLib(szMtlPath, vecMtlTex, vecHiddenMtlTex);

		}
		else if (szBuf[0] == 'g')
		{
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, 1 - v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformNormal(&v.n, &vecVN[aIndex[i][2] - 1], pMat);
					D3DXVec3TransformCoord(&v.p, &vecV[aIndex[i][0] - 1], pMat);
				}


				if (StartsWith(StringToChar(sMtlName), "Flower"))
					vecHiddenVertex.push_back(v);
				else
					vecVertex.push_back(v);
			}
			if (StartsWith(StringToChar(sMtlName), "Flower"))
				vecHiddenAttr.push_back(m_mapHiddenMtlTex[sMtlName]->GetAttrID());
			else
				vecAttr.push_back(m_mapMtlTex[sMtlName]->GetAttrID());

		}

	}
	fclose(fp);

	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&mesh);

	ST_PNT_VERTEX* pV = NULL;
	mesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], sizeof(ST_PNT_VERTEX) * vecVertex.size());
	mesh->UnlockVertexBuffer();

	int* pI = NULL;
	mesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (int i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	mesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	mesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttr[0], sizeof(DWORD) * vecAttr.size());
	mesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(vecVertex.size());
	mesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	mesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		NULL,
		NULL,
		NULL);

	return mesh;

}

void cObjLoader::Loadmap(IN char* szFilename, IN D3DXMATRIX* pMat,
	OUT std::vector<cMtlTex*>& vecMtlTex, OUT LPD3DXMESH& mesh,
	OUT std::vector<cMtlTex*>& vecHiddenMtlTex, OUT LPD3DXMESH& hiddenmesh)
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<D3DXVECTOR2>	vecVT;

	std::string					sMtlName;

	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecAttr;

	std::vector<ST_PNT_VERTEX>	vecHiddenVertex;
	std::vector<DWORD>			vecHiddenAttr;


	FILE* fp = NULL;
	string sFullpath = m_sPath + szFilename;

	fopen_s(&fp, sFullpath.c_str(), "r");
	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };

		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;
		else if (szBuf[0] == '#')
		{
			continue;
		}

		else if (szBuf[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlPath, 1024);
			LoadMtlLib(szMtlPath, vecMtlTex, vecHiddenMtlTex);

		}
		else if (szBuf[0] == 'g')
		{
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, 1 - v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformNormal(&v.n, &vecVN[aIndex[i][2] - 1], pMat);
					D3DXVec3TransformCoord(&v.p, &vecV[aIndex[i][0] - 1], pMat);
				}


				if (StartsWith(StringToChar(sMtlName), "Flower"))
				{
					vecHiddenVertex.push_back(v);
				}
				else
				{
					vecVertex.push_back(v);
				}
			}
			if (StartsWith(StringToChar(sMtlName), "Flower"))
			{
				vecHiddenAttr.push_back(m_mapHiddenMtlTex[sMtlName]->GetAttrID());
			}
			else
			{
				vecAttr.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
			}
		}
	}
	fclose(fp);

	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&mesh);

	ST_PNT_VERTEX* pV = NULL;
	mesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], sizeof(ST_PNT_VERTEX) * vecVertex.size());
	mesh->UnlockVertexBuffer();

	int* pI = NULL;
	mesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (int i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	mesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	mesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttr[0], sizeof(DWORD) * vecAttr.size());
	mesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(vecVertex.size());
	mesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	mesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		NULL,
		NULL,
		NULL);


	D3DXCreateMeshFVF(vecHiddenVertex.size() / 3,
		vecHiddenVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&hiddenmesh);

	ST_PNT_VERTEX* pV2 = NULL;
	hiddenmesh->LockVertexBuffer(0, (LPVOID*)&pV2);
	memcpy(pV2, &vecHiddenVertex[0], sizeof(ST_PNT_VERTEX) * vecHiddenVertex.size());
	hiddenmesh->UnlockVertexBuffer();

	int* pI2 = NULL;
	hiddenmesh->LockIndexBuffer(0, (LPVOID*)&pI2);
	for (int i = 0; i < vecHiddenVertex.size(); ++i)
	{
		pI2[i] = i;
	}
	hiddenmesh->UnlockIndexBuffer();

	DWORD* pA2 = NULL;
	hiddenmesh->LockAttributeBuffer(0, &pA2);
	memcpy(pA2, &vecHiddenAttr[0], sizeof(DWORD) * vecHiddenAttr.size());
	hiddenmesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj2(vecHiddenVertex.size());
	hiddenmesh->GenerateAdjacency(0.0f, &vecAdj2[0]);

	hiddenmesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj2[0],
		NULL,
		NULL,
		NULL);
}

void cObjLoader::LoadMtlLib(char* szFilename)
{
	std::string sMtlName;

	FILE* fp = NULL;
	fopen_s(&fp, szFilename, "r");
	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };

		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
			m_mapMtlTex[sMtlName] = new cMtlTex;
		}
		else if (szBuf[0] == 'K')
		{
			if (szBuf[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if (szBuf[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if (szBuf[1] == 's')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
			}
		}
		else if (szBuf[0] == 'm')
		{
			char szTexturePath[1024];
			sscanf_s(szBuf, "%*s %s", szTexturePath, 1024);
			m_mapMtlTex[sMtlName]->SetTexture(g_pTextureManager->GetTexture(szTexturePath));
		}
	}
	fclose(fp);
}

void cObjLoader::LoadMtlLib(IN char* szFilename, OUT std::vector<cMtlTex*>& vecMtlTex)
{
	std::string sMtlName;

	FILE* fp = NULL;
	fopen_s(&fp, szFilename, "r");
	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };

		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
			m_mapMtlTex[sMtlName] = new cMtlTex;
			m_mapMtlTex[sMtlName]->SetAttrID(vecMtlTex.size());
			vecMtlTex.push_back(m_mapMtlTex[sMtlName]);
		}
		else if (szBuf[0] == 'K')
		{
			if (szBuf[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if (szBuf[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if (szBuf[1] == 's')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
			}
		}
		else if (szBuf[0] == 'm')
		{
			char szTexturePath[1024];
			sscanf_s(szBuf, "%*s %s", szTexturePath, 1024);
			m_mapMtlTex[sMtlName]->SetTexture(g_pTextureManager->GetTexture(szTexturePath));
		}
	}
	fclose(fp);
}

void cObjLoader::LoadMtlLib(IN char * szFilename, OUT std::vector<cMtlTex*>& vecMtlTex, OUT std::vector<cMtlTex*>& vecHiddenMtlTex)
{
	std::string sMtlName;

	FILE* fp = NULL;
	bool hiddenMtl = false;
	fopen_s(&fp, szFilename, "r");

	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };

		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (StartsWith(szBuf, "newmtl"))
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);

			if (StartsWith(StringToChar(sMtlName), "Flower"))
			{
				m_mapHiddenMtlTex[sMtlName] = new cMtlTex;
				m_mapHiddenMtlTex[sMtlName]->SetAttrID(vecHiddenMtlTex.size());
				vecHiddenMtlTex.push_back(m_mapHiddenMtlTex[sMtlName]);
				hiddenMtl = true;
			}
			else
			{
				m_mapMtlTex[sMtlName] = new cMtlTex;
				m_mapMtlTex[sMtlName]->SetAttrID(vecMtlTex.size());
				vecMtlTex.push_back(m_mapMtlTex[sMtlName]);
				hiddenMtl = false;
			}
		}
		else if (szBuf[0] == 'K')
		{
			if (szBuf[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				if (hiddenMtl)
				{
					D3DMATERIAL9& stMtl = m_mapHiddenMtlTex[sMtlName]->GetMtl();
					stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
				}
				else
				{
					D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
					stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
				}

			}
			else if (szBuf[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				if (hiddenMtl)
				{
					D3DMATERIAL9& stMtl = m_mapHiddenMtlTex[sMtlName]->GetMtl();
					stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
				}
				else
				{
					D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
					stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
				}
			}
			else if (szBuf[1] == 's')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				if (hiddenMtl)
				{
					D3DMATERIAL9& stMtl = m_mapHiddenMtlTex[sMtlName]->GetMtl();
					stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
				}
				else
				{
					D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
					stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
				}
			}
		}
		else if (szBuf[0] == 'm')
		{
			char szTexturePath[1024];
			sscanf_s(szBuf, "%*s %s", szTexturePath, 1024);
			if (hiddenMtl)
			{
				m_mapHiddenMtlTex[sMtlName]->SetTexture(g_pTextureManager->GetTexture(szTexturePath));
			}
			else
			{
				m_mapMtlTex[sMtlName]->SetTexture(g_pTextureManager->GetTexture(szTexturePath));
			}

		}
	}
	fclose(fp);
}

bool cObjLoader::StartsWith(char * str, char * beginStr)
{
	char* temp = strstr(str, beginStr);
	if (temp == str)
		return true;

	return false;
}

char* cObjLoader::StringToChar(string input)
{
	char* c = new char[input.size() + 1];
	std::copy(input.begin(), input.end(), c);
	c[input.size()] = '\0';

	return c;
}

LPD3DXMESH cObjLoader::getHiddenMash(OUT LPD3DXMESH& mash_out)
{
	LPD3DXMESH mash = mash_out;

	return mash_out;
}
