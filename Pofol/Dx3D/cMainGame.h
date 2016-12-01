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

class cMainGame
{
private:
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCharController*			m_pCharController;

	cFiona*						m_pFiona;
	cRegina*					m_pRegina;
	
	//HeightMap
	cObjMap*						m_pMap;
	
	//Vindictus Map test
	LPD3DXMESH					m_mapMesh;
	std::vector<cMtlTex*>		m_vecMtlTex;
	
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();
};

