#include "stdafx.h"
#include "cAllocateHierarchy.h"
#include "cSkinnedMesh.h"
#include "cSkinnedMeshManager.h"
#include "cFiona.h"


cFiona::cFiona()
	: m_pSkinnedMesh(NULL)
	, m_eDir(FRONT)
	, m_eState(IDEL)
	, m_eSmash(SMASH_0)
	, m_eAttack(ATTACK_0)
	, m_sword(NULL)
	, m_shield(NULL)
{
}


cFiona::~cFiona()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_cBox);
	SAFE_DELETE(m_sword);
	SAFE_DELETE(m_shield);

}

void cFiona::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("./Character/PC/Fiona2/", "fiona.X");
	m_cBox = new cOBB;
	m_cBox->Setup(m_pSkinnedMesh);

	//애니메이션 정보
	AnimationSetup();

	// 평타 및 스킬 셋업
	SetSkill();

	//아이템 셋팅
	m_sword = new cLongSword;
	m_sword->Setup();
	FindFrame(&m_matLeftHand, "ValveBiped_Anim_Attachment_RH", m_pSkinnedMesh->GetRoot());
	m_sword->SetState(ITEM_EQUIP);

	m_shield = new cSmallShield;
	m_shield->Setup();
	FindFrame(&m_matRightHand, "ValveBiped_Anim_Attachment_LF", m_pSkinnedMesh->GetRoot());
	m_shield->SetState(ITEM_EQUIP);

	//D3DXMATRIXA16* temp = NULL;
	//temp = m_pSkinnedMesh->FindFrame("ValveBiped_Anim_Attachment_LH", m_pSkinnedMesh->GetRoot());
	//m_sword->SetWorldTM(temp);
}

void cFiona::Update(int nAniIndex, D3DXMATRIXA16* matWorld)
{
	m_matWorld = *matWorld;
	m_cBox->Update(&m_matWorld);
}

void cFiona::Render()
{
	if (m_pSkinnedMesh)
	{
		D3DXMATRIXA16 matR;
		D3DXMatrixIdentity(&matR);
		D3DXMatrixRotationY(&matR, -(D3DX_PI / 2));
		matR = matR * m_matWorld;
		m_pSkinnedMesh->UpdateAndRender(&matR);
	}

	m_sword->Update(m_matLeftHand);
	m_shield->Update(m_matRightHand);

	m_sword->Render();
	m_shield->Render();

	m_cBox->DebugRender(D3DCOLOR_ARGB(255, 255, 255, 255));
}

//int cFiona::FindIndexByName(char* AniName)
//{
//	int index = m_mapAnimation.find(name)->second->index;
//	return index;
//}

void cFiona::FindFrame(D3DXMATRIXA16** matrix, string frameName, ST_BONE* frame)
{
	string st;
	if (frame->Name)
		st = frame->Name;

	if (st == frameName)
	{
		*matrix = &frame->CombinedTransformationMatrix;
	}

	if (frame->pFrameFirstChild)
	{
		FindFrame(matrix, frameName, (ST_BONE*)frame->pFrameFirstChild);
	}
	if (frame->pFrameSibling)
	{
		FindFrame(matrix, frameName, (ST_BONE*)frame->pFrameSibling);
	}
}

void cFiona::AnimationSetup()
{
	int maxAniNum = m_pSkinnedMesh->GetAniController()->GetMaxNumAnimationSets();
	for (int i = 0; i < maxAniNum; i++)
	{
		LPD3DXANIMATIONSET TempSet = NULL;
		m_pSkinnedMesh->GetAniController()->GetAnimationSet(i, &TempSet);

		AniINFO* sAniInfo = new AniINFO;
		string name = TempSet->GetName();
		sAniInfo->AniName = name;
		sAniInfo->period = (float)TempSet->GetPeriod();
		sAniInfo->index = i;
		//float TempSet->GetPeriod();
		m_mapAnimation.insert(pair<string, AniINFO*>(name, sAniInfo));
	}
}

void cFiona::SetSkill()
{
	// Normal Attack
	SkillSetup("attack_1", 1.0f, 1.0f, 1.0f);
	SkillSetup("attack_2", 1.0f, 1.0f, 1.0f);
	SkillSetup("attack_3", 1.0f, 1.0f, 1.0f);
	SkillSetup("attack_4", 1.0f, 1.0f, 1.0f);

	// Smash
	SkillSetup("attack_strong_00", 1.0f, 1.0f, 1.0f);
	SkillSetup("attack_strong_01", 1.0f, 1.0f, 1.0f);
	SkillSetup("attack_strong_02", 1.0f, 1.0f, 1.0f);
	SkillSetup("attack_strong_03", 1.0f, 1.0f, 1.0f);
	SkillSetup("attack_strong_04", 1.0f, 1.0f, 1.0f);
}

void cFiona::SkillSetup(string name, float Movement, float CoolTime, float DelayTime)//, float PassedTime)
{
	if (m_mapSkill.find(name) == m_mapSkill.end())
	{
		PC_SKILL* temp = new PC_SKILL;
		temp->m_sSkillName = name;
		temp->m_Aninum = m_mapAnimation.find(name)->second->index;
		temp->m_CoolTime = CoolTime;
		temp->m_DelayTime = DelayTime;
		temp->m_Movement = Movement;
		temp->m_PassedTime = m_mapAnimation.find(name)->second->period;
		//temp->m_PassedTime = PassedTime;

		m_mapSkill[name] = temp;
	}
}

void cFiona::AtkCombo(float& Period)
{
	PC_SKILL* temp;
	switch (m_eAttack)
	{
		case ATTACK_0:
		{
			temp = m_mapSkill.find("attack_1")->second;
			ChangeAnimation(temp->m_Aninum, ATTACK_1);
			Period = m_fMaxPeriod;
			break;
		}
		case ATTACK_1:
		{
			temp = m_mapSkill.find("attack_2")->second;
			ChangeAnimation(temp->m_Aninum, ATTACK_2);
			Period = m_fMaxPeriod;
			break;
		}
		case ATTACK_2:
		{
			temp = m_mapSkill.find("attack_3")->second;
			ChangeAnimation(temp->m_Aninum, ATTACK_3);
			Period = m_fMaxPeriod;
			break;
		}
		case ATTACK_3:
		{		
			temp = m_mapSkill.find("attack_4")->second;
			ChangeAnimation(temp->m_Aninum, ATTACK_4);
			Period = m_fMaxPeriod;
			break;
		}
		case ATTACK_4:
		{
			m_eAttack = ATTACK_0;
			break;
		}
		default:
			break;
	}
}

void cFiona::SmashCombo()
{
	PC_SKILL* temp;

	switch (m_eAttack)
	{
	case ATTACK_0:
	{
		switch (m_eSmash)
		{
		case SMASH_0:
		{
			temp = m_mapSkill.find("attack_strong_00")->second;
			m_pSkinnedMesh->SetAnimationIndex(&temp->m_Aninum);
			m_eSmash = SMASH_1;
			break;
		}
		}
		break;
	}
	case ATTACK_1:
	{
		temp = m_mapSkill.find("attack_2")->second;
		m_pSkinnedMesh->SetAnimationIndex(&temp->m_Aninum);
		m_eAttack = ATTACK_2;
		break;
	}
	case ATTACK_2:
	{
		temp = m_mapSkill.find("attack_3")->second;
		m_pSkinnedMesh->SetAnimationIndex(&temp->m_Aninum);
		m_eAttack = ATTACK_3;
		break;
	}
	case ATTACK_3:
	{
		temp = m_mapSkill.find("attack_4")->second;
		m_pSkinnedMesh->SetAnimationIndex(&temp->m_Aninum);
		m_eAttack = ATTACK_4;
		break;
	}
	case ATTACK_4:
	{
		break;
	}

	}
}

void cFiona::ChangeAnimation(int index, PC_ATTACK nexAtkState)
{
	D3DXTRACK_DESC temp;
	m_pSkinnedMesh->GetAniController()->GetTrackDesc(0, &temp);
	if (temp.Position >= m_fMaxPeriod)
	{
		m_pSkinnedMesh->SetAnimationIndex(index, m_fMaxPeriod);
		m_eAttack = nexAtkState;
	}
}