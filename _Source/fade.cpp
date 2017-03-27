//------------------------------------------------------------------------------
//	�^�C�g���F		�t�F�[�h�̊֐�
//	�t�@�C�����F	fade.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/07/11
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "fade.h"
#include "title.h"
#include "openAL.h"

//------------------------------------------------------------------------------
//	�֐���:	CFade::CFade()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CFade::CFade()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CFade::~CFade()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�f�X�g���N�^
//------------------------------------------------------------------------------
CFade::~CFade()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CFade *CFade::Create
//	����:	CMode *NextMode
//	�߂�l:	�Ȃ�
//	����:	�t�F�[�h�̐���
//------------------------------------------------------------------------------
CFade *CFade::Create(CMode *NextMode)
{
	CFade *pFade;

	//  �C���X�^���X����
	pFade = new CFade;

	//  ������
	pFade->Init();

	pFade->m_NextMode = NextMode;

	return pFade;
}

//------------------------------------------------------------------------------
//	�֐���:	void CFade::Init
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CFade::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  �f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_Pos = D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f);

	m_Size = D3DXVECTOR2(pScreenSize->x, pScreenSize->y);

	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_Fade = FADE_IN;

	//  �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		CManager::GetRenderer()->GetDevice(),
		FADE_TEXTURE_FILE,								//  �e�N�X�`���t�@�C���ʒu
		&m_TextureBuffer							//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
	);

	MakeVertex(pDevice);
}

//------------------------------------------------------------------------------
//	�֐���:	void CFade::Uninit
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CFade::Uninit(void)
{
	//  �e�N�X�`���o�b�t�@�̊J��
	SAFE_RELEASE(m_TextureBuffer);

	//  ���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	�֐���:	void CFade::Update
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_Fade)
	{
	case FADE_IN:
		m_Col.a -= 0.02f;
		if (m_Col.a <= 0.0f)
		{
			m_Fade = FADE_NONE;
		}
		break;
	case FADE_OUT:
		m_Col.a += 0.02f;
		if (m_Col.a >= 1.0f)
		{
			m_Fade = FADE_IN;

			//  ��ʐؑ�
			CManager::SetMode(m_NextMode);
		}
	default:
		break;
	}

	//  ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//  ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Col;

	//  �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	void CFade::Draw
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CFade::Draw(void)
{
	//�f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();;

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//  ���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////  �t�H�O������
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_TextureBuffer);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * nNumVertex, nNumPolygon);

	//  ���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	////  �t�H�O�L����
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	�֐���:	void CFade::SetFade
//	����:	FADE fade, bool PressButtonUse
//	�߂�l: �Ȃ�
//	����:	�Z�b�g�t�F�[�h
//------------------------------------------------------------------------------
void CFade::Set(CMode *NextMode)
{
	//�t�F�[�h�̏�Ԃ�ݒ�
	m_Fade = FADE_OUT;

	//���̃��[�h��ݒ�
	m_NextMode = NextMode;
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CFade::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CFade::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * nNumVertex,			//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,							//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,						//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL									//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//  ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Col;

	//  �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexBuffer->Unlock();
	return S_OK;
}