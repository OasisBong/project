#pragma once

#define BLENDINGTIME 0.3f

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	//하나만 생성
	ST_BONE*					m_pRootFrame;			
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	ST_SPHERE					m_stBoundingSphere;
	SYNTHESIZE(float, m_fAniRenderTime, fAniRenderTime);

	//test
	vector<LPSTR>				m_vecname;

	// 객체마다 생성
	D3DXVECTOR3					m_vPosition;
	SYNTHESIZE(D3DXVECTOR3, m_Min, Min);
	SYNTHESIZE(D3DXVECTOR3, m_Max, Max);
	SYNTHESIZE_PASS_BY_REF(
		LPD3DXANIMATIONCONTROLLER, m_pAnimController, AniController)

private:
	bool						m_isBlending;
	float						m_fPassedBlendingTime;
	
public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	~cSkinnedMesh(void);
	
	void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);

	// Funtion For Blenbing
	void SetAnimationIndex(int* nIndex);
	void SetAnimationIndex(int nIndex, float& period);
	void SetAnimatinoIndexNotBlend(int nindex, float& period);

	void SetRandomTrackPosition(); // 테스트용

	void SetPosition(D3DXVECTOR3 v)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter = v;
	}
	ST_SPHERE* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}

	ST_BONE* GetRoot() { return m_pRootFrame; }
	LPD3DXANIMATIONCONTROLLER GetAnicon() { return m_pAnimController; }
	void FindFrame(IN LPSTR FrameName, IN ST_BONE * pBone);

private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();
};

