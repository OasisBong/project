#pragma once
class cUIInterface
{
private:
	D3DXMATRIXA16				m_mWorld_interface;


	//HP�� ��������Ʈ
	LPD3DXSPRITE				m_pHPBar_IN;	//����
	LPD3DXSPRITE				m_pHPBar_Out;	//�ۿ���
	LPDIRECT3DTEXTURE9			m_pTexHPBar_IN;	//���� �ؽ���
	LPDIRECT3DTEXTURE9			m_pTexHPBar_Out;//�ۿ��� �ؽ���
	LPD3DXFONT					m_pHPBar_Font;	//HP�ؽ�Ʈ
	D3DXIMAGE_INFO				m_stImageInfo;
	D3DXIMAGE_INFO				m_stImageInfo2;

	//SP�� ��������Ʈ
	LPD3DXSPRITE				m_pSPBar_IN;	//����
	LPD3DXSPRITE				m_pSPBar_Out;	//�ۿ���
	LPDIRECT3DTEXTURE9			m_pTexSPBar_IN;	//���� �ؽ���
	LPDIRECT3DTEXTURE9			m_pTexSPBar_Out;//�ۿ��� �ؽ���
	LPD3DXFONT					m_pSPBar_Font;	//HP�ؽ�Ʈ
	D3DXIMAGE_INFO				m_stImageInfo_SPBar_Out;
	D3DXIMAGE_INFO				m_stImageInfo_SPBar_IN;
	
	//�ؽ�Ʈ
	char strpt[128];
	//��ų����Ű â
	LPD3DXSPRITE				m_pSkillWindow;//��ų����Ű â
	LPDIRECT3DTEXTURE9			m_pTexSkillWindow;	//���� �ؽ���
	D3DXIMAGE_INFO				m_stImageInfo_SkillWindow;
public:

	cUIInterface(void);
	~cUIInterface(void);

	// cUIObject override
	void Setup();
	void Render();
	void Update();
	//void Update(IN �÷��̾�HP, IN �÷��̾�SP); �÷��̾� HP,SP�� �޾Ƽ� �ǽð����� Bar���� ���� �Ϲ� �ɰ� ���ƿ� �ϴ���!
};

