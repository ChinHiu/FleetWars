//------------------------------------------------------------------------------
//	�^�C�g���F		�����Ԃ��̊֐�
//	�t�@�C�����F	spray.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/02/02
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "sprayBefore.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"

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
//	�֐���:	CSpray::CSpray
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CSpray::CSpray()
{
	m_VertexBuffer = NULL;					//  ���_�o�b�t�@�ւ̃|�C���g

}

//------------------------------------------------------------------------------
//	�֐���:	CSpray::~CSpray
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CSpray::~CSpray()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CSpray *CSpray::Create
//	����:	�Ȃ�
//	�߂�l:	pEffect
//	����:	�G�t�F�N�g�̐���
//------------------------------------------------------------------------------
CSpray *CSpray::Create(void)
{
	CSpray *pSpray;

	//  �C���X�^���X����
	pSpray = new CSpray;

	//  ������
	pSpray->Init();

	return pSpray;
}

//------------------------------------------------------------------------------
//	�֐���:	void CSpray::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CSpray::Init(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int i = 0; i < SPRAY_TYPE_MAX; i++)
	{
		switch (i)
		{
		case SPRAY_BEFORE_RIGHT:
			m_Anim[i].PatternX = 4;
			m_Anim[i].PatternY = 8;
			m_Anim[i].Frame = 2;
			break;
		case SPRAY_BEFORE_LEFT:
			m_Anim[i].PatternX = 4;
			m_Anim[i].PatternY = 8;
			m_Anim[i].Frame = 2;
			break;
		default:
			break;
		}
	}

	//  ���_���̍쐬
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	�֐���:	void CSpray::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CSpray::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	�֐���:	void CSpray::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CSpray::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	for (int i = 0; i < SPRAY_TYPE_MAX; i++)
	{
		if (m_Spray[i].Flag)
		{
			if (m_Spray[i].Anim.PatternX != 1 && m_Spray[i].Anim.PatternY != 1)
			{//  ���p�^�[���Əc�p�^�[�����P�ł͂Ȃ���΁A�e�N�X�`���A�j���[�V�����������s��
			 //  �e�N�X�`�����W�̐ݒ�
				SetTexture(m_Spray[i].Anim.Pattern, m_Spray[i].Anim.PatternX, m_Spray[i].Anim.PatternY, i);

				//  �J�E���g
				m_Spray[i].Anim.Cnt++;

				if (m_Spray[i].Anim.Cnt == m_Spray[i].Anim.Frame)
				{//  ���t���[�����ƂɍX�V
					m_Spray[i].Anim.Cnt = 0;						//  �A�j���[�V�����J�E���g�̏�����
					m_Spray[i].Anim.Pattern++;						//  �A�j���[�V�������݃p�^�[�����X�V

					if (m_Spray[i].Anim.Pattern == m_Spray[i].Anim.PatternX * m_Spray[i].Anim.PatternY)
					{//  �S�p�^�[�����񂵂��Ȃ��
						m_Spray[i].Anim.Pattern = 0;				//  �A�j���[�V�����p�^�[�����̏�����
						if (!m_Spray[i].AnimLoop)
						{//  ���[�v�ł͂Ȃ����
							m_Spray[i].Flag = false;
						}
					}
				}
			}

			//  ���_���̍X�V
			SetVertex(i);
		}
	}

}

//------------------------------------------------------------------------------
//	�֐���:	void CSpray::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CSpray::Draw(int nID)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//  ���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//  �t�H�O������
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//  �J�����O���s��Ȃ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	if (m_Spray[nID].Flag)
	{
		//  ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_Spray[nID].Matrix.World);

		//  �X�P�[���𔽉f
		D3DXMatrixScaling
		(
			&m_Spray[nID].Matrix.Scl,
			m_Spray[nID].Scl.x,
			m_Spray[nID].Scl.y,
			m_Spray[nID].Scl.z
		);
		D3DXMatrixMultiply
		(
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.Scl
		);

		//  ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll
		(
			&m_Spray[nID].Matrix.Rot,
			m_Spray[nID].Rot->y + m_Spray[nID].AdjustRot.y,
			m_Spray[nID].Rot->x + m_Spray[nID].AdjustRot.x,
			m_Spray[nID].Rot->z
		);
		D3DXMatrixMultiply
		(
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.Rot
		);

		//  �ʒu�𔽉f
		D3DXMatrixTranslation
		(
			&m_Spray[nID].Matrix.Trans,
			m_Spray[nID].Pos->x,
			m_Spray[nID].Pos->y,
			m_Spray[nID].Pos->z
		);
		D3DXMatrixMultiply
		(
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.Trans
		);

		//  ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_Spray[nID].Matrix.World);

		//  �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::GetEffectTextureBuffer(EFFECT_SPRAY_BEFORE));

		//  �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nID * nNumVertex, nNumPolygon);
	}

	//  ���e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//  ���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  �t�H�O�L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//  �J�����O���s��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CSpray::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CSpray::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * SPRAY_TYPE_MAX,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,									//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,										//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,									//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,									//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL												//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < SPRAY_TYPE_MAX; i++, pVtx += nNumVertex)
	{
		//  ���_���W�̐ݒ�
		pVtx[0].pos =
		pVtx[1].pos =
		pVtx[2].pos =
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���̐ݒ�
		pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
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
//	�֐���:	void CSpray::Set
//	����:	D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, SPRAY_TYPE Spray_Type, bool bAnimLoop
//	�߂�l:	�Ȃ�
//	����:	�����Ԃ��̎g�p�ݒ�
//------------------------------------------------------------------------------
void CSpray::Set(MODEL_TYPE Model_Type, D3DXVECTOR3 *pos, D3DXVECTOR3 *rot, D3DXVECTOR3 *size, SPRAY_TYPE Spray_Type, bool bAnimLoop)
{
	for (int i = 0; i < SPRAY_TYPE_MAX; i++)
	{
		if (!m_Spray[i].Flag)
		{
			m_Spray[i].Pos = pos;
			m_Spray[i].Rot = rot;
			m_Spray[i].Size = size;
			m_Spray[i].SprayType = Spray_Type;
			m_Spray[i].AnimLoop = bAnimLoop;
			m_Spray[i].Anim.PatternX = m_Anim[m_Spray[i].SprayType].PatternX;
			m_Spray[i].Anim.PatternY = m_Anim[m_Spray[i].SprayType].PatternY;
			m_Spray[i].Anim.Frame = m_Anim[m_Spray[i].SprayType].Frame;
			m_Type = Model_Type;

			switch (Model_Type)
			{
			case MODEL_GORSHKOV:
				switch (Spray_Type)
				{
				case SPRAY_BEFORE_LEFT:
					m_Spray[i].AdjustRot = D3DXVECTOR2(-D3DX_PI * 0.13f, -D3DX_PI * 0.42f);
					break;
				case SPRAY_BEFORE_RIGHT:
					m_Spray[i].AdjustRot = D3DXVECTOR2(D3DX_PI * 0.13f, -D3DX_PI * 0.58f);
					break;
				default:
					break;
				}
				break;
			case MODEL_HAMINA:
				switch (Spray_Type)
				{
				case SPRAY_BEFORE_LEFT:
					m_Spray[i].AdjustRot = D3DXVECTOR2(-D3DX_PI * 0.3f, -D3DX_PI * 0.5f);
					break;
				case SPRAY_BEFORE_RIGHT:
					m_Spray[i].AdjustRot = D3DXVECTOR2(D3DX_PI * 0.3f, -D3DX_PI * 0.5f);
					break;
				default:
					break;
				}
				break;
			}

			m_Spray[i].Flag = true;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CSpray::SetVertex
//	����:	int nID
//	�߂�l:	�Ȃ�
//	����:	���_���̐ݒ�
//------------------------------------------------------------------------------
void CSpray::SetVertex(int nID)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//if (m_Spray[nID].SprayType == SPRAY_BEHIDE)
	//{
		/*pVtx[0].pos = D3DXVECTOR3(-m_Spray[nID].Size->x * 0.5f, 0.0f, m_Spray[nID].Size->z);
		pVtx[1].pos = D3DXVECTOR3(m_Spray[nID].Size->x * 0.5f, 0.0f, m_Spray[nID].Size->z);
		pVtx[2].pos = D3DXVECTOR3(-m_Spray[nID].Size->x * 0.5f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_Spray[nID].Size->x * 0.5f, 0.0f, 0.0f);*/
	//}
	//else
	//{
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_Spray[nID].Size->y * 0.8f, m_Spray[nID].Size->z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_Spray[nID].Size->x, m_Spray[nID].Size->y * 0.8f, m_Spray[nID].Size->z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, -m_Spray[nID].Size->y * 0.2f, -m_Spray[nID].Size->z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_Spray[nID].Size->x, -m_Spray[nID].Size->y * 0.2f, -m_Spray[nID].Size->z * 0.5f);

	//}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	void CSpray::SetTexture
//	����:	int nPatternAnim, int nPatternX, int nPatternY
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CSpray::SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID)
{
	D3DXVECTOR2 TexAdjust;				//  �e�N�X�`�������W��
	int nPatternAnimX, nPatternAnimY;	//  �A�j���[�V�����p�^�[�����i�[����

	TexAdjust.x = 1.0f / float(nPatternX);
	TexAdjust.y = 1.0f / float(nPatternY);

	if (nPatternX == 1)
	{//  ���������p�^�[�����P�Ȃ�΁A�e�N�X�`��X���W�ς�炸�̐ݒ�
		nPatternAnimX = 1;
	}
	else
	{
		nPatternAnimX = nPatternAnim;
	}

	if (nPatternY == 1)
	{//  �����c���p�^�[�����P�Ȃ�΁A�e�N�X�`��Y���W�ς�炸�̐ݒ�
		nPatternAnimY = 0;
	}
	else
	{
		nPatternAnimY = nPatternAnim;
	}
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//  �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[1].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[2].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));
	pVtx[3].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}