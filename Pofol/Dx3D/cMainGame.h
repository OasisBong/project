#pragma once

class cCamera;
class cGrid;
class cCharController;
class cGroup;
class iMap;
class cSkinnedMesh;
class cMtlTex;
class cFiona;

class cMainGame
{
private:
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCharController*			m_pCharController;
	iMap*						m_pMap;
	std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;
	LPD3DXMESH					m_mapMesh;
	std::vector<cMtlTex*>		m_vecMtlTex;
	cSkinnedMesh*				m_pSkinnedMesh;
	cFiona*						m_pFiona;
	
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();
};

