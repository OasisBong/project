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
	

	SYNTHESIZE(bool, m_isEvent, isEvent);

	//HeightMap
	cObjMap*					m_pMap;

	//UI
	cUIInterface*				m_pUIs;

	//디버그
	LPD3DXFONT					m_pFontRocation;	//위치확인 폰트
	char strpt[128];
	int fionaAniNum;
	int aniNum;
	int time = 0;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();
	void TextRender();
	//D3DXVECTOR3* SetCamera();
	//float CameraDistance();
};

