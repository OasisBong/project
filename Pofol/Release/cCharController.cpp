#include "stdafx.h"
#include "cCharController.h"
#include "iMap.h"

cCharController::cCharController(void)
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 1)
	, m_fAngle(0.0f)
	, m_fSpeed(3.0f)
	, m_nAniIndex(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cCharController::~cCharController(void)
{
}

void cCharController::Update(iMap* pMap)
{
	KeyControl(pMap);	
}


void cCharController::KeyControl(iMap* pMap)
{
	//방향 회전
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_fAngle -= 0.1f;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_fAngle += 0.1f;
	}

	D3DXVECTOR3 p = m_vPosition;

	//진퇴 컨트롤
	if (GetKeyState('W') & 0x8000)
	{
		p = p - m_vDirection * m_fSpeed;
	}
	if (GetKeyState('S') & 0x8000)
	{
		p = p + m_vDirection * m_fSpeed;
	}

	if (!KEYMANAGER->isToggleKey('O'))
	{
		//높이 보정
		if (pMap && pMap->GetHeight(p.x, p.y, p.z))
		{
			m_vPosition = p;
		}
	}
	else
	{
		//높이 컨트롤
		if (GetKeyState('E') & 0x8000)
		{
			m_vPosition.y += m_fSpeed;
		}
		if (GetKeyState('Q') & 0x8000)
		{
			m_vPosition.y -= m_fSpeed;
		}
	}

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		m_nAniIndex++;
	}


	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXMATRIXA16 matT, matRotY;
	D3DXMatrixRotationY(&matRotY, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matRotY);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRotY * matT;
}
