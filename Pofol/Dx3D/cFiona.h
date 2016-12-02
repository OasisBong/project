#pragma once
class cSkinnedMesh;

class cFiona
{
private:
	//�ɸ��� ����

	//�ɸ��� �ɷ�ġ

	//�ɸ��� �̹��� & �ִϸ��̼�
	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE(D3DXMATRIX, m_matWorld, WorldTM);
	SYNTHESIZE_PASS_BY_REF(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);

public:
	cFiona();
	~cFiona();

	void Setup();
	void Update(D3DXMATRIX matWorld);
	void Render();
};

