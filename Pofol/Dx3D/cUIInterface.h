#pragma once
class cUIInterface
{
private:
	D3DXMATRIXA16				m_mWorld_interface;


	//HP바 스프라이트
	LPD3DXSPRITE				m_pHPBar_IN;	//안쪽
	LPD3DXSPRITE				m_pHPBar_Out;	//밖에쪽
	LPDIRECT3DTEXTURE9			m_pTexHPBar_IN;	//안쪽 텍스쳐
	LPDIRECT3DTEXTURE9			m_pTexHPBar_Out;//밖에쪽 텍스쳐
	LPD3DXFONT					m_pHPBar_Font;	//HP텍스트
	D3DXIMAGE_INFO				m_stImageInfo;
	D3DXIMAGE_INFO				m_stImageInfo2;

	//SP바 스프라이트
	LPD3DXSPRITE				m_pSPBar_IN;	//안쪽
	LPD3DXSPRITE				m_pSPBar_Out;	//밖에쪽
	LPDIRECT3DTEXTURE9			m_pTexSPBar_IN;	//안쪽 텍스쳐
	LPDIRECT3DTEXTURE9			m_pTexSPBar_Out;//밖에쪽 텍스쳐
	LPD3DXFONT					m_pSPBar_Font;	//HP텍스트
	D3DXIMAGE_INFO				m_stImageInfo_SPBar_Out;
	D3DXIMAGE_INFO				m_stImageInfo_SPBar_IN;
	
	//텍스트
	char strpt[128];
	//스킬단축키 창
	LPD3DXSPRITE				m_pSkillWindow;//스킬단축키 창
	LPDIRECT3DTEXTURE9			m_pTexSkillWindow;	//안쪽 텍스쳐
	D3DXIMAGE_INFO				m_stImageInfo_SkillWindow;
public:

	cUIInterface(void);
	~cUIInterface(void);

	// cUIObject override
	void Setup();
	void Render();
	void Update();
	//void Update(IN 플레이어HP, IN 플레이어SP); 플레이어 HP,SP를 받아서 실시간으로 Bar길이 없뎃 하믄 될것 같아욤 일단은!
};

