#pragma once

#include "iMap.h"
class cMtlTex;

class cObjMap : public iMap
{
private:
	//Vindictus Map test
	SYNTHESIZE(LPD3DXMESH, m_mapMesh, MapMesh);
	SYNTHESIZE(LPD3DXMESH, m_mapHiddenMesh, MapHiddenMesh);
	SYNTHESIZE(LPD3DXMESH, m_mapSkyBoxMesh, MapSkyBoxMesh);
	SYNTHESIZE(vector<cMtlTex*>, m_vecMtlTex, vecMtlTex);
	SYNTHESIZE(vector<cMtlTex*>, m_vecHiddenMtlTex, vecHiddenMtlTex);
	SYNTHESIZE(vector<cMtlTex*>, m_vecSkyBoxMtlTex, vecSkyBoxMtlTex);
	SYNTHESIZE(D3DXMATRIX, m_matWorld, MatWorld);

	LPD3DXEFFECT m_pEffect;
	LPDIRECT3DTEXTURE9   textest;


	//vector<D3DXVECTOR3*>	m_vecSurface;
public:
	cObjMap(void);
	virtual ~cObjMap(void);

	virtual void Load(char* szMap, char* szSurface = NULL, D3DXMATRIXA16* pmat = NULL);

	// iMap override
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
	virtual void Render() override;

	LPD3DXEFFECT LoadShader(const char* filename);
};

