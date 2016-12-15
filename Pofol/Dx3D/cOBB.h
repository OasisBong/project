#pragma once
class cSkinnedMesh;

class cOBB
{
private:
	D3DXVECTOR3					m_vOrgCenterPos;		
	D3DXVECTOR3					m_vOrgAxisDir[3];		
	
	D3DXVECTOR3					m_vCenterPos;		// ���� �߾��� ��ǥ

private:
	D3DXVECTOR3					m_vAxisDir[3];		// ���ڿ� ������ �� ���� ��������
	float						m_fAxisLen[3];		// ������ ������ �� ���� ���� fAxisLen[n]�� vAxisDir[n]�� ���� �����Ѵ�.
	float						m_fAxisHalfLen[3];

	std::vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXMATRIXA16				m_matWorldTM;
public:
	cOBB(void);
	~cOBB(void);

	void Setup(cSkinnedMesh* pSkinnedMesh);
	void Setup(LPD3DXMESH pMesh);		
	void Update(D3DXMATRIXA16* pmatWorld);
	void DebugRender(D3DCOLOR c);

	static bool IsCollision(cOBB* pOBB1, cOBB* pOBB2);
};

