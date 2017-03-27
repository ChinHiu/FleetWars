//------------------------------------------------------------------------------
//	�^�C�g���F		���[�U�[�C���^�[�t�F�[�X�̊֐�
//	�t�@�C�����F	UI.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/01/07
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "UI.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "title.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define WEAPON_UI_SPACE (5.0f)
#define GLITTER_CNT		(500)

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CUI::CUI
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CUI::CUI(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;						//  ���_�o�b�t�@�ւ̃|�C��
}

//------------------------------------------------------------------------------
//	�֐���:	CUI::~CUI
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�f�X�g���N�^
//------------------------------------------------------------------------------
CUI::~CUI()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CUI *CUI::Create
//	����:	int			nPriority		//  �v���C�I���e�B
//			OBJECT_TYPE Object_Type		//  �I�u�W�F�N�g�^�C�v
//	�߂�l:	pUI
//	����:	UI�̐���
//------------------------------------------------------------------------------
CUI *CUI::Create()
{
	CUI *pUI;

	//  �C���X�^���X����
	pUI = new CUI();

	//  ������
	pUI->Init();

	return pUI;
}

//------------------------------------------------------------------------------
//	�֐���:	void CUI::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CUI::Init(void)
{
	//  ���_���̍쐬
	MakeVertex(CManager::GetRenderer()->GetDevice());
}

//------------------------------------------------------------------------------
//	�֐���:	void CUI::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CUI::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	�֐���:	void CUI::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CUI::Update(void)
{
	//  ���_���̐ݒ�
	SetVertex();
}

//------------------------------------------------------------------------------
//	�֐���:	void CUI::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CUI::Draw(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	//  ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//  ���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//  �t�H�O������
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	for (int i = 0; i < nUIMax; i++)
	{
		if (m_UI[i].Flag)
		{
			//  �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, CManager::GetUITextureBuffer(m_UI[i].Lable));

			//  �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
		}
	}

	//  ���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  �t�H�O�L����
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CUI::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CUI::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
		(
		sizeof(VERTEX_2D) * nNumVertex * nUIMax,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,							//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,								//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,							//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL										//  NULL�ɐݒ�
		)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nUIMax; i++, pVtx += nNumVertex)
	{
		//  ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);

		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		//  ���_�J���[�̐ݒ�
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_UI[i].Col;

		//  �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void CUI::SetVertex
//	����:	int nID
//	�߂�l:	�Ȃ�
//	����:	���_���̍X�V
//------------------------------------------------------------------------------
void CUI::SetVertex(void)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nUIMax; i++, pVtx += nNumVertex)
	{
		if (m_UI[i].Flag)
		{
			switch(m_UI[i].Type)
			{
			case UI_HEIGHT_SCROLL:
				pVtx[0].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f - m_UI[i].Size.y * m_UI[i].TexRate,	0.0f);
				pVtx[1].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f - m_UI[i].Size.y * m_UI[i].TexRate,	0.0f);
				pVtx[2].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f,										0.0f);
				pVtx[3].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f,										0.0f);
				break;
			case UI_WIDTH_SCROLL:
				pVtx[0].pos = D3DXVECTOR3(m_UI[i].Pos.x,									m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * m_UI[i].TexRate, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(m_UI[i].Pos.x,									m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * m_UI[i].TexRate, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
				break;
			default:
				pVtx[0].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
				break;
			}

			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			//  ���_�J���[�̐ݒ�
			pVtx[0].col =
			pVtx[1].col =
			pVtx[2].col =
			pVtx[3].col = m_UI[i].Col;

			//  �e�N�X�`�����W�̐ݒ�
			switch (m_UI[i].Type)
			{
			case UI_WIDTH_SCROLL:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(m_UI[i].TexRate, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(m_UI[i].TexRate, 1.0f);
				break;
			case UI_HEIGHT_SCROLL:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f - m_UI[i].TexRate);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f - m_UI[i].TexRate);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			case UI_RESULT:
				pVtx[0].tex = D3DXVECTOR2(m_UI[i].TexRate, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(m_UI[i].TexRate + 0.2f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(m_UI[i].TexRate, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(m_UI[i].TexRate + 0.2f, 1.0f);
				break;
			default:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			}
		}
	}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

void CUI::SetColor(int nID, D3DXCOLOR col)
{
	m_UI[nID].Col = col;
}

void CUI::SetFlag(int nID, bool bFlag)
{
	m_UI[nID].Flag = bFlag;
}

void CUI::SetTexRate(int nID, float fTexRate)
{
	m_UI[nID].TexRate = fTexRate;
}

//------------------------------------------------------------------------------
//	�֐���:	void CUI::Set
//	����:	UI_TYPE		type		//  UI�^�C�v
//			D3DXVECTOR2 pos			//  �ʒu
//			D3DXVECTOR2 size		//  �T�C�Y
//			D3DXCOLOR	col			//  �F
//			bool		bTypeID		//  �^�C�v����ID�Ő������邩�ǂ���
//	�߂�l:	int nID
//	����:	UI�̐ݒ�
//------------------------------------------------------------------------------
int CUI::Set(UI_LABLE lable, UI_TYPE type, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	//int i;

	//for (i = 0; i < nUIMax; i++)
	//{
		if (!m_UI[lable].Flag)
		{
			m_UI[lable].Pos = pos;
			m_UI[lable].Lable = lable;
			m_UI[lable].Type = type;
			m_UI[lable].Flag = true;
			m_UI[lable].Size.x = size.x;
			m_UI[lable].Size.y = size.y;
			m_UI[lable].Col = col;
			//break;
		}
	//}

	return (int)lable;
}