//------------------------------------------------------------------------------
//	�^�C�g���F		DirectX�֘A�̊֐�
//	�t�@�C�����F	renderer.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/18
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"
#include "debugProc.h"
#include "camera.h"
#include "light.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include <typeinfo.h>
#include "title.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CRenderer::CRenderer
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CRenderer::CRenderer()
{
	m_D3D			= NULL;			//  Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	m_D3DDevice		= NULL;			//  Direct3D�f�o�C�X�ւ̃|�C���^
#ifdef _DEBUG
	m_D3DXFont		= NULL;			//  �t�H���g�ւ̃|�C���^
#endif

	m_bFog = true;
}

//------------------------------------------------------------------------------
//	�֐���:	CRenderer::~CRenderer
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�f�X�g���N�^
//------------------------------------------------------------------------------
CRenderer::~CRenderer()
{
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CRenderer::Init
//	����:	HINSTANCE hInstance, HWND hWnd, BOOL bWindow
//	�߂�l:	E_FAIL���Ə��������s�AS_OK���Ə���������
//	����:	����������
//------------------------------------------------------------------------------
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	D3DXVECTOR2 *Screen = GetScreenSize();
	
	//  Direct3D�I�u�W�F�N�g�̐���
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_D3D == NULL)
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));							//  ���[�N���[���N���A

	//  �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	if (bWindow == TRUE)
	{
		//  �E�B���h�E���[�h
		//  ���݃f�B�X�v���C���[�h���擾
		if (FAILED(m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		{
			return E_FAIL;
		}
		d3dpp.BackBufferWidth = (UINT)Screen->x;				//  ��ʂ̕����w��
		d3dpp.BackBufferHeight = (UINT)Screen->y;				//  ��ʂ̍������w��
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				//  32Bit Color
		d3dpp.Windowed = TRUE;									//  �E�B���h�E���[�h
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;				//  �f���M���ɓ������ăt���b�v����
		d3dpp.BackBufferCount = 1;								//  �o�b�N�o�b�t�@�̐�
		d3dpp.EnableAutoDepthStencil = TRUE;					//  �f�v�X�o�b�t�@(Z�o�b�t�@)�ƃX�e���c���o�b�t�@���쐬
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;			//  �f�v�X�o�b�t�@�Ƃ���32�r�b�g���g��
	}
	else
	{
		//  �t���X�N���[�����[�h
		d3dpp.BackBufferWidth = (UINT)Screen->x;				//  ��ʂ̕����w��
		d3dpp.BackBufferHeight = (UINT)Screen->y;				//  ��ʂ̍������w��
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				//  32Bit Color
		d3dpp.Windowed = FALSE;									//  �E�B���h�E���[�h
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;				//  �f���M���ɓ������ăt���b�v����
		d3dpp.BackBufferCount = 1;								//  �o�b�N�o�b�t�@�̐�
		d3dpp.FullScreen_RefreshRateInHz = 75;					//  ���t���b�V�����[�g
		d3dpp.EnableAutoDepthStencil = TRUE;					//  �f�v�X�o�b�t�@(Z�o�b�t�@)�ƃX�e���c���o�b�t�@���쐬
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;			//  �f�v�X�o�b�t�@�Ƃ���32�r�b�g���g��
	}


	//  �f�o�C�X�̐���
	//  �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	//  �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(
		m_D3D->CreateDevice
		(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_D3DDevice
		)))
	{
		//  ��L�̐ݒ肪���s������
		//  �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(
			m_D3D->CreateDevice
			(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_D3DDevice
			)))
		{
			//  ��L�̐ݒ肪���s������
			//  �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(
				m_D3D->CreateDevice
				(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_D3DDevice
				)))
			{
				//  ���������s
				return E_FAIL;
			}
		}
	}

	//�e�N�X�`���[�X�e�[�W�p�����[�^�̂̐ݒ�
	//m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_D3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
	m_D3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); //D3DTA_DIFFUSE

	 //  �����_�[�X�e�[�g�̐ݒ�
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					//  �J�����O���s��
	//m_D3DDevice -> SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				//  �J�����O���s��Ȃ�
	//m_D3DDevice -> SetRenderState( D3DRS_ZENABLE, TRUE );						//  Z�o�b�t�@���g�p
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					//  ���u�����h���s��
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				//  ���\�[�X�J���[�̎w��
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			//  ���f�X�e�B�l�[�V�����J���[�̎w��

	//�T���v���[�X�e�[�g�̐ݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		//�e�N�X�`��( U�l )�J��Ԃ��ݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		//�e�N�X�`��( V�l )�J��Ԃ��ݒ�

	//  �t�H�O�̐ݒ�
	FLOAT StartPos = 0;																	//  �J�n�ʒu
	FLOAT EndPos = 8000;																//  �I���ʒu
	m_D3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.90f, 0.90f, 0.90f, 0.1f));	//  ���F�ŕs����
	m_D3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&StartPos));					//  �J�n�ʒu
	m_D3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&EndPos));						//  �I���ʒu
	m_D3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);						//  ���_���[�h
	m_D3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);						//  �e�[�u�����[�h

#ifdef _DEBUG
	//  �f�o�b�O�v���V�[�W���\���p�t�H���g��ݒ�
	D3DXCreateFont
	(
		m_D3DDevice,					//  �f�o�C�X
		30,								//  �����̍���
		0,								//	������
		FW_NORMAL,						//  �t�H���g�̑���	
		NULL,							//  MIPMAP�̃��x��
		FALSE,							//  �C�^���b�N���H
		SHIFTJIS_CHARSET,				//  �����Z�b�g
		OUT_DEFAULT_PRECIS,				//  �o�͐��x
		DRAFT_QUALITY,					//  �o�͕i��							
		DEFAULT_PITCH | FF_DONTCARE,	//  �t�H���g�s�b�`�ƃt�@�~��  //FIXED_PITCH=�Œ蕝	VARIABLE_PITCH=�ϕ�							
		"Terminal",						//  �t�H���g��				
		&m_D3DXFont						//  Direct3D�t�H���g�ւ̃|�C���^�ւ̃A�h���X
	);
#endif
	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void CRenderer::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CRenderer::Uninit(void)
{
	//  �f�o�C�X�̊J��
	SAFE_RELEASE(m_D3DDevice);

	//  �I�u�W�F�N�g�̊J��
	SAFE_RELEASE(m_D3D);

#ifdef _DEBUG
	//  �f�o�b�O�v���V�[�W���\���p�t�H���g��ݒ�
	SAFE_RELEASE(m_D3DXFont);
#endif
}

//------------------------------------------------------------------------------
//	�֐���:	void CRenderer::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CRenderer::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F1)) m_bFillMode = m_bFillMode ? false : true;

	if (pKeyboard->GetTrigger(DIK_F2)) m_bFog = m_bFog ? false : true;
}

//------------------------------------------------------------------------------
//	�֐���:	void CRenderer::Begin
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`��J�n
//------------------------------------------------------------------------------
void CRenderer::Begin(void)
{
	CMode *pMode = CManager::GetMode();

	//  �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_D3DDevice->Clear
	(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0
	);

	//  �Q�[�����[�h�̍X�V����
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		if (m_bFog)
		{
			m_D3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);									//  �t�H�O�FON
		}
		else
		{
			m_D3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		}
	}

#ifdef _DEBUG
	switch (m_bFillMode)
	{
	case true:
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	//  ���C���t���[��4
		break;
	case false:
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		//  �h��Ԃ�
		break;
	}
#endif

	//  Direct3D�ɂ��`��̊J�n
	m_D3DDevice->BeginScene();
#ifdef _DEBUG
	//FPS���̕`�揈��
	DrawFPS();
#endif
}

//------------------------------------------------------------------------------
//	�֐���:	void CRenderer::End
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`��I��
//------------------------------------------------------------------------------
void CRenderer::End(void)
{
	//  Direct3D�ɂ��`��̏I��
	m_D3DDevice->EndScene();

	//  �t�H�O������
	if (m_bFog)	m_D3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (m_bFillMode) m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		//  �h��Ԃ�

	//  �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_D3DDevice->Present(NULL, NULL, NULL, NULL);
}

//------------------------------------------------------------------------------
//	�֐���:	LPDIRECT3DDEVICE9 CRenderer::GetDevice
//	����:	�Ȃ�
//	�߂�l:	m_D3DDevice
//	����:	�f�o�C�X���擾
//------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_D3DDevice;
}

#ifdef _DEBUG
//------------------------------------------------------------------------------
//	�֐���:	void CRenderer::DrawFPS
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	FPS���̕`�揈��
//------------------------------------------------------------------------------
void CRenderer::DrawFPS(void)
{
	D3DXVECTOR2 *pScreen = GetScreenSize();
	int *pCountFPS;

	pCountFPS = GetFPS();
	RECT rect = { 0, 0, (int)pScreen->x, (int)pScreen->y };

	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", *pCountFPS);

	//�e�L�X�g�`��
	m_D3DXFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT | DT_BOTTOM, D3DCOLOR_RGBA(50, 255, 50, 255));
}
#endif