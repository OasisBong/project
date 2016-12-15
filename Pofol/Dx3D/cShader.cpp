#include "stdafx.h"
#include "cShader.h"


cShader::cShader()
{
}


cShader::~cShader()
{
}

LPD3DXEFFECT cShader::LoadShader(const char* filename)
{
	LPD3DXEFFECT effect = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags = dwShaderFlags | D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(g_pD3DDevice, filename, NULL, NULL, dwShaderFlags, NULL, &effect, &pError);

	if (!effect && pError)
	{
		int size = pError->GetBufferSize();
		void* ack = pError->GetBufferPointer();

		if (ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugString(str);
			delete[] str;
		}

		return NULL;
	}
	return effect;
}
