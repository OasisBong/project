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
#include "cUIInterface.h"

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCharController(NULL)
	, m_pMap(NULL)
	, m_pFiona(NULL)
	, m_pRegina(NULL)
	, m_isEvent(false)
	, aniNum(0)
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
	//SAFE_DELETE(m_pSword);

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
	
	m_pMap = new cObjMap;
	m_pMap->Load("./Map/Garden/map.obj");
	
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

	SetLight();

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 20;
	fd.Width = 10;
	fd.Weight = FW_BOLD;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, "Century Gothic");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFontRocation);
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	if (m_pCharController->GetPosition()->z >= 500 && m_pCamera->GeteTime() < 950)
	{
		m_pRegina->GetSkinnedMesh()->SetfAniRenderTime(1.0f);
		m_isEvent = true;
		time++;
	}
	else
	{
		m_isEvent = false;
		m_pRegina->GetSkinnedMesh()->SetfAniRenderTime(2.0f);
	}

	if (time == 0)
	{
		aniNum = 0;
		m_pRegina->GetSkinnedMesh()->SetAnimationIndex(&aniNum);
	}
	if (!m_isEvent)
	{
		if (m_pCharController)
			m_pCharController->Update(m_pFiona,m_pMap);
	}


	//if(m_pCharController)
	//	m_pCharController->Update(m_pFiona, m_pMap);

	if (m_pFiona)
	{
		m_pFiona->Update(m_pCharController->GetAniIndex(),
			&m_pCharController->GetWorldTM());
	}

	if (m_pRegina)
	{
		m_pRegina->Update();
	}

	if (m_pCamera)
	{
		if (!m_isEvent)
		{
			m_pCamera->Update(m_pMap, m_pCharController->GetPosition());
			//D3DXVECTOR3 move = m_pCharController->GetvPosition();
		}
		else
		{
			m_pCamera->UpdateReginaSpawn(m_pMap, &m_pRegina->GetvPosition());
			//m_pCamera->UpdateReginaSpawn(m_pMap, m_pCharController->GetPosition());
		}
	}

	m_pUIs->Update();

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

	DebugRender();
	
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

void cMainGame::DebugRender()
{
	RECT textRc;

	sprintf(strpt, "PC STATE = %d", m_pFiona->GetState());
	SetRect(&textRc, 100, 100, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "CamTime = %d", m_pCamera->GeteTime());
	SetRect(&textRc, 1070, 300, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "cam Distance = %f", m_pCamera->GetfDistance2());
	SetRect(&textRc, 1070, 350, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "char position X = %f", m_pCharController->GetPosition()->x);
	SetRect(&textRc, 1070, 400, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "char position Y = %f", m_pCharController->GetPosition()->y);
	SetRect(&textRc, 1070, 450, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "char position Z = %f", m_pCharController->GetPosition()->z);
	SetRect(&textRc, 1070, 500, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));


	sprintf(strpt, "cam eye X = %f", m_pCamera->GetEye().x);
	SetRect(&textRc, 500, 550, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "cam eye Y = %f", m_pCamera->GetEye().y);
	SetRect(&textRc, 500, 600, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "cam eye Z = %f", m_pCamera->GetEye().z);
	SetRect(&textRc, 500, 650, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));


	sprintf(strpt, "cam lookat X = %f", m_pCamera->GetLookAt().x);
	SetRect(&textRc, 200, 550, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "cam lookat Y = %f", m_pCamera->GetLookAt().y);
	SetRect(&textRc, 200, 600, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "cam lookat Z = %f", m_pCamera->GetLookAt().z);
	SetRect(&textRc, 200, 650, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "fAngleX = %f", m_pCamera->GetfAngleX());
	SetRect(&textRc, 0, 550, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprintf(strpt, "fAngleY = %f", m_pCamera->GetfAngleY());
	SetRect(&textRc, 0, 600, 0, 0);
	m_pFontRocation->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

}
