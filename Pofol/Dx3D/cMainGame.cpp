#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCharController.h"
#include "cSkinnedMesh.h"
#include "cSkinnedMeshManager.h"
#include "cObjMap.h"
#include "cHeightMap.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cFiona.h"
#include "cRegina.h"
#include "cUIObject.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
#include "cUIInterface.h"
cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCharController(NULL)
	, m_pMap(NULL)
	, m_pFiona(NULL)
	, m_pRegina(NULL)
	, m_pHPbars(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCharController);
	SAFE_DELETE(m_pMap);	
	SAFE_DELETE(m_pFiona);
	SAFE_DELETE(m_pRegina);

	//UI관련 Release
	SAFE_RELEASE(m_pHPbars);
	SAFE_DELETE(m_pUIs);

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
	
	// Vindictus Map Test
	m_pMap = new cObjMap;
	m_pMap->Load("./Map/Garden/map.obj");

	// HeightMap Dummy
	//cHeightMap* pMap = new cHeightMap;
	//pMap->Load("HeightMapData", "HeightMap.raw", "terrain.jpg");
	//m_pMap = pMap;

	
	m_pFiona = new cFiona;
	m_pFiona->Setup();

	m_pRegina = new cRegina;
	m_pRegina->Setup();

	m_pCharController = new cCharController;

	////////////////////////////////////////////////////////////////////////
	///                UI셋팅                         //////////////////////
	////////////////////////////////////////////////////////////////////////
	m_pUIs = new cUIInterface;
	m_pUIs->Setup();
	//HP바 셋팅

	//HP바 밖
	//cUIImageView* hpBar_Out = new cUIImageView;
	//hpBar_Out->SetTexture(g_pTextureManager->GetTexture("./UI/bar/hpBar_Out.png", &stImageInfo));
	//hpBar_Out->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	//hpBar_Out->SetLocalPos(D3DXVECTOR3(350, 5, 0));	
	//m_pHPbars = hpBar_Out;

	//HP바 안
	//cUIImageView* hpBar_In = new cUIImageView;
	//hpBar_In->SetTexture(g_pTextureManager->GetTexture("./UI/bar/hpBar_In.png", &stImageInfo));
	//hpBar_In->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	//hpBar_In->SetLocalPos(D3DXVECTOR3(2, 5, 0));
	//m_pHPbars->AddChild(hpBar_In);
	//SAFE_RELEASE(hpBar_In);	
	
	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	
	if(m_pCharController)
		m_pCharController->Update(m_pMap);

	if (m_pFiona)
	{
		m_pFiona->Update(m_pCharController->GetWorldTM());
	}

	if (m_pRegina)
	{
		m_pRegina->Update();
	}

	if (m_pCamera)
	{
	}

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
	

	// Vindictus Map test
	m_pMap->Render();

	m_pFiona->Render();
	m_pRegina->Render();

	m_pUIs->Render();
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

D3DXVECTOR3* cMainGame::SetCamera()
{
	D3DXVECTOR3 vRayPos = *m_pCharController->GetPosition();
	D3DXVECTOR3 vRayDir = m_pCamera->GetEye();
	D3DXVec3Normalize(&vRayDir, &vRayDir);
	
	BOOL pHit;
	float u, v, d;
	//DWORD pFaceIndex;
	D3DXIntersect(m_pMap->GetMapMesh(),
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
		D3DXVECTOR3 temp = vRayPos + (d * vRayDir);
		return &temp;
	}
	return NULL;
}

//float cMainGame::CameraDistance()
//{
//	D3DXVECTOR3 vRayPos = *m_pCharController->GetPosition();
//	D3DXVECTOR3 vRayDir = m_pCamera->GetEye();
//	D3DXVec3Normalize(&vRayDir, &vRayDir);
//
//	BOOL pHit;
//	float u, v, d;
//	//DWORD pFaceIndex;
//	D3DXIntersect(m_pMap->GetMapMesh(),
//		&vRayPos,
//		&vRayDir,
//		&pHit,
//		NULL,
//		&u, &v, &d,
//		NULL,
//		NULL);
//	
//	if (pHit && D3DXVec3Length(&(vRayDir - vRayPos)) > d)
//	{
//		return d;
//	}		
//	return 0;
//}

