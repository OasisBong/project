#pragma once
#include "cAction.h"
class cObjMap;

class cRegina;

class cCamera
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vEye, Eye);
	SYNTHESIZE(D3DXVECTOR3, m_vLookAt, LookAt);
	SYNTHESIZE(D3DXVECTOR3, m_vUp, vUp);
	SYNTHESIZE(float, m_fDistance, fDistance);

	SYNTHESIZE(float, m_fDistance2, fDistance2);
	SYNTHESIZE(float, m_fAngleX, fAngleX);
	SYNTHESIZE(float, m_fAngleY, fAngleY);

	SYNTHESIZE(float, m_fAngleX2, fAngleX2);
	SYNTHESIZE(float, m_fAngleY2, fAngleY2);
	SYNTHESIZE(int, m_neTime, eTime );
	SYNTHESIZE(float, m_fLookatY, fLookatY);
	SYNTHESIZE(float, m_fEyeY, fEyeY);
private:
	bool			m_isLButtonDown;
	POINT			m_ptPrevMouse;
	//float			m_fAngleX;
	//float			m_fAngleY;

public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	void Update(cObjMap* pMap, D3DXVECTOR3* pTarget = NULL);
	//void Update(D3DXVECTOR3* pTarget = NULL, float distance = 0);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void UpdateReginaSpawn(cObjMap* pMap, D3DXVECTOR3* pTarget);
	void CameraShake();
};

