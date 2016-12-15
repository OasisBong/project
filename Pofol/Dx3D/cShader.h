#pragma once
class cShader
{
private:
	LPD3DXEFFECT      m_pEffet;
	LPDIRECT3DTEXTURE9   tex1;
public:
	cShader();
	~cShader();

	LPD3DXEFFECT LoadShader(const char* filename);
};

