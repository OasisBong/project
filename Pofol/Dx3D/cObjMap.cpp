#include "StdAfx.h"
#include "cObjMap.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

cObjMap::cObjMap(void)
	: m_mapMesh(NULL)
	, m_mapHiddenMesh(NULL) 
	, m_mapSkyBoxMesh(NULL)
{
}


cObjMap::~cObjMap(void)
{
	SAFE_RELEASE(m_mapMesh);
	SAFE_RELEASE(m_mapHiddenMesh);
	SAFE_RELEASE(m_mapSkyBoxMesh);
	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
	for each(auto p in m_vecHiddenMtlTex)
	{
		SAFE_RELEASE(p);
	}
	for each(auto p in m_vecSkyBoxMtlTex)
	{
		SAFE_RELEASE(p);
	}
}

void cObjMap::Load(char* szMap, char* szSurface, D3DXMATRIXA16* pmat)
{
	cObjLoader l;
	l.Loadmap(szMap, NULL, m_vecMtlTex, m_mapMesh, m_vecHiddenMtlTex, m_mapHiddenMesh, m_vecSkyBoxMtlTex, m_mapSkyBoxMesh);
	m_pEffect = LoadShader("./Shader/flowershader.fx");

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
	for (size_t i = 0; i < m_vecSkyBoxMtlTex.size(); i++)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetMaterial(&m_vecSkyBoxMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecSkyBoxMtlTex[i]->GetTexture());
		m_mapSkyBoxMesh->DrawSubset(i);
	}

	//for (size_t i = 0; i < m_vecHiddenMtlTex.size(); i++)
	//{
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//	g_pD3DDevice->SetMaterial(&m_vecHiddenMtlTex[i]->GetMtl());
	//	g_pD3DDevice->SetTexture(0, m_vecHiddenMtlTex[i]->GetTexture());
	//	m_mapHiddenMesh->DrawSubset(i);
	//}

	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_mapMesh->DrawSubset(i);
	}

	D3DXCreateTextureFromFile(g_pD3DDevice, "./Shader/flower_a.tga", &textest);

	D3DXMATRIXA16 matWorld, matView, matProj;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	matProj = matView*matProj;

	m_pEffect->SetMatrix("matWorld", &m_matWorld);
	m_pEffect->SetMatrix("matView", &matView);
	m_pEffect->SetMatrix("matProjection", &matProj);
	m_pEffect->SetMatrix("matWorldViewProjection", &(m_matWorld*matProj));


	UINT numPasses = 0;
	m_pEffect->Begin(&numPasses, NULL);

	for (size_t i = 0; i < m_vecHiddenMtlTex.size(); i++)
	{
		m_pEffect->BeginPass(0);

		//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		//g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		//g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0.5f);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetMaterial(&m_vecHiddenMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecHiddenMtlTex[i]->GetTexture());
		m_mapHiddenMesh->DrawSubset(i);
		m_pEffect->EndPass();
	}

	m_pEffect->End();

}


LPD3DXEFFECT cObjMap::LoadShader(const char* filename)
{
	LPD3DXEFFECT pEffect = NULL;

	// ���̴� �ε�
	LPD3DXBUFFER		pError = NULL;			//���� ���� ( ���̴��� �������Ҷ� �߸� �� �����̳� ���������� �������ִ� ���� )
	DWORD				dwShaderFlag = 0;		//���̴� �÷��� 0 

#ifdef _DEBUG
	dwShaderFlag = dwShaderFlag | D3DXSHADER_DEBUG;		//���̴��� ����׸��� �������ϰڴ� ( ����׸��� �ؾ� �߸��� ������ ������ ���� Error ���ۿ� ���������� ���� ) 
#endif

														//fx ���Ϸ� ���� ���̴� ��ü ����
	D3DXCreateEffectFromFile(
		g_pD3DDevice,				// ����̽�
		filename,					// �ҷ��� ���̴� �ڵ� �����̸�
		NULL,						// ���̴��� �������Ҷ� �߰��� ����� #define ���� ( �ϴ� NULL )
		NULL,						// ���̴��� �������Ҷ� #include ���ù��� ó���Ҷ� ����� �������̽� �÷��� ( �ϴ� NULL )
		dwShaderFlag,				// ���̴� ������ �÷���
		NULL,						// ���̴� �Ű������� ������ �޸�Ǯ ( �ϴ� NULL )
		&pEffect,					// �ε��� ���̴� Effect ������
		&pError						// ���̴��� �ε��ϰ� �������Ҷ� ������ ����� �ش� ���ۿ� �����޽����� ���� ( ���������� �ε��Ǹ� NULL �� �����ȴ� )
		);

	//���̴� ���Ϸε������簡 �ִٸ�..
	if (pError != NULL || pEffect == NULL) {

		//������ ������ ���� ���ڿ��� Ȯ��
		int size = pError->GetBufferSize();
		char* str = new char[size];

		//str�� ���ۿ��ִ� ������ �����Ѵ�.
		sprintf_s(str, size, (const char*)pError->GetBufferPointer());

		OutputDebugString(str);
		//���������� ��������� �������� ����
		SAFE_RELEASE(pError);
		if (str)
		{
			delete[] str;
		}

		return NULL;
	}

	return pEffect;
}
