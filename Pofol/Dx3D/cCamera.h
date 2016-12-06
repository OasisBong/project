#pragma once

class cObjMap;
class cCamera
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vEye, Eye);

private:
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	bool			m_isLButtonDown;
	POINT			m_ptPrevMouse;
	float			m_fAngleX;
	float			m_fAngleY;
	float			m_fDistance;

public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	//void Update(cObjMap* pMap, D3DXVECTOR3* pTarget = NULL);
	//void Update(D3DXVECTOR3* pTarget = NULL, float distance = 0);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

