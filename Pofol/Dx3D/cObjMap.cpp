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

	// 셰이더 로딩
	LPD3DXBUFFER		pError = NULL;			//에러 버퍼 ( 셰이더를 컴파일할때 잘못 된 문법이나 오류정보를 리턴해주는 버퍼 )
	DWORD				dwShaderFlag = 0;		//셰이더 플레그 0 

#ifdef _DEBUG
	dwShaderFlag = dwShaderFlag | D3DXSHADER_DEBUG;		//셰이더를 디버그모드로 컴파일하겠다 ( 디버그모드로 해야 잘못된 컴파일 오류가 날때 Error 버퍼에 오류정보가 들어간다 ) 
#endif

														//fx 파일로 부터 셰이더 객체 생성
	D3DXCreateEffectFromFile(
		g_pD3DDevice,				// 디바이스
		filename,					// 불러올 셰이더 코드 파일이름
		NULL,						// 셰이더를 컴파일할때 추가로 사용할 #define 정의 ( 일단 NULL )
		NULL,						// 셰이더를 컴파일할때 #include 지시문을 처리할때 사용할 인터페이스 플레그 ( 일단 NULL )
		dwShaderFlag,				// 셰이더 컴파일 플레그
		NULL,						// 셰이더 매개변수를 공유할 메모리풀 ( 일단 NULL )
		&pEffect,					// 로딩될 셰이더 Effect 포인터
		&pError						// 셰이더를 로딩하고 컴파일할때 문제가 생기면 해당 버퍼에 에러메시지가 들어간다 ( 성공적으로 로딩되면 NULL 이 참조된다 )
		);

	//셰이더 파일로딩에문재가 있다면..
	if (pError != NULL || pEffect == NULL) {

		//문제의 내용이 뭔지 문자열로 확인
		int size = pError->GetBufferSize();
		char* str = new char[size];

		//str에 버퍼에있는 내용을 저장한다.
		sprintf_s(str, size, (const char*)pError->GetBufferPointer());

		OutputDebugString(str);
		//오류내용을 출력했으니 오류버퍼 해제
		SAFE_RELEASE(pError);
		if (str)
		{
			delete[] str;
		}

		return NULL;
	}

	return pEffect;
}
