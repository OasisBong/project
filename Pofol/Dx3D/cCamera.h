#pragma once
<<<<<<< HEAD

=======
class cObjMap;
>>>>>>> 334c4bf429a1b8a487a5d7e734bf19981cd1149b
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
<<<<<<< HEAD
	void Update(D3DXVECTOR3* pTarget = NULL, D3DXVECTOR3* vEye = NULL);
=======
	void Update(D3DXVECTOR3* pTarget = NULL, cObjMap* pMap);
	//void Update(D3DXVECTOR3* pTarget = NULL, float distance = 0);
>>>>>>> 334c4bf429a1b8a487a5d7e734bf19981cd1149b
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

