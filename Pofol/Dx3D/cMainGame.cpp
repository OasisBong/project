#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCharController.h"
#include "cSkinnedMesh.h"
#include "cSkinnedMeshManager.h"
#include "cHeightMap.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cFiona.h"

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCharController(NULL)
	, m_pMap(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pFiona(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCharController);
	SAFE_DELETE(m_pMap);	
	SAFE_RELEASE(m_mapMesh);
	SAFE_DELETE(m_pFiona);
	
	/*for each (auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p);
	}*/

	for each (auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
	g_pDeviceManager->Destroy();
	g_pObjectPool->Destroy();
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);
	
	cObjLoader* pMap = new cObjLoader;

	m_mapMesh = pMap->Load("obj/map_1.obj", m_vecMtlTex);
	//cHeightMap* pMap = new cHeightMap;
	//pMap->Load("HeightMapData", "HeightMap.raw", "terrain.jpg");
	//m_pMap = pMap;

	
	m_pFiona = new cFiona;
	m_pFiona->Setup();

// 	for (int x = -20; x <= 20; ++x)
// 	{
// 		for (int z = 0; z <= 20; ++z)
// 		{
// 			cSkinnedMesh* p = new cSkinnedMesh("Zealot/", "zealot.X");
// 			p->SetPosition(D3DXVECTOR3(x, 0, z));
// 			p->SetRandomTrackPosition();
// 			p->SetAnimationIndex(rand() % 5);
// 			m_vecSkinnedMesh.push_back(p);
// 		}
// 	}

	m_pCharController = new cCharController;

	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	
	if(m_pCharController)
		m_pCharController->Update( ); // m_pMap);

	if (m_pFiona)
	{
		m_pFiona->Update(m_pCharController->GetWorldTM());
	}

	if(m_pCamera)
		m_pCamera->Update(m_pCharController->GetPosition());

// 	if(m_pSkinnedMesh)
// 	{
// 		D3DXMATRIXA16 mat;
// 		D3DXMatrixTranslation(&mat, 1, 0, 0);
// 		m_pSkinnedMesh->Update(&mat);
// 	}
	g_pAutoReleasePool->Drain();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	if(m_pGrid)
		m_pGrid->Render();
	
	

	//if(m_pMap)
	//{
	//	m_pMap->Render();
	//}

	//for each (auto p in m_vecSkinnedMesh)
	//{
	//	p->UpdateAndRender();
	//}

	D3DXMATRIXA16 world, matS, matT;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.25f, 0.25f, 0.25f);
	D3DXMatrixTranslation(&matT, -1900.0f, 0.f, 0.f);
	world = matS * matT;

	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_mapMesh->DrawSubset(i);
	}

	m_pFiona->Render();//  m_pCharController->GetWorldTM());

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if(m_pCamera)
	{
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	}

	switch(message)
	{
	case WM_KEYDOWN:
		{
			if (wParam == VK_SPACE)
			{
				static int n = 0;
				m_pFiona->GetSkinnedMesh()->SetAnimationIndex(&n);
				n++;
			}
		}
		break;
	}
}

void cMainGame::SetLight()
{
	D3DLIGHT9 stLight;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir(1, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->LightEnable(0, true);
}

