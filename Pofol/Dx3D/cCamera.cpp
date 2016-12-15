#include "stdafx.h"
#include "cCamera.h"
#include "cObjMap.h"

#include "cRegina.h"

#include "cActionMove.h"
#include "cActionSeq.h"
#include "cActionRepeat.h"

cCamera::cCamera(void)
	: m_vEye(0, 1000, 0)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_isLButtonDown(false)
	, m_fAngleX(0.0f)
	, m_fAngleY(0.0f)
	, m_fDistance(200.0f)
	, m_fDistance2(880.0f)
	, m_fAngleX2(0.23f)
	, m_fAngleY2(0.32f)
	, m_neTime(0)
	, m_fLookatY(50.0f)
	, m_fEyeY(0.0f)
	, m_fcLookatX(0.0f)
	, m_fcLookatY(60.0f)
	, m_fcEyeX(0.0f)
	, m_fcEyeY(0.0f)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}


cCamera::~cCamera(void)
{
}

void cCamera::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matView, matProj;

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 100000.0f);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update(cObjMap* pMap,				//충돌 대상
	D3DXVECTOR3* pTarget)		//타겟 포지션
{
	// CamaraPos 및 LookAt 초기화


	m_vEye = D3DXVECTOR3(m_fcEyeX, m_fcEyeY, -m_fDistance);
	m_vLookAt = D3DXVECTOR3(m_fcLookatX, m_fcLookatY, 0);
	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fAngleX);
	D3DXMatrixRotationY(&matRotY, m_fAngleY);

	D3DXMATRIXA16 matRot = matRotX * matRotY;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRot);
	//m_fcEyeX++;
	//m_fcLookatX--;
	if (pTarget)
	{
		m_vEye = m_vEye + *pTarget;
		m_vLookAt = m_vLookAt + *pTarget;
	}

	//// 맵 & 오브젝트 충돌시 CameraPos 보정
	D3DXVECTOR3 vRayPos = m_vLookAt;
	D3DXVECTOR3 vRayDir = m_vEye - m_vLookAt;
	float LayDistance = D3DXVec3Length(&vRayDir);
	D3DXVec3Normalize(&vRayDir, &vRayDir);

	BOOL pHit;
	float u, v, d;

	D3DXIntersect(pMap->GetMapMesh(),
		&vRayPos,
		&vRayDir,
		&pHit,
		NULL,
		&u, &v, &d,
		NULL,
		NULL);

	//충돌시 vEye 보정
	if (pHit && d < LayDistance)
	{
		//D3DXVec3Normalize(&PosToDir, &PosToDir);
		m_vEye = (vRayDir * d) + vRayPos;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEWHEEL:
		m_fDistance -= GET_WHEEL_DELTA_WPARAM(wParam) / 20.f;
		//m_fDistance2 -= GET_WHEEL_DELTA_WPARAM(wParam) / 20.f;
		break;
		//case WM_MOUSEMOVE:
		//	{
		//		
		//		POINT ptCurrMouse;
		//		ptCurrMouse.x = LOWORD(lParam);
		//		ptCurrMouse.y = HIWORD(lParam);

		//		int nDeltaX = ptCurrMouse.x - m_ptPrevMouse.x;
		//		int nDeltaY = ptCurrMouse.y - m_ptPrevMouse.y;

		//		m_fAngleX += nDeltaY / 100.f;
		//				
		//		if(m_fAngleX <= -D3DX_PI / 2 + EPSILON)
		//			m_fAngleX = -D3DX_PI / 2 + EPSILON;

		//		if(m_fAngleX >=  D3DX_PI / 2 - EPSILON)
		//			m_fAngleX =  D3DX_PI / 2 - EPSILON;

		//		m_fAngleY += nDeltaX / 100.f;

		//		m_ptPrevMouse = ptCurrMouse;
		//		SetCursorPos(ptCurrMouse.x, ptCurrMouse.y);
		//	}
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		break;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;
	case WM_MOUSEMOVE:
	{

		POINT ptCurrMouse;
		ptCurrMouse.x = LOWORD(lParam);
		ptCurrMouse.y = HIWORD(lParam);

		int nDeltaX = ptCurrMouse.x - m_ptPrevMouse.x;
		int nDeltaY = ptCurrMouse.y - m_ptPrevMouse.y;

		m_fAngleX += nDeltaY / 100.f;

		if (m_fAngleX <= -D3DX_PI / 2 + EPSILON)
			m_fAngleX = -D3DX_PI / 2 + EPSILON;

		if (m_fAngleX >= D3DX_PI / 2 - EPSILON)
			m_fAngleX = D3DX_PI / 2 - EPSILON;

		m_fAngleY += nDeltaX / 100.f;
		
		m_ptPrevMouse = ptCurrMouse;
	
	}
	break;
	}
}

void cCamera::UpdateReginaSpawn(cObjMap * pMap, D3DXVECTOR3* pTarget)
{
	// CamaraPos 및 LookAt 초기화

	m_vEye = D3DXVECTOR3(0, m_fEyeY, -m_fDistance2);
	m_vLookAt = D3DXVECTOR3(0, m_fLookatY, 0);
	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fAngleX2);
	D3DXMatrixRotationY(&matRotY, m_fAngleY2);

	D3DXMATRIXA16 matRot = matRotX * matRotY;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRot);

	if (m_neTime <= 950)
	{
		m_neTime++;
		if (m_neTime < 400)
		{
			m_fDistance2 -= 1.5f;
		}
		if (m_neTime > 400 && m_neTime < 450)
		{
			m_fDistance2 += 1.0f;
		}
		if (m_neTime > 690 && m_neTime < 730)
		{
			m_fLookatY += 5.0f;
			m_fEyeY += 5.0f;
		}
	}

	if (pTarget)
	{
		m_vEye = m_vEye + *pTarget;
		m_vLookAt = m_vLookAt + *pTarget;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

}

void cCamera::CameraShake()
{
	//m_vEye = D3DXVECTOR3(0, m_fEyeY, -m_fDistance2);
	//m_vLookAt = D3DXVECTOR3(0, m_fLookatY, 0);
	//D3DXMATRIXA16 matRotX, matRotY;
	//D3DXMatrixRotationX(&matRotX, m_fAngleX2);
	//D3DXMatrixRotationY(&matRotY, m_fAngleY2);

	//D3DXMATRIXA16 matRot = matRotX * matRotY;
	//D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRot);

	//if (m_neTime <= 950)
	//{
	//	m_neTime++;
	//	if (m_neTime < 400)
	//	{
	//		m_fDistance2 -= 1.5f;
	//	}
	//	if (m_neTime > 400 && m_neTime < 450)
	//	{
	//		m_fDistance2 += 1.0f;
	//	}
	//	if (m_neTime > 690 && m_neTime < 730)
	//	{
	//		m_fLookatY += 5.0f;
	//		m_fEyeY += 5.0f;
	//	}
	//}

	//if (pTarget)
	//{
	//	m_vEye = m_vEye + *pTarget;
	//	m_vLookAt = m_vLookAt + *pTarget;
	//}

	//D3DXMATRIXA16 matView;
	//D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	//g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}
