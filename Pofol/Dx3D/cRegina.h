#pragma once
class cSkinnedMesh;

class cRegina
{
private:
	//�ɸ��� ����

	//�ɸ��� �ɷ�ġ

	//�ɸ��� �̹��� & �ִϸ��̼�
	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE(D3DXMATRIX, m_matWorld, WorldTM);
	SYNTHESIZE_PASS_BY_REF(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);

public:
	cRegina();
	~cRegina();

	void Setup();
	void Update(D3DXMATRIX matWorld);
	void Render();
};

