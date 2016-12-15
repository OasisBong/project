#pragma once

class iMap;
class cFiona;

#define KEYBUFFERTIME 0.5f

class cCharController
{
private:
	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vDirection;
	int							m_AtkCount;
	float						m_fAngle;
	float						m_fSpeed;
	float						m_fMaxPeriod;

	SYNTHESIZE(int, m_nAniIndex, AniIndex);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);

public:
	cCharController(void);
	~cCharController(void);

	void Update(cFiona* Target, iMap* pMap = NULL);
	void KeyControl(cFiona* Target, iMap* pMap);
	
	
	void SetTargetAnimation(cFiona* Target, int index);// , string name);
	float GetDescPos(cFiona* Target);


	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}
	
};

