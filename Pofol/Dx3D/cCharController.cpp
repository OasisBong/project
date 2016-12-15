#include "stdafx.h"
#include "cCharController.h"
#include "cFiona.h"
#include "iMap.h"



cCharController::cCharController(void)
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 1)
	, m_fAngle(0.0f)
	, m_fSpeed(3.0f)
	, m_nAniIndex(0)
	, m_AtkCount(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cCharController::~cCharController(void)
{
}

void cCharController::Update(cFiona* Target, iMap* pMap)
{
	KeyControl(Target, pMap);	
}


void cCharController::KeyControl(cFiona* Target, iMap* pMap)
{
	bool isKeyMove = false;

	PC_STATE curSTATE = Target->GetState();

	D3DXVECTOR3 p = m_vPosition;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		isKeyMove = true;
		if (m_AtkCount > 4)
			m_AtkCount = 0;
		if (curSTATE == BATTLE)
		{
			if (GetDescPos(Target) >= (m_fMaxPeriod - KEYBUFFERTIME))
			{
				SetTargetAnimation(Target, (m_AtkCount + 3));
				m_AtkCount++;
			}
		}
		else
		{
			Target->SetState(BATTLE);
			SetTargetAnimation(Target, (m_AtkCount + 3));
			m_AtkCount++;
		}
	}



	//Smash
	//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	//{		
	//	isKeyMove = true;
	//	if (curSTATE != BATTLE)
	//	{
	//		Target->SetState(BATTLE);
	//	}
	//	Target->SmashCombo();
	//}

	//방향 회전
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_fAngle -= 0.1f;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_fAngle += 0.1f;
	}
		
	//진퇴 컨트롤
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		isKeyMove = true;
		p = p - m_vDirection * m_fSpeed;
		if(curSTATE != MOVE)
		{
			if (curSTATE == IDEL)
			{
				Target->SetState(MOVE);
				SetTargetAnimation(Target, 1);
			}
			else
			{
				if (GetDescPos(Target) >= m_fMaxPeriod)
				{
					Target->SetState(MOVE);
					SetTargetAnimation(Target, 1);
				}
			}
		}
		
	}

	//if (KEYMANAGER->isStayKeyDown('S'))
	//{
	//	isKeyMove = true;
	//	p = p + m_vDirection * m_fSpeed;
	//	if (curSTATE != MOVE && curSTATE != BATTLE)
	//	{
	//		Target->SetState(MOVE);
	//		SetTargetAnimation(Target, 1);
	//	}
	//}

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
		if (KEYMANAGER->isStayKeyDown('E'))
		{
			m_vPosition.y += m_fSpeed;
		}
		if (KEYMANAGER->isStayKeyDown('Q'))
		{
			m_vPosition.y -= m_fSpeed;
		}
	}

	if ((GetDescPos(Target) >= m_fMaxPeriod) && !isKeyMove)
	{
		SetTargetAnimation(Target, 0);
		Target->SetState(IDEL);
	}

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXMATRIXA16 matT, matRotY;
	D3DXMatrixRotationY(&matRotY, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matRotY);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRotY * matT;
}

void cCharController::SetTargetAnimation(cFiona* Target, int index)//, string name)
{	
	Target->GetSkinnedMesh()->SetAnimationIndex(index, m_fMaxPeriod);
}

float cCharController::GetDescPos(cFiona* Target)
{
	D3DXTRACK_DESC Rtu;
	Target->GetSkinnedMesh()->GetAniController()->GetTrackDesc(0, &Rtu);

	return (float)Rtu.Position;
}
