#pragma once
#include "hStruct.h"


class cCamera;
class cGrid;
class cCharController;
class cGroup;
class iMap;
class cObjMap;
class cSkinnedMesh;
class cMtlTex;
class cFiona;
class cRegina;
class cUIInterface;

class cMainGame
{
private:
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCharController*			m_pCharController;

	cFiona*						m_pFiona;
	cRegina*					m_pRegina;
	
	//HeightMap
	cObjMap*					m_pMap;
	
	//UI
	LPD3DXFONT					m_pFont;
	LPD3DXSPRITE				m_pHPBar_Out;
	cUIObject*					m_pHPbars;

	cUIInterface*				m_pUIs;
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();
	D3DXVECTOR3* SetCamera();
	//D3DXVECTOR3* SetCamera();
	//float CameraDistance();
};

