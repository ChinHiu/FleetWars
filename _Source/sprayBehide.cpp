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
#include "sprayBehide.h"
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
//	�֐���:	CSprayBehide::CSprayBehide
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CSprayBehide::CSprayBehide(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;					//  ���_�o�b�t�@�ւ̃|�C���g

}

//------------------------------------------------------------------------------
//	�֐���:	CSprayBehide::~CSprayBehide
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CSprayBehide::~CSprayBehide()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CSprayBehide *CSprayBehide::Create
//	����:	�Ȃ�
//	�߂�l:	pEffect
//	����:	�G�t�F�N�g�̐���
//------------------------------------------------------------------------------
CSprayBehide *CSprayBehide::Create(void)
{
	CSprayBehide *pSpray;

	//  �C���X�^���X����
	pSpray = new CSprayBehide;

	//  ������
	pSpray->Init();

	return pSpray;
}

//------------------------------------------------------------------------------
//	�֐���:	void CSprayBehide::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CSprayBehide::Init(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_Anim.PatternX = 8;
	m_Anim.PatternY = 2;
	m_Anim.Frame = 2;

	//  ���_���̍쐬
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	�֐���:	void CSprayBehide::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CSprayBehide::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	�֐���:	void CSprayBehide::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CSprayBehide::Update(void)
{
	for (int i = 0; i < nSprayMax; i++)
	{
		if (m_SprayBehide[i].Flag)
		{
			if (m_SprayBehide[i].Anim.PatternX != 1 && m_SprayBehide[i].Anim.PatternY != 1)
			{//  ���p�^�[���Əc�p�^�[�����P�ł͂Ȃ���΁A�e�N�X�`���A�j���[�V�����������s��
				//  �e�N�X�`�����W�̐ݒ�
				SetTexture(m_SprayBehide[i].Anim.Pattern, m_SprayBehide[i].Anim.PatternX, m_SprayBehide[i].Anim.PatternY, i);

				//  �J�E���g
				m_SprayBehide[i].Anim.Cnt++;

				if (m_SprayBehide[i].Anim.Cnt == m_SprayBehide[i].Anim.Frame)
				{//  ���t���[�����ƂɍX�V
					m_SprayBehide[i].Anim.Cnt = 0;						//  �A�j���[�V�����J�E���g�̏�����
					m_SprayBehide[i].Anim.Pattern++;						//  �A�j���[�V�������݃p�^�[�����X�V

					if (m_SprayBehide[i].Anim.Pattern == m_SprayBehide[i].Anim.PatternX * m_SprayBehide[i].Anim.PatternY)
					{//  �S�p�^�[�����񂵂��Ȃ��
						m_SprayBehide[i].Anim.Pattern = 0;				//  �A�j���[�V�����p�^�[�����̏�����
						if (!m_SprayBehide[i].AnimLoop)
						{//  ���[�v�ł͂Ȃ����
							m_SprayBehide[i].Flag = false;
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
//	�֐���:	void CSprayBehide::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CSprayBehide::Draw(void)
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

	//  �y�o�b�t�@�֎~
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//  �J�����O���s��Ȃ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int i = 0; i < nSprayMax; i++)
	{
		if (m_SprayBehide[i].Flag)
		{
			//  ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_SprayBehide[i].Matrix.World);

			//  �X�P�[���𔽉f
			D3DXMatrixScaling( &m_SprayBehide[i].Matrix.Scl, m_SprayBehide[i].Scl.x, m_SprayBehide[i].Scl.y, m_SprayBehide[i].Scl.z );
			D3DXMatrixMultiply( &m_SprayBehide[i].Matrix.World, &m_SprayBehide[i].Matrix.World, &m_SprayBehide[i].Matrix.Scl );

			//  ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &m_SprayBehide[i].Matrix.Rot, m_SprayBehide[i].Rot->y, m_SprayBehide[i].Rot->x, m_SprayBehide[i].Rot->z );
			D3DXMatrixMultiply( &m_SprayBehide[i].Matrix.World, &m_SprayBehide[i].Matrix.World, &m_SprayBehide[i].Matrix.Rot );

			//  �ʒu�𔽉f
			D3DXMatrixTranslation( &m_SprayBehide[i].Matrix.Trans, m_SprayBehide[i].Pos->x, m_SprayBehide[i].Pos->y, m_SprayBehide[i].Pos->z );
			D3DXMatrixMultiply( &m_SprayBehide[i].Matrix.World, &m_SprayBehide[i].Matrix.World, &m_SprayBehide[i].Matrix.Trans );

			//  ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_SprayBehide[i].Matrix.World);

			//  �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, CManager::GetEffectTextureBuffer(EFFECT_SPRAY_BEHIDE));

			//  �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
		}
	}

	//  ���e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//  �y�o�b�t�@���s��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//  ���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  �t�H�O�L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//  �J�����O���s��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CSprayBehide::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CSprayBehide::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nSprayMax,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,							//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,								//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,							//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL										//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nSprayMax; i++, pVtx += nNumVertex)
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
//	�֐���:	void CSprayBehide::Set
//	����:	D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, SPRAY_TYPE Spray_Type, bool bAnimLoop
//	�߂�l:	�Ȃ�
//	����:	�����Ԃ��̎g�p�ݒ�
//------------------------------------------------------------------------------
void CSprayBehide::Set(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot, D3DXVECTOR3 *size, bool bAnimLoop)
{
	for (int i = 0; i < nSprayMax; i++)
	{
		if (!m_SprayBehide[i].Flag)
		{
			m_SprayBehide[i].Pos = pos;
			m_SprayBehide[i].Rot = rot;
			m_SprayBehide[i].Size = size;
			m_SprayBehide[i].AnimLoop = bAnimLoop;
			m_SprayBehide[i].Anim.PatternX = m_Anim.PatternX;
			m_SprayBehide[i].Anim.PatternY = m_Anim.PatternY;
			m_SprayBehide[i].Anim.Frame = m_Anim.Frame;
			m_SprayBehide[i].Flag = true;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CSprayBehide::SetVertex
//	����:	int nID
//	�߂�l:	�Ȃ�
//	����:	���_���̐ݒ�
//------------------------------------------------------------------------------
void CSprayBehide::SetVertex(int nID)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	pVtx[0].pos = D3DXVECTOR3(-m_SprayBehide[nID].Size->x * 0.5f,0.0f, m_SprayBehide[nID].Size->z);
	pVtx[1].pos = D3DXVECTOR3(m_SprayBehide[nID].Size->x * 0.5f, 0.0f, m_SprayBehide[nID].Size->z);
	pVtx[2].pos = D3DXVECTOR3(-m_SprayBehide[nID].Size->x * 0.5f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_SprayBehide[nID].Size->x * 0.5f, 0.0f, 0.0f);


	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	void CSprayBehide::SetTexture
//	����:	int nPatternAnim, int nPatternX, int nPatternY
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CSprayBehide::SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID)
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