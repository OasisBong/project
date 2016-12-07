#include "stdafx.h"
#include "cUIInterface.h"


cUIInterface::cUIInterface()
	: m_pHPBar_IN(NULL)
	, m_pHPBar_Out(NULL)
	, m_pSPBar_IN(NULL)
	, m_pSPBar_Out(NULL)
	, m_pSkillWindow(NULL)
	, m_pHPBar_Font(NULL)
	, m_pSPBar_Font(NULL)
	, m_pTexSkillWindow(NULL)

{
	D3DXMatrixIdentity(&m_mWorld_interface);
}


cUIInterface::~cUIInterface()
{
	SAFE_RELEASE(m_pHPBar_IN);
	SAFE_RELEASE(m_pHPBar_Out);
	SAFE_RELEASE(m_pTexHPBar_IN);
	SAFE_RELEASE(m_pTexHPBar_Out);
	SAFE_RELEASE(m_pSPBar_IN);
	SAFE_RELEASE(m_pSPBar_Out);
	SAFE_RELEASE(m_pTexSPBar_IN);
	SAFE_RELEASE(m_pTexSPBar_Out);
	SAFE_RELEASE(m_pSkillWindow);
	SAFE_RELEASE(m_pHPBar_Font);
	SAFE_RELEASE(m_pSPBar_Font);
	SAFE_RELEASE(m_pSkillWindow);
	SAFE_RELEASE(m_pTexSkillWindow);
}

void cUIInterface::Setup()
{
	//HP바 밖에쪽 셋업
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./UI/bar/hpBar_Out.tga",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTexHPBar_Out);
	D3DXCreateSprite(g_pD3DDevice, &m_pHPBar_Out);

	//HP바 안쪽 셋업
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./UI/bar/hpBar_In.tga",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo2,
		NULL,
		&m_pTexHPBar_IN);
	D3DXCreateSprite(g_pD3DDevice, &m_pHPBar_IN);

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 20;
	fd.Width = 10;
	fd.Weight = FW_BOLD;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, "Century Gothic");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pHPBar_Font);

	//SP바 밖에쪽 셋업
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./UI/bar/hpBar_Out.tga",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo_SPBar_Out,
		NULL,
		&m_pTexSPBar_Out);
	D3DXCreateSprite(g_pD3DDevice, &m_pSPBar_Out);

	//SP바 안쪽 셋업
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./UI/bar/spBar_In.tga",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo_SPBar_IN,
		NULL,
		&m_pTexSPBar_IN);
	D3DXCreateSprite(g_pD3DDevice, &m_pSPBar_IN);

	D3DXFONT_DESC fd2;
	ZeroMemory(&fd2, sizeof(D3DXFONT_DESC));
	fd2.Height = 20;
	fd2.Width = 10;
	fd2.Weight = FW_BOLD;
	fd2.Italic = false;
	fd2.CharSet = DEFAULT_CHARSET;
	fd2.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd2.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd2.FaceName, "Century Gothic");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd2, &m_pSPBar_Font);

	//스킬윈도우 셋업
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./UI/window/skill_quickslot.tga",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo_SkillWindow,
		NULL,
		&m_pTexSkillWindow);
	D3DXCreateSprite(g_pD3DDevice, &m_pSkillWindow);

}

void cUIInterface::Render()
{
	D3DXMatrixTranslation(&m_mWorld_interface, 350, 5, 0);

	RECT rcSrc;
	SetRect(&rcSrc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
	m_pHPBar_Out->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pHPBar_Out->SetTransform(&m_mWorld_interface);
	m_pHPBar_Out->Draw(m_pTexHPBar_Out,
		&rcSrc,
		&D3DXVECTOR3(350, 5, 0),
		&D3DXVECTOR3(350, 5, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pHPBar_Out->End();

	RECT rcSrc2;
	SetRect(&rcSrc2, 0, 0, m_stImageInfo2.Width, m_stImageInfo2.Height);
	m_pHPBar_IN->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pHPBar_IN->SetTransform(&m_mWorld_interface);
	m_pHPBar_IN->Draw(m_pTexHPBar_IN,
		&rcSrc2,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(8, 9, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pHPBar_IN->End();

	RECT rcSrc3;
	SetRect(&rcSrc3, 0, 0, m_stImageInfo_SPBar_Out.Width, m_stImageInfo_SPBar_Out.Height);
	m_pSPBar_Out->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSPBar_Out->SetTransform(&m_mWorld_interface);
	m_pSPBar_Out->Draw(m_pTexSPBar_Out,
		&rcSrc3,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 25, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSPBar_Out->End();

	RECT rcSrc4;
	SetRect(&rcSrc4, 0, 0, m_stImageInfo_SPBar_IN.Width, m_stImageInfo_SPBar_IN.Height);
	m_pSPBar_IN->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSPBar_IN->SetTransform(&m_mWorld_interface);
	m_pSPBar_IN->Draw(m_pTexSPBar_IN,
		&rcSrc4,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(8, 33, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSPBar_IN->End();

	RECT textRc;
	sprintf(strpt, "5000 / 5000"); //지금은 걍 때려박았는데 캐릭터 겟,셋터 이용해서 조정하죵
	SetRect(&textRc, 1070, 8, 0, 0);
	m_pHPBar_Font->DrawText(NULL, strpt, strlen(strpt), &textRc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	RECT textRc2;
	sprintf(strpt, "155 / 155 / %d", m_stImageInfo_SPBar_IN.Width);
	SetRect(&textRc2, 1070, 35, 0, 0);
	m_pSPBar_Font->DrawText(NULL, strpt, strlen(strpt), &textRc2, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	RECT rcSrc5;
	SetRect(&rcSrc5, 0, 0, m_stImageInfo_SkillWindow.Width, m_stImageInfo_SkillWindow.Height);
	m_pSkillWindow->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSkillWindow->SetTransform(&m_mWorld_interface);
	m_pSkillWindow->Draw(m_pTexSkillWindow,
		&rcSrc5,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(130, 550, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSkillWindow->End();
}

void cUIInterface::Update()
{

}
