#pragma once

class iMap;

class cCharController
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, vPosition);
	D3DXVECTOR3					m_vDirection;
	float						m_fAngle;
	float						m_fSpeed;
	SYNTHESIZE(int, m_nAniIndex, AniIndex);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);

public:
	cCharController(void);
	~cCharController(void);

	void Update(iMap* pMap = NULL);
	void KeyControl(iMap* pMap);

	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}
	
};

