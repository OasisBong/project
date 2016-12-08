#pragma once
class cSkinnedMesh;
class cHeightMap;

class cRegina
{
private:
	//케릭터 상태

	//케릭터 능력치

	//케릭터 이미지 & 애니메이션
	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE(D3DXMATRIX, m_matWorld, WorldTM);
	SYNTHESIZE_PASS_BY_REF(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);

public:
	cRegina();
	~cRegina();

	void Setup();
	void Update();
	void Update(D3DXMATRIX matWorld);
	void Render(cHeightMap* pMap = NULL);
};

