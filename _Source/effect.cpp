//------------------------------------------------------------------------------
//	�^�C�g���F		�o���b�g�֘A�̊֐�
//	�t�@�C�����F	bullet.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/09/15
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "effect.h"
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
//	�֐���:	CEffect::CEffect
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CEffect::CEffect(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;					//  ���_�o�b�t�@�ւ̃|�C���g

}

//------------------------------------------------------------------------------
//	�֐���:	CEffect::~CEffect
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CEffect::~CEffect()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CEffect *CEffect::Create
//	����:	�Ȃ�
//	�߂�l:	pEffect
//	����:	�G�t�F�N�g�̐���
//------------------------------------------------------------------------------
CEffect *CEffect::Create(void)
{
	CEffect *pEffect;

	//  �C���X�^���X����
	pEffect = new CEffect;

	for (int i = EFFECT_SHOT_FIRE, j = 0; i <= EFFECT_EXPLOSION_001; i++, j++)
	{
		switch (i)
		{
		case EFFECT_EXPLOSION_000:
			pEffect->m_Anim[j].PatternX = 8;
			pEffect->m_Anim[j].PatternY = 6;
			pEffect->m_Anim[j].Frame = 1;
			break;
		case EFFECT_EXPLOSION_001:
			pEffect->m_Anim[j].PatternX = 8;
			pEffect->m_Anim[j].PatternY = 4;
			pEffect->m_Anim[j].Frame = 2;
			break;
		case EFFECT_SHOT_FIRE:
			pEffect->m_Anim[j].PatternX = 2;
			pEffect->m_Anim[j].PatternY = 2;
			pEffect->m_Anim[j].Frame = 1;
			break;
		default:
			break;
		}
	}

	//  ������
	pEffect->Init();

	return pEffect;
}

//------------------------------------------------------------------------------
//	�֐���:	void CEffect::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CEffect::Init(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���_���̍쐬
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	�֐���:	void CEffect::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CEffect::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	�֐���:	void CEffect::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CEffect::Update(void)
{
	for (int i = 0; i < nEffect_Anim_Max; i++)
	{
		if (m_Effect[i].Flag)
		{
			if (m_Effect[i].Anim.PatternX != 1 && m_Effect[i].Anim.PatternY != 1)
			{//  ���p�^�[���Əc�p�^�[�����P�ł͂Ȃ���΁A�e�N�X�`���A�j���[�V�����������s��
				//  �e�N�X�`�����W�̐ݒ�
				SetTexture(m_Effect[i].Anim.Pattern, m_Effect[i].Anim.PatternX, m_Effect[i].Anim.PatternY, i);

				//  �J�E���g
				m_Effect[i].Anim.Cnt++;

				if (m_Effect[i].Anim.Cnt == m_Effect[i].Anim.Frame)
				{//  ���t���[�����ƂɍX�V
					m_Effect[i].Anim.Cnt = 0;						//  �A�j���[�V�����J�E���g�̏�����
					m_Effect[i].Anim.Pattern++;						//  �A�j���[�V�������݃p�^�[�����X�V

					if (m_Effect[i].Anim.Pattern == m_Effect[i].Anim.PatternX * m_Effect[i].Anim.PatternY)
					{//  �S�p�^�[�����񂵂��Ȃ��
						m_Effect[i].Anim.Pattern = 0;				//  �A�j���[�V�����p�^�[�����̏�����
						if (!m_Effect[i].AnimLoop)
						{//  ���[�v�ł͂Ȃ����
							m_Effect[i].Flag = false;
						}
					}
				}
			}

			//  ���_���̐ݒ�
			SetVertex(i);
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CEffect::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CEffect::Draw(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//  �t�H�O������
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//  ���e�X�g���s��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  ���e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  ���e�X�g���i�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  ���Q�ƒl

	//  ���Z�����i�A���t�@�u�����h�j
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//  SRC(���ꂩ��`�悷�鑤)�{DEST(���ɕ`�悳��Ă鑤)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//  SRC�𔼓�����������
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				//  DEST�����̂܂ܕ`�悷��

	//  �y�o�b�t�@�֎~
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	for (int i = 0; i < nEffect_Anim_Max; i++)
	{
		if (m_Effect[i].Flag)
		{
			//  ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_Effect[i].Matrix.World);

			//  �r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &m_Effect[i].ViewMatrix);

			//  �t�s������߂�
			D3DXMatrixInverse(&m_Effect[i].Matrix.World, NULL, &m_Effect[i].ViewMatrix);

			m_Effect[i].Matrix.World._41 = 0.0f;
			m_Effect[i].Matrix.World._42 = 0.0f;
			m_Effect[i].Matrix.World._43 = 0.0f;

			//  �X�P�[���𔽉f
			D3DXMatrixScaling( &m_Effect[i].Matrix.Scl, m_Effect[i].Scl.x, m_Effect[i].Scl.y, m_Effect[i].Scl.z );
			D3DXMatrixMultiply( &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.Scl );

			//  ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &m_Effect[i].Matrix.Rot, m_Effect[i].Rot.y, m_Effect[i].Rot.x, m_Effect[i].Rot.z );
			D3DXMatrixMultiply( &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.Rot );

			//  �ʒu�𔽉f
			D3DXMatrixTranslation( &m_Effect[i].Matrix.Trans, m_Effect[i].Pos.x, m_Effect[i].Pos.y, m_Effect[i].Pos.z );
			D3DXMatrixMultiply( &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.Trans );

			//  ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_Effect[i].Matrix.World);

			//  �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, CManager::GetEffectTextureBuffer(m_Effect[i].EffectType));

			//  �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
		}
	}

	//  ���e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);				//  ���e�X�g������

	//  �ʏ�u�����h
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���f�X�e�B�l�[�V�����J���[�̎w��

	//  �y�o�b�t�@�L��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  �t�H�O������
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CEffect::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CEffect::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nEffect_Anim_Max,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
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

	for (int i = 0; i < nEffect_Anim_Max; i++, pVtx += nNumVertex)
	{
		//  ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_Effect[i].Size.x * 0.5f, m_Effect[i].Size.y * 0.5f, m_Effect[i].Size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_Effect[i].Size.x * 0.5f, m_Effect[i].Size.y * 0.5f, m_Effect[i].Size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_Effect[i].Size.x * 0.5f, -m_Effect[i].Size.y * 0.5f, -m_Effect[i].Size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_Effect[i].Size.x * 0.5f, -m_Effect[i].Size.y * 0.5f, -m_Effect[i].Size.z * 0.5f);

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
//	�֐���:	void CEffect::SetTexture
//	����:	int nPatternAnim, int nPatternX, int nPatternY
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CEffect::SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, EFFECT_TYPE EffectType, bool bAnimLoop, bool AlphaTest, bool AlphaBlend, bool ZBuffer)
{
	for (int i = 0; i < nEffect_Anim_Max; i++)
	{
		if (!m_Effect[i].Flag)
		{
			m_Effect[i].Pos = pos;
			m_Effect[i].Size = size;
			m_Effect[i].EffectType = EffectType;
			m_Effect[i].AnimLoop = bAnimLoop;
			m_Effect[i].Anim.PatternX = m_Anim[m_Effect[i].EffectType - EFFECT_SHOT_FIRE].PatternX;
			m_Effect[i].Anim.PatternY = m_Anim[m_Effect[i].EffectType - EFFECT_SHOT_FIRE].PatternY;
			m_Effect[i].Anim.Frame = m_Anim[m_Effect[i].EffectType - EFFECT_SHOT_FIRE].Frame;
			m_Effect[i].AlphaTest = AlphaTest;
			m_Effect[i].AlphaBlend = AlphaBlend;
			m_Effect[i].ZBuffer = ZBuffer;
			m_Effect[i].Flag = true;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CEffect::SetVertex
//	����:	int nID
//	�߂�l:	�Ȃ�
//	����:	���_���̐ݒ�
//------------------------------------------------------------------------------
void CEffect::SetVertex(int nID)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//  ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_Effect[nID].Size.x * 0.5f, m_Effect[nID].Size.y * 0.5f, m_Effect[nID].Size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_Effect[nID].Size.x * 0.5f, m_Effect[nID].Size.y * 0.5f, m_Effect[nID].Size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_Effect[nID].Size.x * 0.5f, -m_Effect[nID].Size.y * 0.5f, -m_Effect[nID].Size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_Effect[nID].Size.x * 0.5f, -m_Effect[nID].Size.y * 0.5f, -m_Effect[nID].Size.z * 0.5f);

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	void CEffect::SetTexture
//	����:	int nPatternAnim, int nPatternX, int nPatternY
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CEffect::SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID)
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