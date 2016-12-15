#pragma once

enum OBJECT_TYPE
{
	OBJ_NONE,
	OBJ_FLOWER,
	OBJ_SKYBOX
};
class cMtlTex;
class cGroup;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*>		m_mapMtlTex;
	std::map<std::string, cMtlTex*>		m_mapHiddenMtlTex;
	std::map<std::string, cMtlTex*>		m_mapSkyBoxMtlTex;
	string								m_sPath;
public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN char* szFilename, OUT std::vector<cGroup*>& vecGroup, IN D3DXMATRIXA16* pmat = NULL);
	LPD3DXMESH Load(IN char* szFilename, OUT std::vector<cMtlTex*>& vecMtlTex, IN D3DXMATRIXA16* pmat = NULL);

	LPD3DXMESH Load(IN char* szFilename, IN D3DXMATRIX* pMat,
		OUT std::vector<cMtlTex*>& vecMtlTex, OUT LPD3DXMESH& mesh,
		OUT std::vector<cMtlTex*>& vecHiddenMtlTex, OUT std::vector<LPD3DXMESH>& vecHiddenMesh);

	void Loadmap(IN char* szFilename, IN D3DXMATRIX* pMat,
		OUT std::vector<cMtlTex*>& vecMtlTex, OUT LPD3DXMESH& mesh,
		OUT std::vector<cMtlTex*>& vecHiddenMtlTex, OUT LPD3DXMESH& hiddenmesh,
		OUT std::vector<cMtlTex*>& vecSkyBoxMtlTex, OUT LPD3DXMESH& SkyBoxmesh);

	void LoadMtlLib(char* szFilename);
	void LoadMtlLib(IN char* szFilename, OUT std::vector<cMtlTex*>& vecMtlTex);
	void LoadMtlLib(IN char* szFilename, OUT std::vector<cMtlTex*>& vecMtlTex, OUT std::vector<cMtlTex*>& vecHiddenMtlTex, OUT std::vector<cMtlTex*>& vecSkyBoxMtlTex);

	bool StartsWith(char* str, char* beginStr);
	char* StringToChar(string input);
	LPD3DXMESH getHiddenMash(OUT LPD3DXMESH& mash_out);

};

